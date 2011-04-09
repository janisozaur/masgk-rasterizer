#-------------------------------------------------
#
# Project created by QtCreator 2011-03-17T00:07:59
#
#-------------------------------------------------

QT       += core gui script

TARGET = rasterizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rasterizerinterface.cpp \
    rasterizer.cpp \
    colorvertex.cpp \
    qscriptctors.cpp \
    vertexprocessor.cpp \
    box.cpp \
    sphere.cpp \
    cylinder.cpp

HEADERS  += mainwindow.h \
    rasterizerinterface.h \
    rasterizer.h \
    colorvertex.h \
    qscriptctors.h \
    vertexprocessor.h \
    box.h \
    sphere.h \
    cylinder.h

FORMS    += mainwindow.ui
