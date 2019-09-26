namespace RhinoInside.Excel
{
    partial class Ribbon1 : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public Ribbon1()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Ribbon1));
            this.tab1 = this.Factory.CreateRibbonTab();
            this.RhinoInside = this.Factory.CreateRibbonGroup();
            this.test01 = this.Factory.CreateRibbonButton();
            this.tab1.SuspendLayout();
            this.RhinoInside.SuspendLayout();
            this.SuspendLayout();
            // 
            // tab1
            // 
            this.tab1.ControlId.ControlIdType = Microsoft.Office.Tools.Ribbon.RibbonControlIdType.Office;
            this.tab1.Groups.Add(this.RhinoInside);
            this.tab1.Label = "TabAddIns";
            this.tab1.Name = "tab1";
            // 
            // RhinoInside
            // 
            this.RhinoInside.Items.Add(this.test01);
            this.RhinoInside.Label = "Rhino Inside";
            this.RhinoInside.Name = "RhinoInside";
            // 
            // test01
            // 
            this.test01.Image = ((System.Drawing.Image)(resources.GetObject("test01.Image")));
            this.test01.Label = "test01";
            this.test01.Name = "test01";
            this.test01.ShowImage = true;
            this.test01.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.test01_click);
            // 
            // Ribbon1
            // 
            this.Name = "Ribbon1";
            this.RibbonType = "Microsoft.Excel.Workbook";
            this.Tabs.Add(this.tab1);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.Ribbon1_Load);
            this.tab1.ResumeLayout(false);
            this.tab1.PerformLayout();
            this.RhinoInside.ResumeLayout(false);
            this.RhinoInside.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab tab1;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup RhinoInside;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton test01;
    }

    partial class ThisRibbonCollection
    {
        internal Ribbon1 Ribbon1
        {
            get { return this.GetRibbon<Ribbon1>(); }
        }
    }
}
