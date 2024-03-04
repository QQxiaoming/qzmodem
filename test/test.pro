!versionAtLeast(QT_VERSION, 6.2.0) {
    message("Cannot use Qt $$QT_VERSION")
    error("Use Qt 6.2.0 or newer")
}
QT += core gui widgets

TARGET_ARCH=$${QT_ARCH}
CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS += -Wno-deprecated-copy

include(../src/qzmodem.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp
    

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h
