# Rhino.Inside.JavaScript
Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.
### Running Rhino and Grasshopper inside various JavaScript Runtimes / Frameworks (Node.js, Electron, Chromium Embedded Framework)


## Samples

1. [Sample 1](Sample-1): Rhino.Inside.Node 1 - This sample runs Rhino inside Node.js. The JavaScript code calls into a .NET dll which launches Rhino, creates some geometry, and returns information related to that geometry. This information is then passed back to JavaScript and is printed to the console.
2. [Sample 2](Sample-2): Rhino.Inside.Node 2 - This sample is similar to Sample 1, but shows how to define other methods and call them via edge.js.
3. [Sample 3](Sample-3): Rhino.Inside.Electron - This sample extends Sample 1 and 2 with Electron. The Electron app calls methods from JavaScript to .NET to launch Rhino, create some geometry. This geometry is then passed back to Electron. The geometry is deserialized with rhino3dm.js and rendered with three.js.
4. [Sample 4](Sample-4): Rhino.Inside.Electron 2 - This sample extends Sample 3. The Electron app calls methods from JavaScript to .NET to launch Rhino and then launch Grasshopper. When a component is added to the definition which has a result that includes meshes, the meshes are passed back to Electron. The geometry is deserialized with rhino3dm.js and rendered with three.js.
5. [Sample 5](Sample-5): Rhino.Inside.CEF (Chromium Embedded Framework via CefSharp) - This sample is similar to Sample 4, except this time it uses Chromium Embedded Framework instead of Electron. The sample embeds a Chromium Browser inside a WinForm window, launches Rhino, and launches Grasshopper. When meshes are added to the Grasshopper definition, these meshes will be rendered in the Chromium browser by three.js.

## JavaScript Runtimes / Frameworks

The samples show how to run Rhino.Inside the following JavaScript frameworks:
- [`Node.js`](https://nodejs.org/en/) - Sample 1, Sample 2, and Sample 3. Node.js® is a JavaScript runtime built on Chrome's V8 JavaScript engine.
- [`Electron.js`](https://electronjs.org/) - Sample 4. Electron is an open-source framework developed and maintained by GitHub. Electron allows for the development of desktop GUI applications using web technologies: It combines the Chromium rendering engine and the Node.js runtime.
- [`Chromium Embedded Framework (CefSharp)`](https://cefsharp.github.io/) - Sample 5. The Chromium Embedded Framework is an open-source software framework for embedding a Chromium web browser within another application. 

## Dependencies
- [`Node.js`](https://nodejs.org) - It is crucial to install Node.js prior to running any of these samples.
- [`Edge.js`](https://github.com/agracio/edge-js) - This is used to call .NET functions from JavaScript in Sample 1, Sample 2, Sample 3, and Sample 4. Sample 5 uses the mechanism in CEF to pass data between .NET and JavaScript.

