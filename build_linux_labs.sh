#!/bin/bash

# USER SETTINGS
QT_PATH=/home/csunix/linux/apps/install/qt/5.15.2/5.15.2/gcc_64

# PROJECT SETTINGS
PROJECT_FILE=src/vreal.pro
PLATFORM=linux

QMAKE=$QT_PATH/bin/qmake

killall VReal

if [ -d build/$PLATFORM/release ]; then
    rm -rf build/$PLATFORM/release
fi

if [ ! -d build/$PLATFORM/release ]; then
    mkdir -p build/$PLATFORM/release
fi

cd build/$PLATFORM/release

$QMAKE ../../../$PROJECT_FILE -spec linux-g++ CONFIG+=qtquickcompiler CONFIG+=linux && /usr/bin/make qmake_all

if [[ $? -ne 0 ]]; then
    echo "Failed: qmake failed to execute"
    exit 1
fi
echo "Success: qmake successfully executed"

/usr/bin/make -j48

if [[ $? -ne 0 ]]; then
    echo "Failed: make failed to execute"
    exit 1
fi
echo "Success: make successfully executed"

cd ../../../

build/$PLATFORM/release/VReal

exit 0
