#ifndef LIBROS_GLOBAL_H
#define LIBROS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBROS_LIBRARY)
#  define LIBROSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBROSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBROS_GLOBAL_H
