# Rhino Inside

[![Discourse users](https://img.shields.io/discourse/https/discourse.mcneel.com/users.svg)](https://discourse.mcneel.com/c/serengeti/inside)


The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.  It may be possible to:

* Starting Rhino and Grasshopper as an add in another product.
* Call directly into the host's native APIs from a Grasshopper or Rhino plugin.
* Access Rhino's APIs through the host application.
* Grasshopper definitions can be opened and previewed in Rhino within the same process as the parent.
* Object can be natively created by Rhino or Grasshopper within the parent product.

![sample-shot](Autodesk/Revit/doc/images/Sample5.gif)

This repository contains all the sample developer code for loading Rhino inside other 64-bit Windows applications.

The version of Rhino that these samples are compatible with is the Rhino WIP version that you can found [here](https://www.rhino3d.com/download/rhino/wip) .

## Samples by host application.
The samples in this repository are organized by folders that correspond to the Company\Product name of the host application where you can found more information.

This repository contains samples for:
- [Autodesk](Autodesk)
   - [AutoCAD](Autodesk/AutoCAD)
   - [Revit](Autodesk/Revit)
- [Bricsys](Bricsys)
   - [BricsCAD](Bricsys/BricsCAD)
- [Unity](Unity)
   - [How to use compute.rhino3d with Unity](https://youtu.be/zUbm83ynn0Q)
- [Console](ConsoleApps)
   - [A simple console application](ConsoleApps/HelloWorld)
   - [A simple console application for converting files to .obj](ConsoleApps/Convert)
- [JavaScript](JavaScript)
   - [Sample 1](JavaScript/Sample-1) A basic example showing how to run Rhino inside of Node.js via edge.js.
   - [Sample 2](JavaScript/Sample-2) Extends Sample-1.
   - [Sample 3](JavaScript/Sample-3) Sample of running Rhino inside Electron.
   - [Sample 4](JavaScript/Sample-4) Sample of running Grasshopper inside Electron.
   - [Sample 5](JavaScript/Sample-5) Sample of running Grasshopper inside Chromium Embedded Framework.

**If you have any questions, [visit the discussion forum...](https://discourse.mcneel.com/c/serengeti/inside)**
