# Rhino Inside Unreal Engine
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.

## Sample 2: Pass mesh geometry to Unreal Engine
This sample builds upon sample 1 and shows how to pass geometry from Rhino to Unreal Engine.

> NOTE: Please see the Setup section for instructions on installing USharp: 

## Contents
The sample contains an Unreal Engine project which contains a directory named `Managed`. In here you will find the .sln, .csproj, and .cs files. There is one class which is loaded when the project is opened in Unreal Engine. Upon loading, the class manages to launch Rhino without UI and run some basic operations. The only .cs file is `rhino.inside\Epic Games\UE\Sample-2\Managed\Sample2.Managed\Sample2Actor.cs`. You can check the code here to see how Rhino is launched.

This class has been converted to a blueprint, in order to get access to the Procedural Mesh.

## Tutorial
This sample was prepared for a masterclass for the AEC Tech Symposium 2019. You can find the documentation here: https://github.com/mcneel/Rhino.Inside-Workshop/wiki/Sample-3


