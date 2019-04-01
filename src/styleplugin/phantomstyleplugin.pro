QT += core gui widgets
CONFIG += plugin
TARGET = phantomstyleplugin
TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += rtti_off exceptions_off

include(../phantom/phantom.pri)

SOURCES += phantomstyleplugin.cpp

HEADERS += phantomstyleplugin.h

OTHER_FILES += phantomstyleplugin.json

g++ {
    QMAKE_CXXFLAGS *= -Wno-unused-function -Wno-unknown-pragmas
}
clang {
    QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-format-security -Wno-unused-function -Wno-unknown-pragmas
}
msvc {
    # Enable a bunch of warnings, and disable the ones that cause spam from STL
    # headers, Qt headers, stdlib headers.
    QMAKE_CXXFLAGS *= /Wall /wd4365 /wd4820 /wd4623 /wd4625 /wd4626 /wd5026 /wd5027 /wd4619 /wd4548 /wd4774 /wd4946 /wd4371
    QMAKE_CXXFLAGS *= /wd4710 # function not inlined
    QMAKE_CXXFLAGS *= /wd4711 # selected for automatic inline expansion

    # unreachable code warning in Qt library code, only happens in release (in Wall)
    CONFIG(release, debug|release) {
        QMAKE_CXXFLAGS *= /wd4702
    }

    # Disable MSVC C4068: unknown pragma warning. We use clang pragmas -- even
    # in MSVC builds -- to control the clang static analyzer's output.
    QMAKE_CXXFLAGS *= /wd4068

    # Enable warning on unhandled enums in switch cases
    QMAKE_CXXFLAGS *= /w14062
}
