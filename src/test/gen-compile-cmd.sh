#!/bin/bash

rm -rf tmp compile_commands.json
mkdir tmp
cd tmp
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
mv compile_commands.json ..
cd ..
rm -rf tmp
