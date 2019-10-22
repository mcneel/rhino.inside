# Rhino.Inside.UE
Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.
### Running Rhino and Grasshopper inside Epic Games' Unreal Engine (4.23)

![gif](https://user-images.githubusercontent.com/1014562/67323123-52dde100-f512-11e9-89f8-e76f884612d6.gif)

## Samples

1. [Sample 1](Sample-1): This sample runs Rhino inside Unreal Engine using the USharp Library. Check the Unreal Engine console (`Window > Developer Tools > Output Log`) for the results of a basic operation with RhinoCommon.
1. [Sample 2](Sample-2): This sample builds upon Sample 1 and shows how to pass mesh geometry from Rhino to Unreal Engine. The `ASample3Actor` class includes methods that return a list of vertices and face ids that are exposed to the Blueprint System.
1. [Sample 3](Sample-3): This sample shows how to pass meshes from Grasshopper to Unreal Engine.


## Dependencies
At the time of writing, all samples developed on Windows 10. Besides having Rhino 7 WIP installed, you will need the following: 

- [`Unreal Engine`](https://www.unrealengine.com/) - The samples were developed with UE 4.23. Requires about 9-10 GB of hard drive space.
- [`Visual Studio 2017`](https://visualstudio.microsoft.com/downloads/) - USharp depends on Visual Studio 2017 build tools for the setup.
- [`USharp`](https://github.com/pixeltris/USharp) - C# plugin for Unreal Engine 4. Please see the setup section below for preparing the USharp plugin.

## Setup
Since Rhino.Inside is based on .NET, the host application should have a .NET API. Unreal Engine has a C++ API. In order to facilitate working with Rhino.Inside, we can use the [USharp project](https://github.com/pixeltris/USharp), which provides a .NET wrapper around some of UE's C++ API as well as some tools to properly format our assemblies. 
The [USharp setup](https://github.com/pixeltris/USharp/wiki/Plugin-Setup) goes through some steps to compile the source code for some of these tools. We've had to change one variable in the source code to make Grasshopper work within Unreal. In order to skip the compilation steps, we've prepared a compiled version of USharp which you will need to install.

> NOTE: This assumes you've already installed Unreal Engine 4.23 

1. Download this zip: [USharp Build](https://drive.google.com/file/d/1nB37JJfVslURkR6WmX3WFf_WjnfBMGlK/view?usp=sharing)
2. Unzip the contents to the `C:\Program Files\Epic Games\UE_4.23\Engine\Plugins` directory. The contents should unzip into a directory named `USharp`.
3. Create a folder `%APPDATA%\USharp`.
4. Open the Unreal Engine Editor. When prompted to create a new project, you should now have four project types: C++, Blueprint, Unreal Studio, and C#.

![image](https://user-images.githubusercontent.com/1014562/66644086-5e7efd00-ec20-11e9-9225-a4dc87406743.png)

5. Test the installation by creating a new project based on the "2D Side Scroller". Enter a folder and project name, and click `Create Project`. You will get a popup from USharp asking if you want to build the project with a prompt reading "C# game project isn't compiled. Compile it now?". Click `Yes`.

![image](https://user-images.githubusercontent.com/1014562/66644259-c6354800-ec20-11e9-9e3f-79beadca366f.png)

6. Play the game! Press the `Play` button or press `ALT+P`.

![image](https://user-images.githubusercontent.com/1014562/66644373-114f5b00-ec21-11e9-8eb7-1f43727746d0.png)

