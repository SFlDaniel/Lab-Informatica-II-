#include "exportador.h"

Exportador::Exportador(const char *nombre)
{
    archivo.open(nombre);
}

void Exportador::guardar(Fisica &sistema,
                         double tiempo)
{
    for(auto p : sistema.getParticulas())
    {
        archivo
            << tiempo << " "
            << p->getX() << " "
            << p->getY()
            << std::endl;
    }
}

void Exportador::cerrar()
{
    archivo.close();
}

