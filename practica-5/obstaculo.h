#ifndef OBSTACULO_H
#define OBSTACULO_H

class Obstaculo
{
private:

    double x;
    double y;

    double ancho;
    double alto;

    double restitucion;

public:

    Obstaculo(double x,
              double y,
              double ancho,
              double alto,
              double restitucion);

    bool detectarColision(double px,
                          double py,
                          double radio);

    double getRestitucion();

};

#endif