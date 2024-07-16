$rhino=$args[0]
$env:RHINOINSIDE_RHINOPATH=$rhino
Write-Host "RHINOINSIDE_RHINOPATH = " -nonewline
Write-Host $rhino
dotnet test RhinoInside.sln --framework net48
Remove-Item Env:\RHINOINSIDE_RHINOPATH
