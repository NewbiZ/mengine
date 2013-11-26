Overview
---------
This is the MEgine project, a simple 2D game engine.

[![Build Status](https://drone.io/github.com/newbiz/mengine/status.png)](https://drone.io/github.com/newbiz/mengine/latest)

Dependencies
------------
- libglfw 2.7.7 or greater
- CMake 2.8.8 or greater
- Python 3.3 or greater (only for python bindings with -DBUILD_PYTHON=ON)

Instructions
------------
Just as any CMake project:

    git clone git://github.com/newbiz/mengine.git
    mkdir mengine.build
    cd mengine.build
    cmake ../mengine OR cmake -DBUILD_PYTHON=ON../mengine
    make -j

Authors
-------
- Aurelien Vallee <vallee.aurelien@gmail.com>
