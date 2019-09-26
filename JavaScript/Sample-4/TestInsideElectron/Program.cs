using System;

namespace TestInsideElectron
{
  class Program
  {
    static void Main(string[] args)
    {
      Console.WriteLine("Hello World!");
      var rhinoTaskManager = new InsideElectron.RhinoInsideTaskManager();
      //rhinoTaskManager.StartRhinoTask(null);
      rhinoTaskManager.StartGrasshopperTask(null);
      rhinoTaskManager.DoSomethingTask(null);
    }
  }
}
