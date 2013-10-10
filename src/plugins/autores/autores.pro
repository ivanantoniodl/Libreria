#-------------------------------------------------
#
# Project created by QtCreator 2012-01-26T10:44:29
#
#-------------------------------------------------


include(../plugins.pri)
include(autores_dependencies.pri)


TARGET = $$qtLibraryTarget(autores)

QT       += core gui sql

TEMPLATE = lib
CONFIG += plugin

DEFINES += autores_LIBRARY

SOURCES += autores.cpp \
    fautores.cpp \
    fingresoautor.cpp
    

HEADERS += autores.h \
    autores_global.h \
    fautores.h \
    fingresoautor.h
   


FORMS += \ 
    fautores.ui \
    fingresoautor.ui





























