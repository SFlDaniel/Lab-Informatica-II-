#ifndef FISICA_H
#define FISICA_H

#include <vector>
#include "particula.h"
#include "obstaculo.h"

class Fisica
{
private:

    std::vector<Particula*> particulas;
    std::vector<Obstaculo*> obstaculos;

public:

    Fisica();

    void agregarParticula(Particula* p);
    void agregarObstaculo(Obstaculo* o);

    void actualizarSistema(double dt,
                           double ancho,
                           double alto);

    void detectarColisiones();

    std::vector<Particula*>& getParticulas();
};

#endif