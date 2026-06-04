#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>

#include "infraestructura.h"

class Jugador
{
private:

    QString nombre;

    std::vector<Infraestructura*> infraestructuras;

public:

    Jugador(QString nombre);

    void agregarInfraestructura(
        Infraestructura* i);

    bool derrotado();

    QString getNombre();

    std::vector<Infraestructura*>&
    getInfraestructuras();
};

#endif