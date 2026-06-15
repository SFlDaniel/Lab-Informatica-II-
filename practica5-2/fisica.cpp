#include "fisica.h"

#include <cmath>

Fisica::Fisica()
{
    factorDanio = 0.01;
}

void Fisica::agregarProyectil(
    Proyectil *p)
{
    proyectiles.push_back(p);
}

void Fisica::agregarInfraestructura(
    Infraestructura *i)
{
    infraestructuras.push_back(i);
}

double Fisica::calcularDanio(
    Proyectil *p)
{
    return factorDanio *
           p->getMasa() *
           p->getVelocidad();
}

void Fisica::colisionProyectilInfraestructura(Proyectil *p, Infraestructura *i)
{
    if (p->getPropietario() == i->getPropietario()) return;

    double danio = calcularDanio(p);
    i->recibirDanio(danio);

    double e = 0.5;

    // Determinar lado por velocidad dominante
    double solapX = std::min(std::fabs(p->getX() - i->getX()),
                             std::fabs(p->getX() - (i->getX() + i->getAncho())));
    double solapY = std::min(std::fabs(p->getY() - i->getY()),
                             std::fabs(p->getY() - (i->getY() + i->getAlto())));

    if (solapX < solapY)
        p->reboteHorizontal(e);
    else
        p->reboteVertical(e);
}

void Fisica::actualizarSistema(
    double dt,
    double ancho,
    double alto)
{
    for(auto p : proyectiles)
    {
        p->actualizar(dt);

        // Choques perfectamente elásticos
        // contra límites

        if(p->getX() <= 0
            || p->getX() >= ancho)
        {
            p->reboteHorizontal(1.0);
        }

        if(p->getY() <= 0
            || p->getY() >= alto)
        {
            p->reboteVertical(1.0);
        }

        // Infraestructura

        for(auto i : infraestructuras)
        {
            if(i->destruido())
            {
                continue;
            }

            if(i->detectarColision(
                    p->getX(),
                    p->getY()))
            {
                colisionProyectilInfraestructura(
                    p,
                    i);
            }
        }
    }
}

std::vector<Proyectil*>&
Fisica::getProyectiles()
{
    return proyectiles;
}

std::vector<Infraestructura*>&
Fisica::getInfraestructuras()
{
    return infraestructuras;
}