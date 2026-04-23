#include <iostream>
#include "dinero.h"

using namespace std;

void calcularDinero(int cantidad) { int denominaciones[10] = {50000,20000,10000,5000,2000,1000,500,200,100,50};

    int resultado[10] = {0};

    int *pDen = denominaciones;
    int *pRes = resultado;

    for(int i = 0; i < 10; i++)
    {
        *(pRes + i) = cantidad / *(pDen + i);
        cantidad = cantidad % *(pDen + i);
    }

    cout << "Resultado:" << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << *(pDen + i) << " : " << *(pRes + i) << endl;
    }

    if(cantidad > 0)
    {
        cout << "Faltante: " << cantidad << endl;
    }
    else
    {
        cout << "Faltante: 0" << endl;
    }
}