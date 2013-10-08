#ifndef LIBRO_GLOBAL_H
#define LIBRO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBRO_LIBRARY)
#  define LIBROSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBROSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBRO_GLOBAL_H
