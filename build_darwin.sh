# USER SETTINGS
QT_PATH=/Users/george/Qt/5.15.2/clang_64

# PROJECT SETTINGS
PROJECT_FILE=src/vreal.pro
PLATFORM=darwin

QMAKE=$QT_PATH/bin/qmake

if [ -d build/$PLATFORM/release ]; then
    rm -rf build/$PLATFORM/release
fi

if [ ! -d build/$PLATFORM/release ]; then
    mkdir -p build/$PLATFORM/release
fi

cd build/$PLATFORM/release

$QMAKE ../../../$PROJECT_FILE -spec macx-clang CONFIG+=qtquickcompiler CONFIG+=darwin && /usr/bin/make qmake_all

if [[ $? -ne 0 ]]; then
    echo "Failed: qmake failed to execute"
    exit 1
fi
echo "Success: qmake successfully executed"

make -j8

if [[ $? -ne 0 ]]; then
    echo "Failed: make failed to execute"
    exit 1
fi
echo "Success: make successfully executed"

cd ../../../

open build/$PLATFORM/release/vreal.app

exit 0
