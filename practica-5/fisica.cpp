#include "fisica.h"
#include <cmath>

Fisica::Fisica()
{

}

void Fisica::agregarParticula(Particula *p)
{
    particulas.push_back(p);
}

void Fisica::agregarObstaculo(Obstaculo *o)
{
    obstaculos.push_back(o);
}

void Fisica::actualizarSistema(double dt,
                               double ancho,
                               double alto)
{
    for(auto p : particulas)
    {
        p->actualizar(dt);

        // Rebotes horizontales
        if(p->getX() <= 0 ||
            p->getX() >= ancho)
        {
            p->reboteHorizontal();
        }

        // Rebotes verticales
        if(p->getY() <= 0 ||
            p->getY() >= alto)
        {
            p->reboteVertical(0.8);
        }

        for(auto o : obstaculos)
        {
            if(o->detectarColision(
                    p->getX(),
                    p->getY(),
                    p->getRadio()))
            {
                colisionParticulaObstaculo(p, o);
            }
        }
    }

    detectarColisiones();
}

void Fisica::colisionParticulaObstaculo(
    Particula *p,
    Obstaculo *o)
{
    double px = p->getX();
    double py = p->getY();

    double ox = o->getX();
    double oy = o->getY();

    double ancho = o->getAncho();
    double alto = o->getAlto();

    // Distancias a cada lado
    double izquierda = fabs(px - ox);

    double derecha =
        fabs(px - (ox + ancho));

    double arriba = fabs(py - oy);

    double abajo =
        fabs(py - (oy + alto));

    // Encontrar menor distancia
    double minimo =
        std::min(
            std::min(izquierda, derecha),
            std::min(arriba, abajo));

    // Rebote lateral
    if(minimo == izquierda ||
        minimo == derecha)
    {
        p->reboteHorizontal();
    }
    else
    {
        p->reboteVertical(
            o->getRestitucion());
    }
}

void Fisica::detectarColisiones()
{
    for(size_t i = 0;
         i < particulas.size();
         i++)
    {
        for(size_t j = i + 1;
             j < particulas.size();
             j++)
        {
            if(particulas[i]->detectarColision(particulas[j]))
            {
                particulas[i]->fusionar(particulas[j]);

                delete particulas[j];

                particulas.erase(particulas.begin() + j);

                j--;
            }
        }
    }
}

std::vector<Particula*>&
Fisica::getParticulas()
{
    return particulas;
}