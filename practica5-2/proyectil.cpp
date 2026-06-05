#include "proyectil.h"

#include <cmath>

Proyectil::Proyectil(double xIn,
                     double yIn,
                     double velocidad,
                     double angulo,
                     double masaIn,
                     int propietarioIn)
{
    x = xIn;
    y = yIn;

    masa = masaIn;

    propietario = propietarioIn;

    gravedad = 9.81;

    velX = velocidad *
           cos(angulo * M_PI / 180);

    velY = -velocidad *
           sin(angulo * M_PI / 180);
}

void Proyectil::actualizar(double dt)
{
    x += velX * dt;
    velY += gravedad * dt;
    y += velY * dt;
}

void Proyectil::reboteHorizontal(double restitucion)
{
    velX *= -restitucion;
}

void Proyectil::reboteVertical(double restitucion)
{
    velY *= -restitucion;

    if(fabs(velY) < 1)
    {
        velY = 0;
    }
}

double Proyectil::getX()
{
    return x;
}

double Proyectil::getY()
{
    return y;
}

double Proyectil::getVelX()
{
    return velX;
}

double Proyectil::getVelY()
{
    return velY;
}

double Proyectil::getMasa()
{
    return masa;
}

double Proyectil::getVelocidad()
{
    return sqrt(
        velX * velX +
        velY * velY);
}

int Proyectil::getPropietario()
{
    return propietario;
}

void Proyectil::setPosicion(double xIn,
                            double yIn)
{
    x = xIn;
    y = yIn;
}