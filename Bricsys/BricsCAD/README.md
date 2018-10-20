# Rhino Inside BricsCAD
This folder contains the BricsCAD sample project.
## Getting started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes
### Prerequisites
1. GIT client ([download](https://git-scm.com/downloads))
2. Visual Studio 2017 ([download](https://visualstudio.microsoft.com/downloads/))
3. Rhino WIP ([download](https://www.rhino3d.com/download/rhino/wip))
4. Bricssys BricsCAD V18 ([download](https://www.bricsys.com/en-intl/))

### Getting Source & Build
1. Clone the repository. At the command prompt, enter the following command:
```
git clone --recursive https://github.com/mcneel/rhino.inside.git rhino.inside
```
2. In Visual Studio: open _rhino.inside\Bricssys\BricsCAD\RhinoInside.BricsCAD.sln_.
3. Set the solution configuration according the BricsCAD version you have installed.
4. Navigate to _Build_ > _Build Solution_ to begin your build.

### Installing & Uninstalling
Launch AutoCAD and run the `NETLOAD` command to load the .NET application.

## Using the sample
1. Launch BricsCAD V18.
2. Start a new drawing.
3. Run the `NETLOAD` command to load the .NET application.
4. Navigate to the project output folder and select the _RhinoInside.BricsCAD.dll_ file.
5. Run the `TestRhinoInside` command.

