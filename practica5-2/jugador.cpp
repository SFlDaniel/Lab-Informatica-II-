#include "jugador.h"

Jugador::Jugador(QString nombreIn,
                 double xIn,
                 double yIn,
                 double vidaIn)
{
    nombre = nombreIn;

    x = xIn;
    y = yIn;

    vida = vidaIn;
}

void Jugador::agregarInfraestructura(
    Infraestructura *i)
{
    infraestructuras.push_back(i);
}

bool Jugador::derrotado()
{
    if (infraestructuras.empty()) return false;
    for (auto* i : infraestructuras)
        if (!i->destruido()) return false;
    return true;
}

void Jugador::recibirDanio(
    double danio)
{
    vida -= danio;

    if(vida < 0)
    {
        vida = 0;
    }
}

QString Jugador::getNombre()
{
    return nombre;
}

double Jugador::getX()
{
    return x;
}

double Jugador::getY()
{
    return y;
}

double Jugador::getVida()
{
    return vida;
}

std::vector<Infraestructura*>&
Jugador::getInfraestructuras()
{
    return infraestructuras;
}