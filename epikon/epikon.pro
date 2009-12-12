# -------------------------------------------------
# Project created by QtCreator 2009-12-03T09:07:15
# -------------------------------------------------
QT += network \
    svg \
    phonon
TARGET = epikon
TEMPLATE = app
SOURCES += main.cpp \
    epikonmainwindow.cpp \
    epikongame.cpp \
    epikonplayer.cpp \
    epikonplanet.cpp \
    epikongamescene.cpp \
    epikonplanetitem.cpp \
    epikonattack.cpp \
    epikonshipitem.cpp \
    epikonserver.cpp \
    epikonconnectionmanager.cpp \
    epikonclient.cpp
HEADERS += epikonmainwindow.h \
    epikongame.h \
    epikonplayer.h \
    epikonplanet.h \
    epikongamescene.h \
    epikonplanetitem.h \
    epikonattack.h \
    epikonshipitem.h \
    epikonserver.h \
    epikonconnectionmanager.h \
    epikonclient.h
FORMS += epikonmainwindow.ui
RESOURCES += resources.qrc
