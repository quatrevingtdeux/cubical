#-------------------------------------------------
#
# Project created by QtCreator 2011-05-12T12:34:42
#
#-------------------------------------------------

QT       += core gui xml opengl

TARGET = cubical
TEMPLATE = app


SOURCES +=\
    main-viewer.cpp \
    main.cpp

HEADERS  += \
    viewer.h \
    Point.h \
    ComplexeCubique.h \
    Cellule.h

LIBS += -lglut -lqglviewer-qt4
