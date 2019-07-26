# Rhino Inside Node.js
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.

## Sample 4
This sample shows how to run Rhino from `Electron`.
This sample extends Sample 1, 2, and 3 by using Electron for UI. Geometry rendered with [three.js](https://threejs.org).
The sample has been tested on Windows 10, Rhino 7 WIP, and Node.js 8.11.12 (though should work on more recent versions of Node.js)

There are three projects in this sample:
- `InsideElectron` - Compiles to a .net framework class library with two classes and several methods. This class contains the code to start Rhino and Grasshopper, as well as a custom TaskScheduler.
- `TestInsideElectron` - A small project to test the TaskScheduler class to control Rhino.
- `InsideElectronApp` - The Electron app that provides a GUI and launches Rhino and Grasshopper from JavaScript.

### Dependencies
- Rhino WIP (7.0.19127.235, 5/7/2019)
- Node.js (8.11.2)
- edge.js (^11.3.1)
- Electron
- Three.js
- rhino3dm.js
- Json.Net

### Running this sample
This assumes you've installed Node.js for Windows.
1. Open the `InsideElectron.sln` in Visual Studio and build the solution. This builds the .dll which is referenced in the Electron app. Note: You might need to Clean dna Rebuild the InsideElectron.csproj to get NuGet to restore the Json.Net package.
2. Open a console from the `InsideElectronApp` directory.
3. Run `npm install` to install any dependencies.
4. Run `npm start` to run the sample. You should see the Electron window appear, followed by the Grasshopper editor.
5. In the Grasshopper editor, add a Mesh > Primitive > MeshSphere component to the Grasshopper Canvas. You should see someting like this:
![](Rhino.Inside.JavaScript_Sample-4_sphere.png)
As you continue to develop the definition, the rendered geometry will update to reflect what you have defined in the Grasshopper canvas:
![](Rhino.Inside.JavaScript_Sample-4.png)

