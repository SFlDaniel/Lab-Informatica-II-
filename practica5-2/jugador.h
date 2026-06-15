#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>
#include <vector>

#include "infraestructura.h"

class Jugador
{
private:

    QString nombre;

    double x;
    double y;

    double vida;

    std::vector<Infraestructura*> infraestructuras;

public:

    Jugador(QString nombre,
            double x,
            double y,
            double vida);

    void agregarInfraestructura(
        Infraestructura* i);

    bool derrotado();

    void recibirDanio(
        double danio);

    QString getNombre();

    double getX();
    double getY();

    double getVida();

    std::vector<Infraestructura*>&
    getInfraestructuras();
};

#endif