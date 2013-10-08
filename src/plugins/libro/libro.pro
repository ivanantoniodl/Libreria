#-------------------------------------------------
#
# Project created by QtCreator 2012-01-26T10:44:29
#
#-------------------------------------------------


include(../plugins.pri)
include(libro_dependencies.pri)


TARGET = $$qtLibraryTarget(libro)

QT       += core gui sql

TEMPLATE = lib
CONFIG += plugin

DEFINES += LIBRO_LIBRARY

SOURCES += libro.cpp \
    fprincipallibro.cpp


HEADERS += libro.h \
    libro_global.h \ 
    fprincipallibro.h

FORMS += \
    fprincipallibro.ui


































