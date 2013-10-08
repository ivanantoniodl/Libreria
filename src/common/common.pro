include(../../Libreria.pri)
include(../model/model.pri)
DESTDIR = $$APP_BUILD_TREE

QT += sql xml
TARGET = tipcommon
TEMPLATE = lib
DEFINES += COMMON_LIBRARY

HEADERS += \ 
	tvalidator.h \
    tlineedit.h \
    ttable.h \
    nightcharts.h \
    common_global.h \
	twidgets.h \
    permisos.h \
    odsreports/reporteods.h \
    odsreports/configodsreport.h \
    combo.h
SOURCES += \ 
	tvalidator.cpp \
    tlineedit.cpp \
    ttable.cpp \
    nightcharts.cpp \
	twidgets.cpp \
    permisos.cpp \
    odsreports/reporteods.cpp \
    odsreports/configodsreport.cpp \
    combo.cpp









