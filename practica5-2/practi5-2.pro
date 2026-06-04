QT += core gui widgets
QT += widgets

CONFIG += c++17

SOURCES += \
    fisica.cpp \
    gamewindow.cpp \
    infraestructura.cpp \
    juego.cpp \
    jugador.cpp \
    main.cpp \
    panelcontrol.cpp \
    proyectil.cpp

HEADERS += \
    fisica.h \
    gamewindow.h \
    infraestructura.h \
    juego.h \
    jugador.h \
    panelcontrol.h \
    proyectil.h

TARGET = Practica5Parte2

TEMPLATE = app