# USER SETTINGS
QT_PATH=/Users/george/Qt/5.15.2/clang_64
QMAKE=$QT_PATH/bin/qmake

# PROJECT SETTINGS
PROJECT_FILE=src/camera-testing.pro
PLATFORMS=(darwin)

# Determine operating system
OS="unknown"

if [[ $OSTYPE =~ ^darwin ]]; then
    OS="darwin"
fi

if [[ $OSTYPE =~ ^linux ]]; then
    OS="linux"
fi

# Check operating system is supported
if [[ $OS == "unknown" ]]; then
    echo "Failed: Unknown operating system"
    exit 1
fi

# Perform a build for each platform
for platform in ${PLATFORMS[@]}; do
    if [ ! -d build/$platform/release ]; then
        mkdir -p build/$platform/release
    fi

    cd build/$platform/release

    $QMAKE ../../../$PROJECT_FILE -spec macx-clang CONFIG+=qtquickcompiler CONFIG+=$platform && /usr/bin/make qmake_all

    if [[ $? -ne 0 ]]; then
        echo "Failed: qmake failed to execute"
        exit 1
    fi

    make -j8

    if [[ $? -ne 0 ]]; then
        echo "Failed: make failed to execute"
        exit 1
    fi

    cd ../../../
done

exit 0
