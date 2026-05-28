#include <iostream>

#include "fisica.h"
#include "exportador.h"
///prueba
using namespace std;

int main()
{
    Fisica sistema;

    // Partículas
    sistema.agregarParticula(
        new Particula(
            100,
            100,
            80,
            45,
            10));

    sistema.agregarParticula(
        new Particula(
            400,
            200,
            60,
            135,
            20));

    sistema.agregarParticula(
        new Particula(
            300,
            500,
            90,
            70,
            15));

    sistema.agregarParticula(
        new Particula(
            700,
            300,
            75,
            210,
            12));

    // Obstáculos
    sistema.agregarObstaculo(
        new Obstaculo(
            350,
            250,
            120,
            40,
            0.7));

    sistema.agregarObstaculo(
        new Obstaculo(
            600,
            450,
            100,
            50,
            0.6));

    // Exportador
    Exportador exportador(
        "trayectoria.txt");

    double tiempo = 0;
    double dt = 0.1;

    // Simulación
    for(int i = 0; i < 500; i++)
    {
        sistema.actualizarSistema(
            dt,
            1000,
            700);

        exportador.guardar(
            sistema,
            tiempo);

        tiempo += dt;

        // Mostrar posiciones
        cout << "Tiempo: "
             << tiempo
             << endl;

        for(auto p :
             sistema.getParticulas())
        {
            cout
                << "X: "
                << p->getX()
                << " Y: "
                << p->getY()
                << endl;
        }

        cout << "----------------"
             << endl;
    }

    exportador.cerrar();

    return 0;
}