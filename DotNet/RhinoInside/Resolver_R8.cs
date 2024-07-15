using System;
using System.IO;
using System.Reflection;
using System.Globalization;
using System.Runtime.Loader;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Runtime.CompilerServices;

[assembly: InternalsVisibleTo("RhinoInside.Tests")]

namespace RhinoInside
{
  /// <summary>
  /// Rhino.Inside initialization exception
  /// </summary>
  public sealed class RhinoInsideInitializationException : Exception
  {
    public RhinoInsideInitializationException() { }
    public RhinoInsideInitializationException(string message) : base(message) { }
    public RhinoInsideInitializationException(string message, Exception innerException) : base(message, innerException) { }
  }

  public static class Resolver
  {
    static bool s_initialized;

    /// <summary>
    /// Directory used by assembly resolver to attempt load core Rhino assemblies.
    /// Examples:
    ///   'C:/Program Files/Rhino 8/System' on Windows
    ///   '/Application/Rhino 8.app/Contents/Frameworks' on Mac
    /// </summary>
    public static string RhinoSystemDirectory { get; private set; }

    /// <summary>
    /// Set up an assembly resolver to load RhinoCommon and other Rhino assemblies from where Rhino is installed
    /// </summary>
    /// <param name="useLatest">Whether or not to use the newest installation of Rhino on the system. By default the resolver will only use an installation with a matching major version</param>
    /// <exception cref="RhinoInsideInitializationException">Error occured during initialization.</exception>
    public static void Initialize(bool useLatest = false) => Initialize(RhinoFinder.FindRhinoSystemDirectory(useLatest));

