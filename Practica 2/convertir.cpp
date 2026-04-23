#include <iostream>
#include "convertir.h"

using namespace std;

void intACadena(int numero, char *&cadena)

{
    int temp = numero;
    int digitos = 0;

    if(temp == 0)
    {
        digitos = 1;
    }
    else
    {
        while(temp != 0)
        {
            temp /= 10;
            digitos++;
        }
    }
    cadena = new char[digitos + 1];
    cadena[digitos] = '\0';
    temp = numero;

    for(int i = digitos - 1; i >= 0; i--)
    {
        int dig = temp % 10;

        *(cadena + i) = dig + '0';
        temp /= 10;
    }
}