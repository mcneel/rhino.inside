using System;
using System.Runtime.InteropServices;

class RhinoLib
{
    public enum LoadMode : int
    {
        Headless = 0,
        FullUserInterface = 1
    }
    static RhinoLib()
    {
        Init();
    }

    private static bool _pathsSet = false;
    public static string _rhpath;
    public static void Init()
    {
        if (!_pathsSet)
        {
            string envPath = Environment.GetEnvironmentVariable("path");

            // Add Rhino WIP to the path.
            string programFiles = Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles);
            string rhinoSystemDir = System.IO.Path.Combine(programFiles, "Rhino WIP", "System");

            Environment.SetEnvironmentVariable("path", envPath + ";" + rhinoSystemDir);
            _pathsSet = true;
            _rhpath = rhinoSystemDir;
            _rhinocommon = System.Reflection.Assembly.LoadFrom(System.IO.Path.Combine(rhinoSystemDir, "RhinoCommon.dll"));
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
        }
    }

    static System.Reflection.Assembly _rhinocommon;
    private static System.Reflection.Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
    {
        if (args.Name.Contains("RhinoCommon"))
            return _rhinocommon;
        return null;
    }

    [DllImport("RhinoLibrary.dll")]
    internal static extern int LaunchInProcess(LoadMode mode, int reserved2);

    [DllImport("RhinoLibrary.dll")]
    internal static extern int ExitInProcess();
}
