#-------------------------------------------------
#
# Project created by QtCreator 2012-01-26T10:44:29
#
#-------------------------------------------------


include(../plugins.pri)
include(libros_dependencies.pri)


TARGET = $$qtLibraryTarget(libros)

QT       += core gui sql

TEMPLATE = lib
CONFIG += plugin

DEFINES += LIBROS_LIBRARY

SOURCES += libros.cpp 

HEADERS += libros.h \
    libros_global.h


FORMS += 





























