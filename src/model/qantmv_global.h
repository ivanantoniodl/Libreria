 #ifndef QANTMV_GLOBAL_H
#define QANTMV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QANTMV_LIBRARY)
#  define QANTMVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QANTMVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QANTMV_GLOBAL_H
