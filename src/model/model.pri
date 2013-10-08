include(../../Libreria.pri)

INCLUDEPATH *= $$PWD \
	$$PWD/om \
	$$PWD/views

INCLUDEPATH *= $$PWD
LIBS *= -L$$APP_BUILD_TREE -lqantmvc