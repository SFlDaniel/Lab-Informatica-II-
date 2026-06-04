#ifndef INFRAESTRUCTURA_H
#define INFRAESTRUCTURA_H

class Infraestructura
{
private:

    double x;
    double y;

    double ancho;
    double alto;

    double resistencia;

    double restitucion;
public:
    Infraestructura(double x,
                    double y,
                    double ancho,
                    double alto,
                    double resistencia,
                    double restitucion);

    bool detectarColision(double px,
                          double py);

    void recibirDanio(double danio);

    bool destruido();

    double getX();
    double getY();

    double getAncho();
    double getAlto();

    double getResistencia();

    double getRestitucion();
};

#endif // INFRAESTRUCTURA_H
