# General

This application makes use of the Qt Community Edition which is an open source development framework. As such any changes you make to this repository must comply with the rules set out by the Qt Group these can be found [Here](https://www.qt.io/download-open-source#obligations). Further details about licencing can be found [Here](https://doc.qt.io/qt-5/licenses-used-in-qt.html).

> [!TIP]
> If you experience a `permission denied` error when attempting to run scripts you may need to modify the files permissions, this can be done by running `chmod u+x <name>.sh`

# Building for macOS

## Prerequisites

- Qt Version 5.15.2
- Either the [GNU Compiler Collection](https://www.gnu.org) including gcc g++ and make or alternatively [Clang](https://clang.llvm.org)

> [!NOTE]
> The GNU Compiler Collection can be installed from [Homebrew](https://formulae.brew.sh/formula/gcc)

> [!NOTE]
> Clang comes packaged in Xcode and is the default C/C++ compiler option for macOS at `/usr/bin`

> [!WARNING]
> It is advised to user Clang when creating applications for macOS

## Process

> [!IMPORTANT]
> The version of Qt 5.15.2 provided by the offical channel is currently non functional out of box. As such a shell script has been provided which aims to update all known issues. This script is called `fixes_darwin.sh` make sure to update the `QT_PATH` variable in this file before running

1. Update the `QT_PATH` variable in the `build_darwin.sh` file to match your current Qt 5.15.2 installation location
2. Execute `./build_darwin.sh` in the terminal to build the application
3. The application binary (`.app` file) will be in the `build/darwin/release` folder

# Building for RHEL (Labs)

## Prerequisites

- Qt Version 5.15.2
- The [GNU Compiler Collection](https://www.gnu.org)

> [!NOTE]
> To install the required tools you can run the following
> ```
> module load legacy-eng
> module load dependent-modules
> ```
> ```
> module add gcc
> ```
> ```
> module add qt/5.15.2
> ```

## Process

> [!IMPORTANT]
> Make sure you have installed the required tools using the Labs method, alternatively you can run the `fixes_linux_labs.sh` script which will do this for you

1. Update, if necessary, the `QT_PATH` variable in the `build_linux_labs.sh` file to match your current Qt 5.15.2 installation location
2. Execute `./build_linux_labs.sh` in the terminal to build the application
3. The application binary will be in the `build/linux/release` folder