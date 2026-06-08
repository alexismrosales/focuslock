#!/bin/bash
cd build
echo "Building..."
cmake --build .   
cd app
cp focuslock.out daemon.out ../../
cd ../../
echo "Giving +rw permissions... "
chmod +rw focuslock.out daemon.out 
echo "DONE!"
