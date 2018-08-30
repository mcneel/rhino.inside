# Rhino Inside AutoCAD
This folder contains the AutoCAD sample project.
## Getting started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes
### Prerequisites
1. GIT client ([download](https://git-scm.com/downloads))
2. Visual Studio 2017 ([download](https://visualstudio.microsoft.com/downloads/))
3. Rhino WIP ([download](https://www.rhino3d.com/download/rhino/wip))
4. Autodesk AutoCAD 2019 ([download](https://www.autodesk.com/products/autocad/free-trial))

### Getting Source & Build
1. Clone the repository. At the command prompt, enter the following command:
```
git clone --recursive https://github.com/mcneel/rhino.inside.git rhino.inside
```
2. In Visual Studio: open _rhino.inside\Autodesk\AutoCAD\RhinoInside.AutoCAD.sln_.
3. Set the solution configuration acording the AutoCAD version you have installed.
4. Navigate to _Build_ > _Build Solution_ to begin your build.

### Installing & Uninstalling
Launch AutoCAD and run the `NETLOAD` command to load the .NET application.

## Using the sample
1. Launch AutoCAD 2019.
2. Start a new drawing.
3. Run the `NETLOAD` command to load the .NET application.
4. Navigate to the project output folder and select the _RhinoInside.AutoCAD.dll_ file.
5. AutoCAD will warn you this add-on is not verified. Please click on `Load always` or `Load once`.
6. Run the `TestRhinoInside` command.

