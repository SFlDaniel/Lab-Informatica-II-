#ifndef FISICA_H
#define FISICA_H

#include <vector>

#include "particula.h"

class Fisica
{
private:

    std::vector<Particula*> particulas;

public:

    Fisica();

    void agregarParticula(Particula* p);

    void actualizarSistema(double dt,
                           double ancho,
                           double alto);

    void detectarColisiones();

    std::vector<Particula*>& getParticulas();
};

#endif