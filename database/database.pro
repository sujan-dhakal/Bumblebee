TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    dbtable.cpp \
    dbtool.cpp \
    dbevent.cpp \
    dbudp.cpp \
    ../process_messages/event.cpp \
    data.cpp

HEADERS += \
    dbtable.h \
    dbtool.h \
    dbevent.h \
    dbudp.h \
    ../process_messages/event.h \
    data.h

LIBS += -l sqlite3
