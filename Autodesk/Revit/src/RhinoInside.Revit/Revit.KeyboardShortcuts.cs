using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Rhino;

using Autodesk.Revit.DB;
using System.IO;
using System.Xml.Serialization;

namespace RhinoInside.Revit
{
  public partial class Revit
  {
    public static class KeyboardShortcuts
    {
      [Serializable()]
      public class ShortcutItem
      {
        [XmlAttribute()] public string CommandName { get; set; }
        [XmlAttribute()] public string CommandId   { get; set; }
        [XmlAttribute()] public string Shortcuts   { get; set; }
        [XmlAttribute()] public string Paths       { get; set; }
      }

      [Serializable(), XmlRoot("Shortcuts", Namespace = "")]
      public class Shortcuts : List<ShortcutItem> { }

      internal static bool LoadFrom(string keyboardShortcutsPath, out Shortcuts shortcuts)
      {
        try
        {
          using (var ReadFileStream = new FileStream(keyboardShortcutsPath, FileMode.Open, FileAccess.Read, FileShare.Read))
          {
            var serializer = new XmlSerializer(typeof(Shortcuts));
            shortcuts = serializer.Deserialize(ReadFileStream) as Shortcuts;
            return true;
          }
        }
        catch (FileNotFoundException)
        {
          shortcuts = null;
          return false;
        }
      }

      internal static bool SaveAs(Shortcuts shortcuts, string keyboardShortcutsPath)
      {
        try
        {
          using (var WriteFileStream = new StreamWriter(keyboardShortcutsPath))
          {
            var ns = new XmlSerializerNamespaces();
            ns.Add(string.Empty, string.Empty);

            var serializer = new XmlSerializer(typeof(Shortcuts));
            serializer.Serialize(WriteFileStream, shortcuts, ns);
            return true;
          }
        }
        catch (Exception)
        {
          return false;
        }
      }
    }
  }
}
