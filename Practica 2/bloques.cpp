#include <iostream>
#include "bloques.h"

using namespace std;

int longitud(const char *cad)
{
    int i = 0;

    while (*(cad + i) != '\0')
        i++;

    return i;
}

int sumarBloques(const char *cadena, int n)
{
    int len = longitud(cadena);

    int resto = len % n;
    int ceros = 0;

    if (resto != 0)
        ceros = n - resto;

    int nuevaLen = len + ceros;

    char *nueva = new char[nuevaLen + 1];

    int k = 0;

    for (int i = 0; i < ceros; i++)
    {
        *(nueva + k) = '0';
        k++;
    }

    for (int i = 0; i < len; i++)
    {
        *(nueva + k) = *(cadena + i);
        k++;
    }

    *(nueva + nuevaLen) = '\0';

    int suma = 0;

    for (int i = 0; i < nuevaLen; i += n)
    {
        int num = 0;

        for (int j = 0; j < n; j++)
        {
            num = num * 10 + (*(nueva + i + j) - '0');
        }
        suma += num;
    }
    delete[] nueva;

    return suma;
}