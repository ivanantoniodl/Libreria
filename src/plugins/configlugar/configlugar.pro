include(../plugins.pri)
include(configlugar_dependencies.pri)

TARGET = $$qtLibraryTarget(ConfigLugar)
TEMPLATE = lib
CONFIG += plugin
DEFINES += CONFIGLUGAR_LIBRARY

QT += sql

SOURCES += \ 
	configlugar.cpp \
    flugaresconfigpage.cpp \
    configlugarpage.cpp \
    flugartipopage.cpp \
    fmaquinaspage.cpp

HEADERS += \ 
	configlugar.h \
    flugaresconfigpage.h \
    configlugarpage.h \
    flugartipopage.h \
    fmaquinaspage.h \
    configlugar_global.h

FORMS += \
    flugarconfig.ui \
    flugaresconfigpage.ui \
    flugartipopage.ui \
    fmaquinaspage.ui

















