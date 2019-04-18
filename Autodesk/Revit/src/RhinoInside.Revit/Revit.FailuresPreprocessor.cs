using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Rhino;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit
{
  public partial class Revit
  {
    class FailuresPreprocessor : IFailuresPreprocessor
    {
      public FailureProcessingResult PreprocessFailures(FailuresAccessor failuresAccessor)
      {
        var severity = failuresAccessor.GetSeverity();
        if (severity == FailureSeverity.Warning)
        {
          foreach (var warning in failuresAccessor.GetFailureMessages(FailureSeverity.Warning))
            RhinoApp.WriteLine(warning.GetDescriptionText());

          failuresAccessor.DeleteAllWarnings();
          return FailureProcessingResult.ProceedWithCommit;
        }

        return FailureProcessingResult.Continue;
      }
    }
  }
}
