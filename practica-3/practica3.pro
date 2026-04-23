QT       -= gui

CONFIG   += console c++17
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
           rle.cpp \
           lz78.cpp \
           crypto.cpp

HEADERS += rle.h \
           lz78.h \
           crypto.h