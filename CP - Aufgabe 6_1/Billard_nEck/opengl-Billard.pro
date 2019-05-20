#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lOpengl32

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



SOURCES += main.cpp\
    kugel.cpp \
        mainwindow.cpp \
    oglwidget.cpp \
    vector3.cpp

HEADERS  += mainwindow.h \
    kugel.h \
    oglwidget.h \
    vector3.h

FORMS    += mainwindow.ui
