#include <iostream>
#include "repetidos.h"

using namespace std;

void eliminarRepetidos(const char *original, char *&sinRep)
{
    int len = 0;

    while (*(original + len) != '\0')
        len++;

    sinRep = new char[len + 1];

    int k = 0;

    for (int i = 0; i < len; i++)
    {
        bool repetido = false;

        for (int j = 0; j < k; j++)
        {
            if (*(sinRep + j) == *(original + i))
            {
                repetido = true;
                break;
            }
        }

        if (!repetido)
        {
            *(sinRep + k) = *(original + i);
            k++;
        }
    }

    *(sinRep + k) = '\0';
}