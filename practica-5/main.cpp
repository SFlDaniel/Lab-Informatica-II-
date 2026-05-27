#include <iostream>

#include "fisica.h"

using namespace std;
///prueba
int main()
{
    Fisica sistema;

    sistema.agregarParticula(
        new Particula(0,0,100,45,10));

    sistema.agregarParticula(
        new Particula(50,50,80,135,20));

    for(int i=0;i<100;i++)
    {
        sistema.actualizarSistema(0.1,
                                  800,
                                  600);

        cout << "Paso "
             << i
             << endl;
    }

    return 0;
}