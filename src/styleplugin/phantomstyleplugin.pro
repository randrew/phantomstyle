QT += core gui widgets
CONFIG += plugin
TARGET = phantomstyleplugin
TEMPLATE = lib

DEFINES += QT_DEPRECATED_WARNINGS

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

    # For newer versions of VS2017 and up, C5045 will be enabled when Wall is
    # specified. This warning causes MSVC to tell you when the /Qspectre
    # switch, if enabled, would have caused spectre mitigations to be inserted
    # by the compiler. The warnings emitted in that case are not relevant for a
    # QStylePlugin.
    QMAKE_CXXFLAGS *= /wd5045
}
