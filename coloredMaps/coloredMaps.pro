#-------------------------------------------------
#  Copyright 2019 ESRI
#
#  All rights reserved under the copyright laws of the United States
#  and applicable international laws, treaties, and conventions.
#
#  You may freely redistribute and use this sample code, with or
#  without modification, provided you include the original copyright
#  notice and use restrictions.
#
#  See the Sample code usage restrictions document for further information.
#-------------------------------------------------

TARGET = coloredMaps 
TEMPLATE = app

CONFIG += c++14

# additional modules are pulled in via arcgisruntime.pri
QT += core gui quickwidgets widgets qml quick opengl

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
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

#-------------------------------------------------------------------------------

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ColoredMapWidget/release/ -lColoredMapWidget
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ColoredMapWidget/debug/ -lColoredMapWidget
else:unix: LIBS += -L$$OUT_PWD/../ColoredMapWidget/ -lColoredMapWidget

INCLUDEPATH += $$PWD/../ColoredMapWidget
DEPENDPATH += $$PWD/../ColoredMapWidget

unix:{
    copydata.commands = $(COPY_DIR) $$PWD/resources $$OUT_PWD
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}
