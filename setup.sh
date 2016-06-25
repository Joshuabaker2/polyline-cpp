#!/bin/bash

if ! type cmake > /dev/null; then
        echo >&2 "ERROR: Cmake is not installed.  Please install (read the READ$
fi

mkdir build
cd build
cmake ..
make

echo "Build successful! Run `./polyline_test` to ensure unit tests work on your platform."

