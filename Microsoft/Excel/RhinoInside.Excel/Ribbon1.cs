using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Office.Tools.Ribbon;

using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;

using Rhino.Geometry;

namespace RhinoInside.Excel
{
    public partial class Ribbon1
    {
        private void Ribbon1_Load(object sender, RibbonUIEventArgs e)
        {

        }

        private void test01_click(object sender, RibbonControlEventArgs e)
        {

            //Open Excel Worksheet
            Microsoft.Office.Interop.Excel.Worksheet activeWorksheet = Globals.RhinoInsideAddIn.Application.ActiveSheet;


            try
            {
                var sphere = new Sphere(Point3d.Origin, 12);
                var brep = sphere.ToBrep();
                var mp = new MeshingParameters(0.5);
                var mesh = Mesh.CreateFromBrep(brep, mp);
                System.Windows.Forms.MessageBox.Show($"Mesh with {mesh[0].Vertices.Count} vertices created");


            }
            catch (Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message);
            }

        }
    }
}
