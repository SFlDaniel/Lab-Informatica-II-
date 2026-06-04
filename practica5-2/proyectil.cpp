#include "proyectil.h"

#include <cmath>

Proyectil::Proyectil(double xIn,
                     double yIn,
                     double velocidad,
                     double angulo,
                     double masaIn)
{
    x = xIn;
    y = yIn;

    masa = masaIn;

    gravedad = 9.81;

    velX = velocidad *
           cos(angulo * M_PI / 180);

    velY = velocidad *
           sin(angulo * M_PI / 180);
}