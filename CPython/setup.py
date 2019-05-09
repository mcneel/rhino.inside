import setuptools
import os
import struct
import distutils.command.install


class _CustomInstall(distutils.command.install.install):
    def run(self):
        if os.name != 'nt':
            raise SystemError('rhinoinside only works on Windows')
        bitness = 8 * struct.calcsize("P")
        if bitness != 64:
            raise SystemError('rhinoinside only works in a 64 bit process')
        distutils.command.install.install.run(self)

# read the contents of your README file
from os import path
this_directory = path.abspath(path.dirname(__file__))
with open(path.join(this_directory, 'README.md')) as f:
    long_description = f.read()

setuptools.setup(
    name="rhinoinside",
    version="0.3.0",
    packages=['rhinoinside'],
    author="Robert McNeel & Associates",
    author_email="steve@mcneel.com",
    description="Embed Rhino in CPython",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/mcneel/rhino.inside/tree/master/CPython",
    install_requires=['pythonnet'],
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Microsoft :: Windows",
        "Programming Language :: Python"
    ],
    cmdclass={ 'install': _CustomInstall }
)
