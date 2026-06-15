#include "juego.h"

Juego::Juego()
    :
    jugador1(
        "Jugador 1",
        100,
        50,
        100),

    jugador2(
        "Jugador 2",
        1100,
        50,
        100)
{
    turnoActual = 1;
}

void Juego::cambiarTurno()
{
    if(turnoActual == 1)
    {
        turnoActual = 2;
    }
    else
    {
        turnoActual = 1;
    }
}

int Juego::getTurnoActual()
{
    return turnoActual;
}

Jugador& Juego::getJugadorActual()
{
    if(turnoActual == 1)
    {
        return jugador1;
    }

    return jugador2;
}

Jugador& Juego::getJugadorRival()
{
    if(turnoActual == 1)
    {
        return jugador2;
    }

    return jugador1;
}

bool Juego::verificarVictoria()
{
    return jugador1.derrotado()
    ||
        jugador2.derrotado();
}

Jugador* Juego::obtenerGanador()
{
    if(jugador1.derrotado())
    {
        return &jugador2;
    }

    if(jugador2.derrotado())
    {
        return &jugador1;
    }

    return nullptr;
}

void Juego::disparar(double x,
                     double y,
                     double velocidad,
                     double angulo,
                     double masa)
{
    Proyectil* p =
        new Proyectil(
            x,
            y,
            velocidad,
            angulo,
            masa,
            turnoActual);

    fisica.agregarProyectil(p);

    if (proyectilEnVuelo) return;
    proyectilEnVuelo = true;
}

Fisica& Juego::getFisica()
{
    return fisica;
}

Jugador& Juego::getJugador1()
{
    return jugador1;
}

Jugador& Juego::getJugador2()
{
    return jugador2;
}