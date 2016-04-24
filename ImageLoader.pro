#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T12:53:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjectRecognizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../_DefaultLibrary/io.cpp \
    ../_DefaultLibrary/text.cpp \
    graphicssceneex.cpp \
    graphicsviewex.cpp

HEADERS  += mainwindow.h \
    ../_DefaultLibrary/io.h \
    ../_DefaultLibrary/text.h \
    graphicssceneex.h \
    graphicsviewex.h

FORMS    += mainwindow.ui
