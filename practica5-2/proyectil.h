#ifndef PROYECTIL_H
#define PROYECTIL_H

class Proyectil
{
private:

    double x;
    double y;

    double velX;
    double velY;

    double masa;

    double gravedad;

public:

    Proyectil(double x,
              double y,
              double velocidad,
              double angulo,
              double masa);

    void actualizar(double dt);

    void reboteHorizontal();

    void reboteVertical(double restitucion);

    double getX();
    double getY();

    double getVelX();
    double getVelY();

    double getMasa();

    double getVelocidad();

    void setPosicion(double x,
                     double y);
};

#endif