#include "fisica.h"

Fisica::Fisica()
{
    factorDanio = 0.05;
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

void Fisica::actualizarSistema(
    double dt,
    double ancho,
    double alto)
{
    for(auto p : proyectiles)
    {
        p->actualizar(dt);

        if(p->getX() <= 0 ||
            p->getX() >= ancho)
        {
            p->reboteHorizontal();
        }

        if(p->getY() <= 0 ||
            p->getY() >= alto)
        {
            p->reboteVertical(1.0);
        }

        for(auto i : infraestructuras)
        {
            if(i->detectarColision(
                    p->getX(),
                    p->getY()))
            {
                double danio =
                    calcularDanio(p);

                i->recibirDanio(
                    danio);

                p->reboteVertical(
                    i->getRestitucion());
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