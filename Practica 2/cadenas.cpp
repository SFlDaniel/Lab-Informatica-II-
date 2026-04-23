#include <iostream>
#include "cadenas.h"

using namespace std;

bool compararCadenas(const char *cad1, const char *cad2)
{
    const char *p1 = cad1;
    const char *p2 = cad2;

    int len1 = 0;
    int len2 = 0;

    while (*(p1 + len1) != '\0')
        len1++;

    while (*(p2 + len2) != '\0')
        len2++;

    if (len1 != len2)
        return false;

    for (int i = 0; i < len1; i++)
    {
        if (*(p1 + i) != *(p2 + i))
            return false;
    }

    return true;
}