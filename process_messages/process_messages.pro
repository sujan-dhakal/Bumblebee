TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    event.cpp \
    parse.cpp \
    trigger.cpp \
    ../database/dbtool.cpp \
    ../database/dbtable.cpp \
    ../database/dbevent.cpp \
    ../database/dbudp.cpp \
    ../database/data.cpp

HEADERS += \
    event.h \
    parse.h \
    trigger.h \
    ../database/dbtool.h \
    ../database/dbtable.h \
    ../database/dbevent.h \
    ../database/dbudp.h \
    ../database/data.h

LIBS += -l sqlite3
