#!/bin/bash

# USER SETTINGS
QT_PATH="/Users/george/Qt"
QT_VERSION_NUMBER="5.15.2"
QT_PLATFORMS=("ios" "clang_64")

# Make sure working directory exists
#if [ ! -d working ]; then
#    mkdir working
#fi

for QT_PLATFORM in ${QT_PLATFORMS[@]}; do
    echo $QT_PLATFORM

    if [[ $QT_PLATFORM == "ios" ]]; then
        # Fix ios build using python version found in /usr/bin/python.
        # This version does not exist in newer versions of macOS.
        # New versions of macOS provide version 3 using /usr/bin/python3.
        cd $QT_PATH/$QT_VERSION_NUMBER/$QT_PLATFORM/mkspecs/features/uikit
        curl https://raw.githubusercontent.com/qt/qtbase/dev/mkspecs/features/uikit/devices.py >devices.py
    fi

    if [[ $QT_PLATFORM == "clang_64" ]]; then

        if [[ $OSTYPE =~ ^darwin ]]; then
            # Move to the mkspecs features folder and update the toolchain.prf file.
            # This fixes the QMAKE_DEFAULT_LIBDIRS empty error on macOS.
            cd $QT_PATH/$QT_VERSION_NUMBER/$QT_PLATFORM/mkspecs/features
            curl https://raw.githubusercontent.com/qt/qtbase/dev/mkspecs/features/toolchain.prf >toolchain.prf
        fi
    fi
done
