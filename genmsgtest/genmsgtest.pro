TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        ../generate_messages/simulation.cpp \
        ../generate_messages/message.cpp \
    ../database/dbtool.cpp \
    ../database/dbtable.cpp \
    ../database/dbevent.cpp \
    ../database/dbudp.cpp \
    ../database/data.cpp  \
    ../process_messages/event.cpp

HEADERS += \
        ../generate_messages/simulation.h \
        ../generate_messages/message.h \
    ../database/dbtool.h \
    ../database/dbtable.h \
    ../database/dbevent.h \
    ../database/dbudp.h \
    ../database/data.h \
    ../process_messages/event.h

LIBS += -l sqlite3

SOURCES += ../gtest/googletest/src/gtest-all.cc

INCLUDEPATH +=  ../gtest                                   \
                ../gtest/googletest                        \
                ../gtest/googletest/include                \
                ../gtest/googletest/include/gtest          \
                ../gtest/googletest/include/gtest/gtest.h
