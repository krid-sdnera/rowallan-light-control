#!/bin/bash

target=$1

cd "$(dirname -- $(readlink -f "$0"))/.."

if [[ ! -e src/inos/rowallan_light_control_${target}.ino ]]; then
  echo \"$target\" is not a valid target
  exit
fi

echo "> Removing previous build"
rm -rf build/
mkdir -p build/rowallan_light_control

echo "> Copying ino for ${target}"
cp src/inos/rowallan_light_control_${target}.ino build/rowallan_light_control/rowallan_light_control.ino

echo "> Copying libs"
cp src/libs/*.{cpp,h} build/rowallan_light_control/

echo "< Done"

