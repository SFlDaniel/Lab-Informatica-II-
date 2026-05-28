#include "exportador.h"

Exportador::Exportador(const char* nombre)
{
    archivo.open(nombre);
    if (archivo.is_open()) {
        archivo << "# SIMULACION DE COLISIONES MULTIPLES\n";
        archivo << "# tiempo  id  x  y  velX  velY  masa\n";
        archivo << "#--------------------------------------------------\n";
    }
}

void Exportador::guardar(Fisica& sistema, double tiempo)
{
    if (!archivo.is_open()) return;

    auto& ps = sistema.getParticulas();
    size_t n = ps.size();

    for (size_t i = 0; i < n; i++) {
        archivo << tiempo           << "  "
                << i                << "  "
                << ps[i]->getX()    << "  "
                << ps[i]->getY()    << "  "
                << ps[i]->getVelX() << "  "
                << ps[i]->getVelY() << "  "
                << ps[i]->getMasa() << "\n";
    }
}

void Exportador::cerrar()
{
    if (archivo.is_open()) archivo.close();
}