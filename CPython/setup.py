import setuptools

# read the contents of your README file
from os import path
this_directory = path.abspath(path.dirname(__file__))
with open(path.join(this_directory, 'README.md')) as f:
    long_description = f.read()

setuptools.setup(
    name="rhinoinside",
    version="0.1.0",
    packages=['rhinoinside'],
    author="Robert McNeel & Associates",
    author_email="steve@mcneel.com",
    description="Embed Rhino in CPython",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/mcneel/rhino.inside/CPython",
    install_requires=['pythonnet'],
    include_package_data = True,
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Microsoft :: Windows",
        "Programming Language :: Python"
    ],
)
