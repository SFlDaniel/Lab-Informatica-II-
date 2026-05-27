#ifndef PARTICULA_H
#define PARTICULA_H

class Particula
{
private:

    double x;
    double y;

    double velX;
    double velY;

    double masa;
    double radio;

    double gravedad;

public:

    Particula(double x,
              double y,
              double velocidad,
              double angulo,
              double masa);

    void actualizar(double dt);

    void reboteHorizontal();

    void reboteVertical(double restitucion);

    bool detectarColision(Particula* otra);

    void fusionar(Particula* otra);

    double getX();
    double getY();

    double getVelX();
    double getVelY();

    double getRadio();

    double getMasa();

    void setPosicion(double x,double y);

};

#endif