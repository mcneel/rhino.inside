// require edge.js: https://github.com/agracio/edge-js
var edge = require('edge-js');

// construct the path to the .NET dll
var namespace = 'InsideNode';
var baseAppPath = '../' + namespace + '/bin/Debug/';
var baseDll = baseAppPath + namespace + '.dll';

var rhinoTypeName = namespace + '.RhinoMethods';

// Define functions
var startRhino = edge.func({
  assemblyFile: baseDll,
  typeName: rhinoTypeName,
  methodName: 'StartRhino'
});

var doSomething = edge.func({
  assemblyFile: baseDll,
  typeName: rhinoTypeName,
  methodName: 'DoSomething'
});

// Call functions
startRhino('', function (error, result) {
  if (error) throw error;
  console.log(result);
});

doSomething('', function (error, result) {
  if (error) throw error;
  console.log(result);
});


