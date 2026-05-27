QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
        fisica.cpp \
        gamewindow.cpp \
        main.cpp \
        obstaculo.cpp \
        particula.cpp
HEADERS += \
    fisica.h \
    gamewindow.h \
    obstaculo.h \
    particula.h