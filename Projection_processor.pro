QT += core gui opengl testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += "DATA_ROOT=\\\"C:/Projects/Gafarov/projection-processor/\\\""

CONFIG += c++11

TARGET = Projection_processor
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    objobject.cpp \
    objprocessor.cpp \
    polygon.cpp \
    kdtreenode.cpp \
    kdtree.cpp \
    kdtreetests.cpp \
    mainwindow.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


include(../Andrew/WViewport3D/WContext/WContextNavigation.pri)
include(../Andrew/Wrap3Framework/WGLGeomDataRendererTests/WGLMaterialSurface/WGLMaterialSurface.pri)
include(../Andrew/Wrap3Framework/WGLGeomDataRendererTests/WGLMaterialWireframe/WGLMaterialWireframe.pri)
include(../Andrew/Wrap3Framework/WGLGeomDataRendererTests/WGLDataGeomStackTriangulated/WGLDataGeomStackTriangulated.pri)
include(../Andrew/Wrap3Framework/WGLObjectRendererTests01/WGLObjectRenderer/WGLObjectRenderer.pri)
include(../Andrew/Wrap3Framework/WGLGridTests/WGLGrid/WGLGrid.pri)
include(../Andrew/Wrap3Framework/Shaders/WGLShaderConst/WGLShaderConst.pri)
include(../Andrew/Wrap3Framework/WGLDots/WGLDots/WGLDots.pri)

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    objobject.h \
    objprocessor.h \
    polygon.h \
    kdtreenode.h \
    kdtree.h \
    kdtreetests.h \
    mainwindow.h

FORMS    += mainwindow.ui
