#!/bin/bash
cd build
echo "Building..."
cmake --build .   
cd app
cp focuslock.out ../../
cd ../../
echo "Giving +rw permissions... "
chmod +rw focuslock.out
echo "DONE!"
