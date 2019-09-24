import setuptools
import os
import struct
import distutils.command.install
from os import path


# read the contents of your README file
this_directory = path.abspath(path.dirname(__file__))
long_description = ""
with open(path.join(this_directory, 'README.md')) as f:
    long_description = f.read()


setuptools.setup(
    name="rhinoinside",
    version="0.4.3",
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
    ]
)
