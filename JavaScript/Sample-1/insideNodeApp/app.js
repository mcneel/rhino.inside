// require edge.js: https://github.com/agracio/edge-js
var edge = require('edge-js')

// link to dll with Rhino.Inside code
var rhinoInside = edge.func('../insideNode/bin/Debug/insideNode.dll')

console.log('Starting Rhino, please wait...')

// run Rhino.Inside code. This method calls into the dll defined above, creates an instance of the Startup class, and runs the Invoke function. 
// This function creates a NURBS sphere, meshes this, and returns some information related to the faces and vertices of the mesh. 
// See insideNode/Startup.cs for the code that is run by this method.

rhinoInside('', function (error, result) {

    if (error) throw error;

    console.log(result);

});
