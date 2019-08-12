### THIS SAMPLE IS UNDER CONSTRUCTION

# Rhino.Inside.PaintDotNet
Rhino Inside® technology allows Rhino and Grasshopper to be embedded within other products.
### Running Rhino and Grasshopper inside Paint.NET

### Dependencies
- [`Rhino 7 WIP`](https://www.rhino3d.com/download/rhino-for-windows/wip) (Required install)
- [`Paint.NET 4.2`](https://www.getpaint.net/download.html) (Required install)

### Running this sample
This assumes you've already installed Rhino 7 WIP and Paint.NET 4.2 for Windows, and have cloned the Rhino.Inside repository.
1. This csproj needs to copy a .dll inside the Paint.NET Effects folder, which is in C:\Program Files and thus needs elevated priileges. You can either give your user elevated permissions to that folder or run Visual Studio as administrator.
2. Once you've cloned the Rhino.Inside repository, open the `RhinoPaint.sln` in Visual Studio and build `RhinoPaint.csproj`. This builds the .dll which is copied to the Paint.NET Effects folder.
3. Start debugging the RhinoPaint project. You should see Paint.NET open.
4. On the Paint.NET menu bar, click on `Effects`. You should see `Rhinoceros`. Clicking on `Rhinoceros` should reveal a submenu named `RhinoPaint`. Click on `RhinoPaint`.
5. You will see a progress prompt appear, after which Paint.NET will crash. 
6. In the Visual Studio Output tab, you will notice that Rhino did run:
```
The mesh has 561 vertices and 512 faces.
```
7. In Paint.NET you should see the pixels rendered from the perspective Rhino viewport with a wireframe sphere.

### References
The Paint.NET Developer forums can be found here: [https://forums.getpaint.net/forum/17-plugin-developers-central/](https://forums.getpaint.net/forum/17-plugin-developers-central/).

To get acquainted with what can and cannot be done with Paint.NET plugins, check out this thread [https://forums.getpaint.net/topic/14566-what-is-and-isnt-possible-when-writing-plugins/](https://forums.getpaint.net/topic/14566-what-is-and-isnt-possible-when-writing-plugins/).



