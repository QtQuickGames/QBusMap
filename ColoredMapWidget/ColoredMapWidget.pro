QT += core gui quickwidgets widgets qml quick opengl concurrent

TEMPLATE = lib
DEFINES += COLOREDMAPWIDGET_LIBRARY

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

equals(QT_MAJOR_VERSION, 5) {
    lessThan(QT_MINOR_VERSION, 15) {
        error("$$TARGET requires Qt 5.15.1")
    }
        equals(QT_MINOR_VERSION, 15) : lessThan(QT_PATCH_VERSION, 1) {
                error("$$TARGET requires Qt 5.15.1")
        }
}

equals(QT_MAJOR_VERSION, 6) {
  error("This version of the ArcGIS Runtime SDK for Qt is incompatible with Qt 6")
}

ARCGIS_RUNTIME_VERSION = 100.11
include($$PWD/arcgisruntime.pri)

win32:CONFIG += \
    embed_manifest_exe

SOURCES += \
    coloredmap.cpp \
    coloredmapwidget.cpp \
    featurelayerfromshapefile.cpp

HEADERS += \
    ColoredMapWidget_global.h \
    coloredmap.h \
    coloredmapwidget.h \
    featurelayerfromshapefile.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ColoredMapApp.qrc
