#include "obstaculo.h"

Obstaculo::Obstaculo(double xIn,
                     double yIn,
                     double anchoIn,
                     double altoIn,
                     double restitucionIn)
{
    x = xIn;
    y = yIn;

    ancho = anchoIn;
    alto = altoIn;

    restitucion = restitucionIn;
}

bool Obstaculo::detectarColision(double px,
                                 double py,
                                 double radio)
{
    return (px + radio >= x &&
            px - radio <= x + ancho &&
            py + radio >= y &&
            py - radio <= y + alto);
}

double Obstaculo::getRestitucion()
{
    return restitucion;
}

double Obstaculo::getX()
{
    return x;
}

double Obstaculo::getY()
{
    return y;
}

double Obstaculo::getAncho()
{
    return ancho;
}

double Obstaculo::getAlto()
{
    return alto;
}