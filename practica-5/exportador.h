#ifndef EXPORTADOR_H
#define EXPORTADOR_H

#include <fstream>

#include "fisica.h"

class Exportador
{
private:

    std::ofstream archivo;

public:

    Exportador(const char* nombre);

    void guardar(Fisica& sistema,
                 double tiempo);

    void cerrar();
};

#endif