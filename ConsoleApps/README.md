# Rhino.Inside Console Apps

## HelloWorld + Docker

The [_Dockerfile_](Dockerfile) in this directory can be used to build a Docker image that will run the HelloWorld sample. To use it...

1. Download Rhino WIP into this directory (update the [_Dockerfile_](Dockerfile) if you use a different version)
1. With the same version of Rhino WIP installed locally, [configure Rhino to disable license key encryption](https://github.com/mcneel/compute.rhino3d/blob/master/docs/installation.md#licensing-rhino-and-scaling) and copy the required files into this directory
    * _C:/ProgramData/McNeel/Rhinoceros/6.0/License Manager/Licenses/55500d41-3a41-4474-99b3-684032a4f4df.lic_
    * _%AppData%/Roaming/McNeel/Rhinoceros/6.0/License Manager/Licenses/cloudzoo.json_
    * _%AppData%/Roaming/McNeel/Rhinoceros/7.0/settings/settings-Scheme__Default.xml_
1. Run `docker build --isolation process -t rhino-hello-world .`
1. Run `docker run --isolation process rhino-hello-world`
1. You should see `Mesh with 2145 vertices created`. Ignore the "Cannot read keys..." error.
1. Press <kbd>Ctrl</kbd>+<kbd>C</kbd> to exit the running container
