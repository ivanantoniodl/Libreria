include(../plugins.pri)
include(coreplugin_dependencies.pri)

TARGET = $$qtLibraryTarget(coreplugin)

TEMPLATE = lib
CONFIG += plugin
DEFINES += CORE_LIBRARY

QT += xml sql

unix {
	INCLUDEPATH +=	/opt/openrpt/OpenRPT/common \
					/opt/openrpt/common \
					/opt/openrpt/OpenRPT/renderer

	LIBS += -L/opt/openrpt/lib
}
win32 {
	INCLUDEPATH +=	c:/openrpt/OpenRPT/common \
					c:/openrpt/common \
					c:/openrpt/OpenRPT/renderer

	LIBS += -Lc:/openrpt/lib
}
LIBS += -lrenderer -lcommon


SOURCES += \ 
	plugincollection.cpp \
	configplugin.cpp \
    configpage.cpp \
    reports/genorpt.cpp \ 
    iplugin.cpp \
    principalformplugin.cpp \
    reportplugin.cpp

HEADERS += iplugin.h \
    principalformplugin.h \
	configplugin.h \
	plugincollection.h \
	configpage.h \
    reportplugin.h \
    reports/genorpt.h \ 
    core_global.h






