import os
import clr
import sys
import struct

# Adding to sys.path will make pythonnet find the
# appropriate DLLs to load
__path_to_rhino = os.path.join(os.environ["ProgramFiles"], "Rhino WIP", "System")
sys.path.append(__path_to_rhino)

# create and hold onto an instance of RhinoCore to properly
# launch Rhino.Inside of python
__rhino_core = None


def load():
    """call load to actually load Rhino into the current process"""
    if os.name != 'nt':
        raise Exception('rhinoinside only works on Windows')
    bitness = 8 * struct.calcsize("P")
    if bitness != 64:
        raise Exception('rhinoinside only works in a 64 bit process')

    global __rhino_core
    if __rhino_core is None:
        clr.AddReference("RhinoCommon")
        import Rhino
        __rhino_core = Rhino.Runtime.InProcess.RhinoCore()
