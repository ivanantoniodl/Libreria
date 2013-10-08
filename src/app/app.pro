#-------------------------------------------------
#
# Project created by QtCreator 2011-08-15T16:46:51
#
#-------------------------------------------------

include(../../Libreria.pri)
include(../model/model.pri)
include(../plugins/coreplugin/coreplugin.pri)
include(../common/common.pri)

QT       += sql

TARGET = LIBRERIA
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    fconfconexion.cpp \
    fconexion.cpp \
	fmenumodeltaskpanel.cpp \
    configdialog.cpp \
    faboutapp.cpp \
    faboutplugins.cpp \
    freportes.cpp

HEADERS  += mainwindow.h \
    fconfconexion.h \
    fconexion.h \
	fmenumodeltaskpanel.h \
    configdialog.h \
    faboutapp.h \
    faboutplugins.h \
    freportes.h

FORMS    += \
    fconfconexion.ui \
    fconexion.ui \
    fmenumodel.ui \
    faboutapp.ui \
    faboutplugins.ui \
    freportes.ui


unix {
	#esto sirve para que el ejecutable en linux busque librerias tambien en el directorio donde el se encuentra

	#do the rpath by hand since it's not possible to use ORIGIN in QMAKE_RPATHDIR
	# this expands to $ORIGIN (after qmake and make), it does NOT read a qmake var
	QMAKE_RPATHDIR += \$\$ORIGIN
	#QMAKE_RPATHDIR += \$\$ORIGIN/plugins
	APP_PLUGINS_RPATH = $$join(QMAKE_RPATHDIR, ":")

	QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${APP_PLUGINS_RPATH}\'
	QMAKE_RPATHDIR =
}

DESTDIR = $$APP_BUILD_TREE

RESOURCES += \
    app.qrc \
    theme.qrc \
    categorias.qrc


















