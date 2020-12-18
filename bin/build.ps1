
param (
  [string]$target,
  [string]$port
)

Push-Location -Path $PSScriptRoot\..\
trap {
  Pop-Location
}

if (!(Test-Path  "src\inos\rowallan_light_control_${target}.ino")) {
  echo "'${target}' is not a valid target"
  pause
  Pop-Location
  exit
}

echo "> Removing previous build"
Get-ChildItem build\* -Recurse | Remove-Item
New-Item -Path "build\" -Name "rowallan_light_control" -ItemType "directory" -Force

echo "> Copying ino for ${target}"
Copy-Item -Path "src\inos\rowallan_light_control_${target}.ino" -Destination "build\rowallan_light_control\rowallan_light_control.ino"

echo "> Copying libs"
Copy-Item -Path "src\libs\*.cpp" -Destination "build\rowallan_light_control\"
Copy-Item -Path "src\libs\*.h" -Destination "build\rowallan_light_control\"

echo "> Dry run: Compiling project"
arduino-cli compile --fqbn arduino:avr:uno build\rowallan_light_control

$confirm = Read-Host "< Confirm upload? [y/N]"

if ($confirm -ne "y" -And $confirm -ne "Y") {
  echo "< Aborting upload"
  exit
}

echo "> Uploading project"
arduino-cli upload -p /dev/${port} --fqbn arduino:avr:uno build\rowallan_light_control

echo "< Done"
