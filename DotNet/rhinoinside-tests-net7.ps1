# — Check whether first positional argument was supplied
if (-not $args.Count -or [string]::IsNullOrWhiteSpace($args[0])) {
    $self = Split-Path -Leaf $PSCommandPath  # script’s own filename
    Write-Host "Usage:`n  $self <rhino_system_path>" -ForegroundColor Red
    exit 1
}
$rhino=$args[0]
$env:RHINOINSIDE_RHINOPATH=$rhino
Write-Host "RHINOINSIDE_RHINOPATH = " -nonewline
Write-Host $rhino
dotnet test RhinoInside.sln /tl:off --framework net7.0-windows
Remove-Item Env:\RHINOINSIDE_RHINOPATH
