using System;
using System.IO;
using System.Reflection;
using System.Runtime.Loader;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Collections.Concurrent;

namespace RhinoInside
{
  public static class Resolver
  {
    static readonly ConcurrentDictionary<string, IntPtr> s_nativeCache = new();
    static AssemblyLoadContext s_context;
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
      SetupXamarin();

      nint rhinoLibraryHandle = 0;
      if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        rhinoLibraryHandle = NativeLibrary.Load(Path.Combine(RhinoSystemDirectory, "RhinoLibrary.dll"));
      }
      else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        rhinoLibraryHandle = NativeLibrary.Load(Path.Combine(RhinoSystemDirectory, "RhinoLibrary.framework/Versions/A/RhinoLibrary"));
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

      s_context = AssemblyLoadContext.GetLoadContext(typeof(Resolver).Assembly);
      s_context.ResolvingUnmanagedDll += NativeAssemblyResolve;
      s_context.Resolving += ManagedAssemblyResolve;

      AppDomain.CurrentDomain.AssemblyLoad += ManagedAssemblyLoaded;
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

    static void ExecuteLoadProc(AssemblyLoadContext context)
    {
      int dotnetMajor = Environment.Version.Major;
      TryGetAssemblyPathFromName($"dotnetstart.{dotnetMajor}", out string dotnetstartLib);
      var assembly = context.LoadFromAssemblyPath(dotnetstartLib);
      var programType = assembly?.GetType("dotnetstart.DotNetInitialization");
      var method = programType?.GetMethod("Start");
      method?.Invoke(null, new object[] { "headless" });
    }

    static void ManagedAssemblyLoaded(object sender, AssemblyLoadEventArgs args)
    {
      var assembly = args.LoadedAssembly;

      if (assembly.IsDynamic
              || AssemblyLoadContext.GetLoadContext(assembly) == s_context)
      {
        return;
      }

      NativeLibrary.SetDllImportResolver(assembly, NativeAssemblyResolve);
    }

    static IntPtr NativeAssemblyResolve(string libname, Assembly assembly, DllImportSearchPath? searchPath)
    {
      if (s_nativeCache.TryGetValue(libname, out var ptr))
      {
        return ptr;
      }

      foreach (string path in new List<string>
      {
          assembly.Location,
          Path.Combine(RhinoSystemDirectory, "netcore"),
          RhinoSystemDirectory,
      })
      {
        var file = Path.Combine(path, libname + ".dll");
        if (File.Exists(file))
        {
          ptr = NativeLibrary.Load(file);
          s_nativeCache[libname] = ptr;
          return ptr;
        }
      }

      s_nativeCache[libname] = IntPtr.Zero;
      return IntPtr.Zero;
    }

    static IntPtr NativeAssemblyResolve(Assembly assembly, string name)
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        if (!string.IsNullOrEmpty(name) && name == "RhinoLibrary")
          return NativeLibrary.Load(Path.Combine(RhinoSystemDirectory, "RhinoLibrary.framework/Versions/A/RhinoLibrary"));
      }

      return IntPtr.Zero;
    }

    static Assembly ManagedAssemblyResolve(AssemblyLoadContext arg1, AssemblyName assemblyName)
    {
      string name = assemblyName.Name;

      if (string.IsNullOrEmpty(name) || name.EndsWith(".resources", StringComparison.OrdinalIgnoreCase))
      {
        return default;
      }

      // load Microsoft.macOS in the default context as xamarin initialization requires it there
      if (name == "Microsoft.macOS")
      {
        return default;
      }

      if (TryGetAssemblyPathFromName(name, out var path))
      {
        return arg1.LoadFromAssemblyPath(path);
      }

      return default;
    }

    static bool TryGetAssemblyPathFromName(string name, out string file)
    {
      file = default;

      foreach (string path in GetSearchPaths())
        if (TryGetAssemblyPathFromName(path, name, out string f))
        {
          file = f;
          return true;
        }

      return false;
    }

    static bool TryGetAssemblyPathFromName(string path, string name, out string file)
    {
      file = default;

      string f = Path.Combine(path, name + ".dll");
      if (File.Exists(f))
      {
        file = f;
        return true;
      }

      f = Path.ChangeExtension(f, ".rhp");
      if (File.Exists(f))
      {
        file = f;
        return true;
      }

      f = Path.ChangeExtension(f, ".gha");
      if (File.Exists(f))
      {
        file = f;
        return true;
      }

      return false;
    }

    static IEnumerable<string> GetSearchPaths()
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        yield return Path.Combine(RhinoSystemDirectory, "RhCore.framework/Resources");
      }
      else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        yield return Path.Combine(RhinoSystemDirectory, "netcore");
        yield return Path.Combine(RhinoSystemDirectory);
      }

      foreach (var path in GetPluginSearchPaths())
      {
        yield return path;

        // Grasshopper.dll is here
        yield return Path.Combine(path, @"Grasshopper");

        // RhinoCodePluginGH is here
        yield return Path.Combine(path, @"Grasshopper\Components");
      }

      yield return Path.GetDirectoryName(typeof(Resolver).Assembly.Location);
    }

    static IEnumerable<string> GetPluginSearchPaths()
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        const string MANAGED_PLUGINS = "RhCore.framework/Versions/A/Resources/ManagedPlugIns";
        yield return Path.Combine(RhinoSystemDirectory, MANAGED_PLUGINS);
      }
      else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        const string PLUGINS = "Plug-ins";
        yield return Path.Combine(RhinoSystemDirectory, PLUGINS);
        yield return Path.Combine(Path.GetDirectoryName(RhinoSystemDirectory), PLUGINS);
      }
    }
  }
}
