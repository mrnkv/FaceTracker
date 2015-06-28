#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T17:55:15
#
#-------------------------------------------------


CONFIG += c++11


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceTracker
TEMPLATE = app


SOURCES += main.cpp\
    controllers/basecontroller.cpp \
    controllers/cameracontroller.cpp \
    views/setupview.cpp \
    views/statistictimes.cpp \
    views/trayicon.cpp \
    controllers/sysidlecontroller.cpp \
    controllers/timecounter.cpp

HEADERS  += views/setupview.h \
    views/statistictimes.h \
    views/trayicon.h \
    controllers/basecontroller.h \
    controllers/cameracontroller.h \
    controllers/sysidlecontroller.h \
    controllers/timecounter.h

FORMS    += forms/setupview.ui \
    forms/statistictimes.ui

unix{
    LIBS += -lX11 -lXss
    PKGCONFIG += opencv
    CONFIG += link_pkgconfig
}

RESOURCES += \
    resources.qrc
