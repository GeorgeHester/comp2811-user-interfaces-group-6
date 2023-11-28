# USER SETTINGS
QT_PATH=/Users/george/Qt/5.15.2/clang_64
QMAKE=$QT_PATH/bin/qmake

# PROJECT SETTINGS
PROJECT_FILE=src/camera-testing.pro

if [ ! -d build/release ]; then
    mkdir -p build/release
fi

cd build/release
$QMAKE ../../$PROJECT_FILE -spec macx-clang CONFIG+=qtquickcompiler CONFIG+=macOS && /usr/bin/make qmake_all
make -j8

#cd /Users/george/university/modules/comp2811/group-project/camera-testing/camera-testing/build/release
#make -j8
