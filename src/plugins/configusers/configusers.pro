include(../plugins.pri)
include(configusers_dependencies.pri)

TARGET = $$qtLibraryTarget(ConfigUsers)
TEMPLATE = lib
CONFIG += plugin

QT += sql

SOURCES += modeloarbolpermisos.cpp \
    imgbutton.cpp \
    configusuarios.cpp \
    booleancolor.cpp \
    fusersadminpage.cpp \
    froladminpage.cpp \
    fusuariocargospage.cpp \
    treview.cpp \
    frolpersmisosmodificar.cpp

HEADERS += modeloarbolpermisos.h \
    imgbutton.h \
    configusuarios.h \
    booleancolor.h \
    fusersadminpage.h \
    froladminpage.h \
    fusuariocargospage.h \
    treview.h \
    frolpersmisosmodificar.h \
    configusers_global.h

FORMS += \ 
    fusersadminpage.ui \
    froladminpage.ui \
    fusuariocargospage.ui \
    frolpersmisosmodificar.ui










































