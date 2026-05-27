#include "particula.h"

#include <cmath>

Particula::Particula(double xIn,
                     double yIn,
                     double velocidad,
                     double angulo,
                     double masaIn)
{
    x = xIn;
    y = yIn;

    masa = masaIn;

    radio = 10;

    gravedad = 9.81;

    velX = velocidad * cos(angulo * M_PI/180);

    velY = velocidad * sin(angulo * M_PI/180);
}

void Particula::actualizar(double dt)
{
    x += velX * dt;

    velY -= gravedad * dt;

    y += velY * dt;
}

void Particula::reboteHorizontal()
{
    velX *= -1;
}

void Particula::reboteVertical(double restitucion)
{
    velY *= -restitucion;
}

bool Particula::detectarColision(Particula *otra)
{
    double dx = otra->x - x;

    double dy = otra->y - y;

    double distancia = sqrt(dx*dx + dy*dy);

    return distancia <= (radio + otra->radio);
}

void Particula::fusionar(Particula *otra)
{
    double nuevaMasa = masa + otra->masa;

    velX = (masa*velX + otra->masa*otra->velX)
           / nuevaMasa;

    velY = (masa*velY + otra->masa*otra->velY)
           / nuevaMasa;

    masa = nuevaMasa;
}

double Particula::getX()
{
    return x;
}

double Particula::getY()
{
    return y;
}

double Particula::getVelX()
{
    return velX;
}

double Particula::getVelY()
{
    return velY;
}

double Particula::getRadio()
{
    return radio;
}

double Particula::getMasa()
{
    return masa;
}

void Particula::setPosicion(double xIn, double yIn)
{
    x = xIn;
    y = yIn;
}