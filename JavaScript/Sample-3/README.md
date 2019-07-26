# Rhino Inside Node.js
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.

## Sample 3
This sample shows how to run Rhino from `Electron`.
This sample extends Sample 1 and 2 by using Electron for UI. Geometry rendered with [three.js](https://threejs.org).
The sample has been tested on Windows 10, Rhino 7 WIP, and Node.js 8.11.12 (though should work on more recent versions of Node.js)

There are two projects in this sample:
- `InsideElectron.csproj` - Compiles to a .net Core 2.0 class library with one class and several methods. This class contains the code to start Rhino.
- `InsideElectronApp` - The Electron app that provides a GUI and launches Rhino and Grasshopper from JavaScript.

### Dependencies
- Rhino WIP (7.0.19127.235, 5/7/2019)
- Node.js (8.11.2)
- edge.js (^11.3.1)
- Electron
- Three.js
- rhino3dm.js

### Running this sample
This assumes you've installed Node.js for Windows.
1. Open a console from the `InsideElectronApp` directory.
2. Run `npm install` to install any dependencies.
3. Open the `InsideElectron.sln` in Visual Studio and build the solution. This builds the .dll which is referenced in the Electron app.
4. Run `npm start` to run the sample. You should see:
![](Rhino.Inside.JavaScript_Sample-3.png)

