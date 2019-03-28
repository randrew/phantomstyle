TEMPLATE = lib
CONFIG += plugin lib
QT         += widgets
SOURCES     = plugin.cpp

TARGET  = phantomstyle
PLUGIN_TYPE = styles
PLUGIN_CLASS_NAME = PhantomStylePlugin



include(../src/phantom/phantom.pri)


DESTDIR = .


EXAMPLE_FILES += phantom.json

target.path = .

INSTALLS += target

CONFIG += install_ok 
