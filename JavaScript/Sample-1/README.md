# Rhino Inside Node.js
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.

## Sample 1
This sample shows how to start Rhino from Node.js.  The JavaScript code calls into a .NET dll which launches Rhino, creates some geometry, and returns information related to that geometry. This information is then passed back to JavaScript and is printed to the console.
The sample has been tested on Windows 10, Rhino 7 WIP, and Node.js 8.11.12 (though should work on more recent versions of Node.js)

There are two projects:
- `insideNode.csproj` - Compiles to a .net class library with one class and one method. This class contains the code to start Rhino.
- `insideNodeApp` - Contains the Node.js code which calls the dotnet class library. Uses [edge.js](https://github.com/agracio/edge-js) to call into dotnet.

### Dependencies
- [`Rhino 7 WIP`](https://www.rhino3d.com/download/rhino-for-windows/wip) (Required install)
- [`Node.js (8.11.2 or newer)`](https://nodejs.org/) (Required install)
- [`edge.js (^11.3.1)`](https://github.com/agracio/edge-js) (Referenced via npm)

### Running this sample
This assumes you've already installed Rhino 7 WIP and Node.js for Windows, and have cloned the Rhino.Inside repository.
1. Once you've cloned the Rhino.Inside repository, open the `insideNode.sln` in Visual Studio and build `insideNode.csproj`. This builds the .dll which is referenced in the Node.js project.
2. Open a console from the `insideNodeApp` directory.
3. Run `npm install` to install any dependencies.
4. Run `node app.js` to run the sample. In the terminal, you should see:
```
Starting Rhino, please wait...
The mesh has 561 vertices and 512 faces.
```

