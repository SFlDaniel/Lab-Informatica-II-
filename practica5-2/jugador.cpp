#include "jugador.h"

Jugador::Jugador(QString nombreIn)
{
    nombre = nombreIn;
}

void Jugador::agregarInfraestructura(
    Infraestructura *i)
{
    infraestructuras.push_back(i);
}

bool Jugador::derrotado()
{
    for(auto i : infraestructuras)
    {
        if(!i->destruido())
        {
            return false;
        }
    }

    return true;
}

QString Jugador::getNombre()
{
    return nombre;
}

std::vector<Infraestructura*>&
Jugador::getInfraestructuras()
{
    return infraestructuras;
}