using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InsideElectron
{
  
  public class RhinoMethods
  {
    static RhinoInsideTaskManager rhinoInsideTaskManager;
    static RhinoMethods()
    {
      rhinoInsideTaskManager = new RhinoInsideTaskManager();
    }

    public async Task<object> StartRhino(dynamic input)
    {
      return await rhinoInsideTaskManager.StartRhinoTask(input);
    }

    public async Task<object> StartGrasshopper(dynamic input)
    {
      return await rhinoInsideTaskManager.StartGrasshopperTask(input);
    }

    public async Task<object> DoSomething(dynamic input)
    {
      return await rhinoInsideTaskManager.DoSomethingTask(input);
    }
  }
}
