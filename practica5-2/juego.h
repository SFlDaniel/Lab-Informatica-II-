#ifndef JUEGO_H
#define JUEGO_H

#include "jugador.h"
#include "fisica.h"

class Juego
{
private:

    Jugador jugador1;

    Jugador jugador2;

    Fisica fisica;

    int turnoActual;

public:

    Juego();

    void cambiarTurno();

    int getTurnoActual();

    Jugador& getJugadorActual();

    Jugador& getJugadorRival();

    bool verificarVictoria();

    bool proyectilEnVuelo;

    Jugador* obtenerGanador();

    void disparar(double x,
                  double y,
                  double velocidad,
                  double angulo,
                  double masa);

    Fisica& getFisica();

    Jugador& getJugador1();

    Jugador& getJugador2();
};

#endif