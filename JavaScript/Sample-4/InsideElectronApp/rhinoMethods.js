const path = require('path');
var namespace = 'InsideElectron';

// Construct path to .NET Core dll
const baseNetAppPath = path.join(path.resolve(__dirname, '..'), namespace +'/bin/Debug/');
var baseDll = path.join(baseNetAppPath, namespace + '.dll');

//process.env.EDGE_USE_CORECLR = 1;
process.env.EDGE_APP_ROOT = baseNetAppPath;

var edge = require('electron-edge-js');

var rhinoTypeName = namespace + '.RhinoMethods';


// Map methods from .NET dll


var startRhino = edge.func({
    assemblyFile: baseDll,
    typeName: rhinoTypeName,
    methodName: 'StartRhino'
});

var grasshopperCommand = edge.func({
  assemblyFile: baseDll,
  typeName: rhinoTypeName,
  methodName: 'StartGrasshopper'
});

/*
var doSomething = edge.func({
  assemblyFile: baseDll,
  typeName: rhinoTypeName,
  methodName: 'DoSomething'
});
*/

// Launch Rhino and Grasshopper from Javascript
/*
startRhino('', function(error, result) {
  if (error) throw JSON.stringify(error);
  console.log(result);
});
*/

var payload = {
  cb: function (data, callback) {
      callback(null, onGhObjectAdded(data));
  }
};
grasshopperCommand(payload, function(error, result) {
  if (error) throw JSON.stringify(error);
  console.log(result);
});

/*
require('electron').ipcRenderer.on('open-rhino', (event, message) => {
  console.log('starting rhino');
  startRhino('', function(error, result) {
    if (error) throw JSON.stringify(error);
    console.log(error);
    console.log(result);

  });
});


require('electron').ipcRenderer.on('open-grasshopper', (event, message) => {
  console.log('starting grasshopper');
  var payload = {
    cb: function (data, callback) {
        callback(null, onGhObjectAdded(data));
    }
  };
  grasshopperCommand(payload, function(error, result) {
    if (error) throw JSON.stringify(error);
    console.log(error);
    console.log(result);
  });
});

require('electron').ipcRenderer.on('do-something', (event, message) => {
  console.log('doing something');
  doSomething('', function(error, result) {
    if (error) throw JSON.stringify(error);
    console.log(error);
    console.log(result);
  });
});

require('electron').ipcRenderer.on('clear-scene', (event, message) => {
  scene.traverseVisible(function(child) {
    if (child.type !== 'Scene') {
       scene.remove(child);
    }
  });
  animate();
});

*/

function onGhObjectAdded(data)
{
  //console.log('Object Added in GH ' + data);

  scene.traverseVisible(function(child) {
    if (child.type !== 'Scene') {
       scene.remove(child);
    }
  });
  

  //convert this to object
  var obj = JSON.parse(data);
  var rhinoMesh = rhino.CommonObject.decode(obj);

  let material = new THREE.MeshBasicMaterial( {wireframe: true, color: 0x00ff00 } );
  var threeMesh = meshToThreejs(rhinoMesh, material);

  scene.add(threeMesh);
}


window.onclose = function(){
  // Do something
  /*
  console.log('About to dispose Rhino');
    disposeRhino('', function(error, result) {
      if (error) throw JSON.stringify(error);
      console.log(error);
      console.log(result);
    });
    */
}

// wait for the rhino3dm web assembly to load asynchronously
rhino3dm().then(function(m) {
  console.log('Loaded rhino3dm.');
  rhino = m; // global
  run();
});


var scene, camera, renderer, controls;
function run() {

    scene = new THREE.Scene();
    scene.background = new THREE.Color(10,10,10);
    camera = new THREE.PerspectiveCamera( 75, window.innerWidth/window.innerHeight, 0.1, 1000 );
    controls = new THREE.OrbitControls( camera );

    renderer = new THREE.WebGLRenderer({antialias: true});
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight );
    document.body.appendChild( renderer.domElement );

    camera.position.z = 5;

    window.addEventListener( 'resize', onWindowResize, false );

    animate();

};

var animate = function () {
  requestAnimationFrame( animate );
  controls.update();
  renderer.render( scene, camera );
};

function onWindowResize() {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize( window.innerWidth, window.innerHeight );
  animate();
}

function meshToThreejs(mesh, material) {
    var geometry = new THREE.BufferGeometry();
    var vertices = mesh.vertices();
    var vertexbuffer = new Float32Array(3 * vertices.count);
    for( var i=0; i<vertices.count; i++) {
      pt = vertices.get(i);
      vertexbuffer[i*3] = pt[0];
      vertexbuffer[i*3+1] = pt[1];
      vertexbuffer[i*3+2] = pt[2];
    }
    // itemSize = 3 because there are 3 values (components) per vertex
    geometry.addAttribute( 'position', new THREE.BufferAttribute( vertexbuffer, 3 ) );
  
    indices = [];
    var faces = mesh.faces();
    for( var i=0; i<faces.count; i++) {
      face = faces.get(i);
      indices.push(face[0], face[1], face[2]);
      if( face[2] != face[3] ) {
        indices.push(face[2], face[3], face[0]);
      }
    }
    geometry.setIndex(indices);
  
    var normals = mesh.normals();
    var normalBuffer = new Float32Array(3*normals.count);
    for( var i=0; i<normals.count; i++) {
      pt = normals.get(i);
      normalBuffer[i*3] = pt[0];
      normalBuffer[i*3+1] = pt[1];
      normalBuffer[i*3+2] = pt[1];
    }
    geometry.addAttribute( 'normal', new THREE.BufferAttribute( normalBuffer, 3 ) );
    return new THREE.Mesh( geometry, material );
  }