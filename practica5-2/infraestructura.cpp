#include "infraestructura.h"

Infraestructura::Infraestructura(
    double xIn,
    double yIn,
    double anchoIn,
    double altoIn,
    double resistenciaIn,
    double restitucionIn)
{
    x = xIn;
    y = yIn;

    ancho = anchoIn;
    alto = altoIn;

    resistencia = resistenciaIn;

    restitucion = restitucionIn;
}

bool Infraestructura::detectarColision(
    double px,
    double py)
{
    return (
        px >= x &&
        px <= x + ancho &&
        py >= y &&
        py <= y + alto
        );
}

void Infraestructura::recibirDanio(
    double danio)
{
    resistencia -= danio;

    if(resistencia < 0)
    {
        resistencia = 0;
    }
}

bool Infraestructura::destruido()
{
    return resistencia <= 0;
}

double Infraestructura::getX()
{
    return x;
}

double Infraestructura::getY()
{
    return y;
}

double Infraestructura::getAncho()
{
    return ancho;
}

double Infraestructura::getAlto()
{
    return alto;
}

double Infraestructura::getResistencia()
{
    return resistencia;
}

double Infraestructura::getRestitucion()
{
    return restitucion;
}