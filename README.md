# PinBall

Simple PinBall game made as an university project.

## Requirements
You'll need CMake and gcc to build and compile the program. The game uses SDL and Chipmunk libraries. Chipmunk is included in this repository, but SDL needs to be downloaded.

Try the game yourself.
First clone the repository 

    git clone https://github.com/JonasKoziorek/PinBall

Then in the project folder run

    mkdir build
    cd build
    cmake -D CMAKE_BUILD_TYPE=Debug ..
    cmake ..
    cd ..
    make -C build && ./build/src/pinball

![Alt text](images/screenshot.png)