    /// <summary>
    /// Set up an assembly resolver to load RhinoCommon and other Rhino assemblies from where Rhino is installed
    /// </summary>
    /// <param name="rhinoPath">Rhino installation path (e.g. 'C:/Program Files/Rhino 8' or '/Application/Rhino 8.app')</param>
    /// <exception cref="RhinoInsideInitializationException">Error occured during initialization.</exception>
    public static void Initialize(string rhinoPath)
    {
      if (s_initialized)
        throw new RhinoInsideInitializationException($"{typeof(Resolver).Assembly.GetName().Name} is already initialized");

      if (System.IntPtr.Size != 8)
        throw new RhinoInsideInitializationException("Only 64 bit applications can use RhinoInside");

      RhinoSystemDirectory = RhinoFinder.PrepareSystemPath(rhinoPath);
      PrepareRhinoEnv();
      s_initialized = true;
    }

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)] delegate void SetLoaderProc(Action p);
    static void PrepareRhinoEnv()
    {
      AppDomain.CurrentDomain.AssemblyResolve += ResolveForRhinoAssemblies;

      SetupXamarin();
      SetupDefaultResolver();

      nint rhinoLibraryHandle = 0;
      if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        rhinoLibraryHandle = NativeLibrary.Load(Path.Combine(RhinoSystemDirectory, "RhinoLibrary.dll"));
      }
      else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        rhinoLibraryHandle = NativeLibrary.Load(Path.Combine(RhinoSystemDirectory, "RhinoLibrary.framework/Versions/A/RhinoLibrary"));
        AssemblyLoadContext.Default.ResolvingUnmanagedDll += ResolvingUnmanagedDll;
      }
      else
        throw new RhinoInsideInitializationException($"Unsupported platform");

      try
      {
        IntPtr handle = NativeLibrary.GetExport(rhinoLibraryHandle, "RhLibRegisterDotNetInitializer");

        GCHandle loaderProcHandle = default;
        Action loaderProc = () =>
        {
          ExecuteLoadProc(AssemblyLoadContext.Default);
          loaderProcHandle.Free();
        };
        loaderProcHandle = GCHandle.Alloc(loaderProc);

        var setLoaderProc = Marshal.GetDelegateForFunctionPointer<SetLoaderProc>(handle);
        setLoaderProc(loaderProc);
      }
      catch (TypeInitializationException typeInitEx)
      {
        throw new RhinoInsideInitializationException($"Unsupported Rhino version", typeInitEx);
      }
      catch (Exception loadEx)
      {
        throw new RhinoInsideInitializationException($"Initialization error: {loadEx.Message} ", loadEx);
      }
    }

    static Assembly ResolveForRhinoAssemblies(object sender, ResolveEventArgs args)
    {
      string path = AssemblyPathFromName(args.Name);
      if (File.Exists(path))
        return Assembly.LoadFrom(path);
      return default;
    }

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)] delegate int GetCLRRuntimeHost(ref Guid ptr, out IntPtr handle);
    static void SetupXamarin()
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        var libCoreClr = NativeLibrary.Load("libcoreclr.dylib");
        var getClrRuntimeHostPtr = NativeLibrary.GetExport(libCoreClr, "GetCLRRuntimeHost");
        var getClrRuntimeHost = Marshal.GetDelegateForFunctionPointer<GetCLRRuntimeHost>(getClrRuntimeHostPtr);
        // var hostId = new Guid(0x90F1A06C, 0x7712, 0x4762, 0x86, 0xB5, 0x7A, 0x5E, 0xBA, 0x6B, 0xDB, 0x02);
        var hostId4 = new Guid(0x64F6D366, 0xD7C2, 0x4F1F, 0xB4, 0xB2, 0xE8, 0x16, 0x0C, 0xAC, 0x43, 0xAF);
        var result = getClrRuntimeHost(ref hostId4, out var coreclr_handle);
        if (result != 0 || coreclr_handle == IntPtr.Zero)
          throw new InvalidOperationException("Could not get CLR Runtime Host");

        // set handle/domain id for xamarin.mac to use
        var libXamarin = NativeLibrary.Load(Path.Combine(RhinoSystemDirectory, "libxamarin-dotnet-coreclr.dylib"));
        var coreClrHandlePtr = NativeLibrary.GetExport(libXamarin, "coreclr_handle");
        var coreClrDomainIdPtr = NativeLibrary.GetExport(libXamarin, "coreclr_domainId");
        Marshal.WriteIntPtr(coreClrHandlePtr, coreclr_handle);
        Marshal.WriteInt32(coreClrDomainIdPtr, AppDomain.CurrentDomain.Id);
      }
    }

    static void SetupDefaultResolver()
    {
      AssemblyLoadContext.Default.Resolving += (ctx, arg) =>
      {
        string path = AssemblyPathFromName(arg.Name);
        if (File.Exists(path))
          return ctx.LoadFromAssemblyPath(path);

        return default;
      };
    }

    static IntPtr ResolvingUnmanagedDll(Assembly assembly, string unmanagedDllName)
    {
      if (unmanagedDllName == "RhinoLibrary")
        return NativeLibrary.Load(Path.Combine(RhinoSystemDirectory, "RhinoLibrary.framework/Versions/A/RhinoLibrary"));

      return IntPtr.Zero;
    }

    static string AssemblyPathFromName(string name)
    {
      if (name == null || name.EndsWith(".resources", StringComparison.OrdinalIgnoreCase))
        return default;

      // load Microsoft.macOS in the default context as xamarin initialization requires it there
      if (name == "Microsoft.macOS")
        return default;

      // only use the plain name to resolve assemblies, not the full name.
      name = new AssemblyName(name).Name;

      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        return Path.Combine(RhinoSystemDirectory, "RhCore.framework/Resources", name + ".dll");
      }
      else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        if (Path.Combine(RhinoSystemDirectory, "netcore", name + ".dll") is string netcorePath
              && File.Exists(netcorePath))
        {
          return netcorePath;
        }

        return Path.Combine(RhinoSystemDirectory, name + ".dll");
      }

      return default;
    }

    static void ExecuteLoadProc(AssemblyLoadContext context)
    {
      var assembly = context.LoadFromAssemblyName(new AssemblyName("dotnetstart"));
      var programType = assembly?.GetType("dotnetstart.DotNetInitialization");
      var method = programType?.GetMethod("Start");
      method?.Invoke(null, new object[] { "headless" });
    }
  }
}
