#-------------------------------------------------
#
# Project created by QtCreator 2019-04-09T11:35:13
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    ../process_messages/parse.cpp \
    ../process_messages/event.cpp \
    ../process_messages/trigger.cpp \
    singleday_widget.cpp \
    ../database/dbtool.cpp \
    ../database/dbtable.cpp \
    ../database/dbevent.cpp \
    ../database/dbudp.cpp \
    ../database/data.cpp \
    current_widget.cpp \
    historymainwidget.cpp \
    multipledaywidget.cpp \
    dialog.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot.h \
    ../process_messages/parse.h \
    ../process_messages/event.h \
    ../process_messages/trigger.h \
    singleday_widget.h \
    ../database/dbtool.h \
    ../database/dbtable.h \
    ../database/dbevent.h \
    ../database/dbudp.h \
    ../database/data.h \
    current_widget.h \
    historymainwidget.h \
    multipledaywidget.h \
    dialog.h

FORMS += \
        mainwindow.ui \
    singleday_widget.ui \
    current_widget.ui \
    historymainwidget.ui \
    multipledaywidget.ui \
    dialog.ui

LIBS += -l sqlite3

RESOURCES += \
    res.qrc
