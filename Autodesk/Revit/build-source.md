# Build RhinoInside Revit from source
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites
* Git ([download](https://git-scm.com/downloads))
* Visual Studio 2017 (15.9 or above) ([download](https://visualstudio.microsoft.com/downloads/))
* .NET Framework 4.7 ([download](https://www.microsoft.com/net/download/visual-studio-sdks))
* Rhino WIP ([download](https://www.rhino3d.com/download/rhino/wip))
* Autodesk Revit 2017-2019 ([download](https://www.autodesk.com/products/revit/free-trial))
* Add this link to your bookmarks ;) ([API docs](https://www.apidocs.co/apps/))

### Getting Source & Build
1. Clone the repository. At the command prompt, enter the following command:
```
git clone --recursive https://github.com/mcneel/rhino.inside.git rhino.inside
```
2. In Visual Studio: open _rhino.inside\Autodesk\Revit\RhinoInside.Revit.sln_.
3. Set the Solution Configuration drop-down according the Revit version you have installed. This will properly link the correct Revit API libraries to the project.
4. Navigate to _Build_ > _Build Solution_ to begin your build.

## Installing & Uninstalling
The project is configured to copy .addon file as well as output files to the folder _"%APPDATA%\\Autodesk\\Revit\\Addins\\%RevitVer%\\RhinoInside.Revit\\"_ folder in order to make Revit load this addon next time it runs.

In order to uninstall it you can use Visual Studio _Build_ > _Clean Solution_ command or just navigate to the folder _"%APPDATA%\\Autodesk\\Revit\\Addins\\%RevitVer%\\_ and remove the file _RhinoInside.Revit.addon_ and the folder _RhinoInside.Revit_.
