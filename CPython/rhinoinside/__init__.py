import os
import clr
import struct


# create and hold onto an instance of RhinoCore to properly
# launch Rhino.Inside of python
__rhino_core = None
__load_called = False


def load(rhino_dir=None):
    """
    Load Rhino into the python process
    :param rhino_dir: optional path to directory where Rhino is installed
    :return:
    """
    global __load_called
    if __load_called:
        return
    __load_called = True

    if os.name != 'nt':
        raise Exception('rhinoinside only works on Windows')
    bitness = 8 * struct.calcsize("P")
    if bitness != 64:
        raise Exception('rhinoinside only works in a 64 bit process')

    global __rhino_core
    if __rhino_core is None:
        path_to_this = os.path.abspath(__file__)
        dir_name = os.path.dirname(path_to_this)
        resolver_dll = os.path.join(dir_name, "RhinoInside.dll")
        clr.AddReference(resolver_dll)
        import RhinoInside
        RhinoInside.Resolver.Initialize()
        if rhino_dir:
            RhinoInside.Resolver.RhinoSystemDirectory = rhino_dir
        clr.AddReference("RhinoCommon")
        import Rhino
        __rhino_core = Rhino.Runtime.InProcess.RhinoCore()
