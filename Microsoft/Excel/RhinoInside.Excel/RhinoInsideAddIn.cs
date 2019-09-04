using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Reflection;
using System.IO;

using Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;

using Rhino.Runtime.InProcess;

namespace RhinoInside.Excel

{
    public partial class RhinoInsideAddIn
    {
        Rhino.Runtime.InProcess.RhinoCore m_rhino_core;

        #region Plugin static constructor

        static RhinoInsideAddIn()
        {

            ResolveEventHandler OnRhinoCommonResolve = null;
            AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
            {
                const string rhino_common_assembly_name = "RhinoCommon";
                var assembly_name = new AssemblyName(args.Name).Name;

                if (assembly_name != rhino_common_assembly_name)
                    return null;

                AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

                var rhino_system_dir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
                return Assembly.LoadFrom(Path.Combine(rhino_system_dir, rhino_common_assembly_name + ".dll"));
            };
        }

        #endregion // Plugin static constructor

        //The Startup event is raised after the VSTO Add-in is loaded
        //and all the initialization code in the assembly has been run. 
        private void ThisAddIn_Startup(object sender, System.EventArgs e)
        {
            // Load Rhino
            try
            {


                //TODO >> grab Excel product name for scheme
                var scheme_name = "RhinoInsideExcel";


                //Run Rhino.Inside no UI
                m_rhino_core = new Rhino.Runtime.InProcess.RhinoCore(new[] { $"/scheme={scheme_name}" });

                //TODO >> Run Rhino.Inside with UI - Error -200
                //m_rhino_core = new Rhino.Runtime.InProcess.RhinoCore(new[] { $"/scheme={scheme_name}" }, WindowStyle.Maximized);


            }
            catch (Exception ex)
            {
                //System.Windows.Forms.MessageBox.Show(ex.Message);
                System.Windows.Forms.MessageBox.Show("Cannot load Rhino Inside Addin");

            }
        }

        private void ThisAddIn_Shutdown(object sender, System.EventArgs e)
        {
            try
            {
                m_rhino_core?.Dispose();
            }
            catch
            {
                // ignored
            }
        }




        #region VSTO generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InternalStartup()
        {
            this.Startup += new System.EventHandler(ThisAddIn_Startup);
            this.Shutdown += new System.EventHandler(ThisAddIn_Shutdown);
        }
        
        #endregion
    }
}
