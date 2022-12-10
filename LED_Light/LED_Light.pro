#Qt
QT += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += QT_DEPRECATED_WARNINGS

#C++
CONFIG += c++17

#Files
SOURCES += \
    config.cpp \
    crc32.cpp \
    export.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    config.h \
    crc32.h \
    export.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    default.qrc
