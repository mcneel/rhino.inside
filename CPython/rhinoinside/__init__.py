import os
import clr
import sys
import struct


# create and hold onto an instance of RhinoCore to properly
# launch Rhino.Inside of python
__rhino_core = None
__load_called = False

def load(rhino_dir = None):
    """
    Load Rhino into the python process
    :param rhino_dir: optional path to directory where Rhino is installed
    :return:
    """
    global __load_called
    if __load_called:
        return
    __load_called = True

    # Adding to sys.path will make pythonnet find the
    # appropriate DLLs to load
    if rhino_dir is None:
        rhino_dir = os.path.join(os.environ["ProgramFiles"], "Rhino WIP", "System")
    sys.path.append(rhino_dir)

    """call load to load RhinoCore.DLL into the current process"""
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
