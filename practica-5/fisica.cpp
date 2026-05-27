#include "fisica.h"

Fisica::Fisica()
{

}

void Fisica::agregarParticula(Particula *p)
{
    particulas.push_back(p);
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
    }

    detectarColisiones();
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