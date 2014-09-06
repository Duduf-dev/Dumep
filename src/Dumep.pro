#-------------------------------------------------
#
# Project created by QtCreator 2014-08-17T18:10:45
#
#-------------------------------------------------

QT       += core gui\
         multimedia\
         multimediawidgets\
         winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dumep
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videowidget.cpp \
    opener.cpp \
    browser.cpp \
    jumpingslider.cpp \
    params.cpp \
    about.cpp \
    browserthread.cpp

HEADERS  += mainwindow.h \
    videowidget.h \
    opener.h \
    browser.h \
    jumpingslider.h \
    params.h \
    about.h \
    browserthread.h

FORMS    += mainwindow.ui \
    opener.ui \
    params.ui \
    about.ui

RESOURCES += \
    ressources.qrc

OTHER_FILES += \
    ico.rc

RC_FILE = ico.rc
