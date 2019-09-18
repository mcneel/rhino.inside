# Rhino Inside Unreal Engine
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.

## Sample 1
This sample shows how to start Rhino from Unreal Engine via the USharp plugin.  The C# code launches Rhino, creates some geometry, and returns information related to that geometry. This information is then printed back to the Unreal Engine Developer Log.
The sample has been tested on Windows 10, Rhino 7 WIP, Unreal Engine 4.23, and the associated version of USharp.

## Contents
The sample contains an Unreal Engine project whcih contains a directory named `Managed`. In here you will find the .sln, .csproj, and .cs files. There is one class which is loaded when the project is opened in Unreal Engine. Upon loading, the class manages to launch Rhino without UI and run some basic operations. The only .cs file is `rhino.inside\Epic Games\UE\Sample-1\Managed\Sample1.Managed\RhinoInsideGameMode.cs`. You can check the code here to see how Rhino is launched.

## Running this sample
This assumes you have already installed:
- Rhino WIP 7
- Unreal Engine 4.23
- USharp (see setup instructions here: https://github.com/pixeltris/USharp/wiki/Plugin-Setup)

Once these are all installed you should be able to: 
- Open the `rhino.inside\Epic Games\UE\Sample-1\Managed\Sample1.Managed.sln` file in Visual Studio and start debugging. This should open the Unreal Engine Editor which will prompt you to open a project.
- Once the UE Editor is open, go ahead and open the `rhino.inside\Epic Games\UE\Sample-1\Sample1.uproject`
- Check the Developer Tools Output Log in Unreal Engine Editor for a few messages which we print in the [RhinoInsideGameMode.cs](Managed/Sample1.Managed/RhinoInsideGameMode.cs) code.
