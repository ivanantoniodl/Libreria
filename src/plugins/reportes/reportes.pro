include(../plugins.pri)
include(reportes_dependencies.pri)

TARGET = $$qtLibraryTarget(reportes)
TEMPLATE = lib
CONFIG += plugin
DEFINES += REPORTES_LIBRARY

QT += sql xml

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

HEADERS += \
    fejemplodialog.h \
    reportespluginscollections.h \
    fejemplosindialog.h \
    freporteexistencias.h \
    freporteventas.h \
    reportes_global.h

SOURCES += \
    fejemplodialog.cpp \
    reportespluginscollections.cpp \
    fejemplosindialog.cpp \
    freporteexistencias.cpp \
    freporteventas.cpp

FORMS += \
    fejemplodialog.ui \
    freporteexistencias.ui \
    freporteventas.ui




















