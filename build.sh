#! /bin/sh

set -e

if [ -d "build" ]
then
    cd build
else
    mkdir build
    cd build
fi

cmake -DCMAKE_BUILD_TYPE=Debug ..

cmake --build .