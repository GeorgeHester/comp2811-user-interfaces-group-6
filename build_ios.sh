# USER SETTINGS
QT_PATH=/Users/george/Qt/5.15.2/ios

# PROJECT SETTINGS
PROJECT_FILE=src/vreal.pro
PLATFORM=ios

QMAKE=$QT_PATH/bin/qmake

if [ -d build/$PLATFORM/release ]; then
    rm -rf build/$PLATFORM/release
fi

if [ ! -d build/$PLATFORM/release ]; then
    mkdir -p build/$PLATFORM/release
fi

cd build/$PLATFORM/release

$QMAKE ../../../$PROJECT_FILE -spec macx-ios-clang CONFIG+=iphoneos CONFIG+=device CONFIG+=ios && /usr/bin/make qmake_all

if [[ $? -ne 0 ]]; then
    echo "Failed: qmake failed to execute"
    exit 1
fi
echo "Success: qmake successfully executed"

cd ../../../

open -a "Xcode" build/$PLATFORM/release/VReal.xcodeproj

exit 0
