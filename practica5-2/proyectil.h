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
    int propietario;

public:

    Proyectil(double x,
              double y,
              double velocidad,
              double angulo,
              double masa,
              int propietario);

    void actualizar(double dt);

    void reboteHorizontal(double restitucion);

    void reboteVertical(double restitucion);

    double getX();
    double getY();

    double getVelX();
    double getVelY();

    double getMasa();

    double getVelocidad();

    int getPropietario();

    void setPosicion(double x,
                     double y);
};

#endif