#ifndef AUTORES_GLOBAL_H
#define AUTORES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AUTORES_LIBRARY)
#  define AUTORESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define AUTORESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AUTORES_GLOBAL_H
