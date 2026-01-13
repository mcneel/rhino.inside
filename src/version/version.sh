#!/bin/bash

# navigate to script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# generate version numbers
dotnet build UpdateVersionNumbers.csproj --configuration ReleaseDebuggable -restore -m

# get version
VERSION_STRING=$(grep 'public const string VERSION_STRING' version.cs | sed -E 's/.*"([^"]+)".*/\1/')

# Remove leading zeros from the last segment
VERSION_STRING_FIXED=$(echo "$VERSION_STRING" | sed -E 's/(.*\.)(0*)([0-9]+)$/\1\3/')
echo "$VERSION_STRING" " → " "$VERSION_STRING_FIXED"

# set version in Directory.Build.props
sed -i 's|<RhinoInsideVersion>.*</RhinoInsideVersion>|<RhinoInsideVersion>'"$VERSION_STRING_FIXED"'</RhinoInsideVersion>|' ../Directory.Build.props

# expose version to GitHub Actions
echo "version=$VERSION_STRING_FIXED" >> "$GITHUB_OUTPUT"