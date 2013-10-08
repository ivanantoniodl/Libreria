include(../plugins.pri)
include(configempresa_dependencies.pri)

TARGET = $$qtLibraryTarget(ConfigEmpresa)
TEMPLATE = lib
CONFIG += plugin
DEFINES += CONFIGEMPRESA_LIBRARY

QT += sql

HEADERS += \
    fempresaspage.h \
    configempresa_global.h

SOURCES += \
    fempresaspage.cpp

FORMS += \
    fempresaspage.ui




