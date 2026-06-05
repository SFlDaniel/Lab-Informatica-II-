#ifndef FISICA_H
#define FISICA_H

#include <vector>

#include "proyectil.h"
#include "infraestructura.h"

class Fisica
{
private:

    std::vector<Proyectil*> proyectiles;

    std::vector<Infraestructura*> infraestructuras;

    double factorDanio;

    void colisionProyectilInfraestructura(
        Proyectil* p,
        Infraestructura* i);

public:

    Fisica();

    void agregarProyectil(
        Proyectil* p);

    void agregarInfraestructura(
        Infraestructura* i);

    void actualizarSistema(
        double dt,
        double ancho,
        double alto);

    double calcularDanio(
        Proyectil* p);

    std::vector<Proyectil*>&
    getProyectiles();

    std::vector<Infraestructura*>&
    getInfraestructuras();
};

#endif