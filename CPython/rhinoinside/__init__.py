import os, clr, sys

# Adding to sys.path will make pythonnet find the
# appropriate DLLs to load
__path_to_rhino = os.path.join(os.environ["ProgramFiles"], "Rhino WIP", "System")
sys.path.append(__path_to_rhino)

clr.AddReference("RhinoCommon")

# create and hold onto an instance of RhinoCore to properly
# launch Rhino.Inside of python
import Rhino
rhinocore = Rhino.Runtime.InProcess.RhinoCore()
