QT += core gui widgets

TARGET = funhouse
TEMPLATE = app

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

include(../src/phantom/phantom.pri)

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    WidgetGallery.cpp \
    ColorTest.cpp \
    FunHouse.cpp \
    PhTestApp.cpp

HEADERS += \
    WidgetGallery.h \
    PhTestApp.h \
    Profiling.h


CONFIG(easy_profile) {
    DEFINES *= BUILD_WITH_EASY_PROFILER

    # When building without BUILD_WITH_EASY_PROFILER set, easy/profile.h's
    # macros do nothing, and we won't need to link with its library even if we
    # include its headers. But we'd rather not rely on it existing if we're
    # using it as a library in other projects, so we'll guard includes and uses
    # of it with ifdefs.
    INCLUDEPATH += "thirdparty/easy_profiler/easy_profiler_core/include"
}

g++ {
    # Disable useless noisy warnings
    QMAKE_CXXFLAGS *= -Wno-unused-function -Wno-unknown-pragmas -std=c++14
}
clang {
    QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-format-security -Wno-unused-function -Wno-unknown-pragmas
}
msvc {
    # Enable a bunch of warnings, and disable the ones that cause spam from STL
    # headers, Qt headers, stdlib headers. Also cause a few false positives in
    # our own code.
    #
    QMAKE_CXXFLAGS *= /Wall /wd4365 /wd4820 /wd4623 /wd4625 /wd4626 /wd5026 /wd5027 /wd4619 /wd4548 /wd4774 /wd4946 /wd4371
    QMAKE_CXXFLAGS *= /wd4710 # function not inlined
    QMAKE_CXXFLAGS *= /wd4711 # selected for automatic inline expansion

    # unreachable code warning in Qt library code, only happens in release (in Wall)
    CONFIG(release, debug|release) {
        QMAKE_CXXFLAGS *= /wd4702
    }

    # Disable MSVC C4068: unknown pragma warning. We use clang pragmas -- even
    # in MSVC builds -- to control the clang static analyzer's output. It would
    # be preferable to always suppress the warnings correctly, but it ends up
    # requiring multiple lines of nested pragmas for different compilers in
    # order to do this. So we'll just disable it globally. There are still
    # parts of the Ripcord code where we use nested pragmas to do it, but going
    # forward we'll just rely on this MSVC warning always being off.
    QMAKE_CXXFLAGS *= /wd4068

    # Enable warning on unhandled enums in switch cases
    QMAKE_CXXFLAGS *= /w14062

    # Speed up startup time when debugging with cdb
    # (copied from qt creator. this might not do anything.)
    QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO

    contains(DEFINES, BUILD_WITH_EASY_PROFILER) {
        CONFIG(debug, debug|release) {
            # todo
        } else {
            LIBS += -L"$$PWD/thirdparty/easy_profiler/bin"
            LIBS += -leasy_profiler
        }
    }
}
