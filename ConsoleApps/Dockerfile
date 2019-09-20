# escape=`

# base image should match the host operating system
# rhino only works with process isolation
FROM mcr.microsoft.com/windows:1903

# install dotnet
RUN powershell -NoProfile -ExecutionPolicy unrestricted -Command " `
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; `
    &([scriptblock]::Create((Invoke-WebRequest -useb 'https://dot.net/v1/dotnet-install.ps1'))) -version 2.2.203"

ENV DOTNET_RUNNING_IN_CONTAINER=true `
    NUGET_XMLDOC_MODE=skip `
    DOTNET_SKIP_FIRST_TIME_EXPERIENCE=true `
    # TODO: edit this if you use a different version of rhino!
    RHINO_INSTALLER=rhino_en-us_7.0.19260.11525.exe

# install .NET 4.6.2 framework via chocolatey
RUN powershell -Command Set-ExecutionPolicy Bypass -Scope Process -Force; `
        iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
RUN powershell -Command "choco install -y netfx-4.6.2-devpack"
RUN setx path "%path%;C:\Users\ContainerAdministrator\AppData\Local\Microsoft\dotnet"

# install rhino (with “-package -quiet” args)
COPY ["$RHINO_INSTALLER", "$RHINO_INSTALLER"]
RUN powershell -Command " `
    Start-Process .\$env:RHINO_INSTALLER -ArgumentList '-package', '-quiet' -NoNewWindow -Wait; `
    Remove-Item .\$env:RHINO_INSTALLER"

# setup cloudzoo auth
# TODO: switch on CloudZooPlainText and copy 55500d41-3a41-4474-99b3-684032a4f4df.lic,
#       cloudzoo.json and settings-Scheme__Default.xml to the working dir
RUN powershell -Command " `
    mkdir 'C:\Users\ContainerAdministrator\AppData\Roaming\McNeel\Rhinoceros\6.0\License Manager\Licenses'; `
    mkdir 'C:\Users\ContainerAdministrator\AppData\Roaming\McNeel\Rhinoceros\7.0\settings'"
COPY ["55500d41-3a41-4474-99b3-684032a4f4df.lic", "C:/ProgramData/McNeel/Rhinoceros/6.0/License Manager/Licenses/"]
COPY ["cloudzoo.json", "C:/Users/ContainerAdministrator/AppData/Roaming/McNeel/Rhinoceros/6.0/License Manager/Licenses/"]
COPY ["settings-Scheme__Default.xml", "C:/Users/ContainerAdministrator/AppData/Roaming/McNeel/Rhinoceros/7.0/settings/"]

# compile
COPY ["HelloWorld", "src"]
RUN powershell -Command "dotnet build .\src"

CMD .\src\bin\Debug\HelloWorld.exe