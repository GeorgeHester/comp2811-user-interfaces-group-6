QT += core widgets gui multimedia multimediawidgets

CONFIG += c++17
CONFIG += sdk_no_version_check

SOURCES += \
    store.cpp \
    main.cpp \
    settingshandler.cpp \
    header.cpp \
    rootwindow.cpp \
    capturewindow.cpp \
    settingswindow.cpp \
    feedwindow.cpp \
    postwindow.cpp

HEADERS += \
    store.h \
    window.h \
    resource.h \
    settingshandler.h \
    header.h \
    footer.h \
    rootwindow.h \
    capturewindow.h \
    settingswindow.h \
    postwindow.h \
    feedwindow.h \
    displaymode.h

RESOURCES += \
    font.qrc \
    icon.qrc \
    style.qrc \
    video.qrc \
    json.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_TARGET_BUNDLE_PREFIX = com.nightfoxdev
QMAKE_BUNDLE = com.nightfoxdev.vreal
QMAKE_APPLICATION_BUNDLE_NAME = VReal
TARGET = VReal
VERSION = 0.1.0

darwin {
    QMAKE_INFO_PLIST = static/darwin/Info.plist
    ICON = static/darwin/icon.icns
}

ios {
    QMAKE_INFO_PLIST = static/ios/Info.plist
}
