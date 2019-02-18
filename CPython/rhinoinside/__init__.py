import os, clr, sys

# Adding to sys.path will make pythonnet find the
# appropriate DLLs to load
__path_to_rhino = os.path.join(os.environ["ProgramFiles"], "Rhino WIP", "System")
sys.path.append(__path_to_rhino)

# we shouldn't need this shim, but David Leon was seeing
# problems loading directly through RhinoCommon's RhinoCore
# class. We'll use the shim for now, and over time we can
# switch over to just constructing a RhinoCore class instance
__path_to_dll = os.path.join(os.path.dirname(os.path.abspath(__file__)), "RhinoInsidePythonShim.dll")  
clr.AddReference(__path_to_dll)

import RhinoInsidePythonShim
RhinoInsidePythonShim.RhinoLib.Init()
RhinoInsidePythonShim.RhinoLib.Launch()

clr.AddReference("RhinoCommon")

# create and hold onto an instance of RhinoCore to properly
# launch Rhino.Inside of python
import Rhino

# uncomment when we get RhinoCore working
#rhinocore = Rhino.Runtime.InProcess.RhinoCore()
