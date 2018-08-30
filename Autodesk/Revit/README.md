# Rhino Inside Revit
This folder contains the Revit sample project.
## Getting started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes
### Prerequisites
1. Git client. ([download](https://git-scm.com/downloads))
2. Visual Studio 2017 ([download](https://visualstudio.microsoft.com/downloads/))
3. Rhino WIP ([download](https://www.rhino3d.com/download/rhino/wip))
4. Autodesk Revit 2017-2019 ([download](https://www.autodesk.com/products/revit/free-trial))

### Getting Source & Build
1. Clone the repository. At the command prompt, enter the following command:
```
git clone --recursive https://github.com/mcneel/rhino.inside.git rhino.inside
```
2. In Visual Studio: open _rhino.inside\Autodesk\Revit\RhinoInside.Revit.sln_.
3. Set the solution configuration acording the Revit version you have installed.
4. Navigate to _Build_ > _Build Solution_ to begin your build.

### Installing & Uninstalling
The project is configured to copy .addon file as well as output files to the folder _"%APPDATA%\\Autodesk\\Revit\\Addins\\%RevitVer%\\RhinoInside.Revit\\"_ folder in order to make Revit load this addon next time it runs.

In order to uninstall it you can use Visual Studio _Build_ > _Clean Solution_ command or just navigate to the folder _"%APPDATA%\\Autodesk\\Revit\\Addins\\%RevitVer%\\_ and remove the file _RhinoInside.Revit.addon_ and the folder _RhinoInside.Revit_.

## Using the sample
1. Once you launch Revit it will warn you this addon is not verified, please click on "Load allways" or "Load once".
2. Create a new project or open an existing one.
3. Open the ribbon tab called _Add-Ins_.
4. Click on the button you will found on the _Rhinoceros_ panel called _Sample 1_.
