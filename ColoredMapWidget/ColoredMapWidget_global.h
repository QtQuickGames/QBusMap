#ifndef COLOREDMAPWIDGET_GLOBAL_H
#define COLOREDMAPWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COLOREDMAPWIDGET_LIBRARY)
#  define COLOREDMAPWIDGET_EXPORT Q_DECL_EXPORT
#else
#  define COLOREDMAPWIDGET_EXPORT Q_DECL_IMPORT
#endif

#endif // COLOREDMAPWIDGET_GLOBAL_H