#include <iostream>

#include "dinero.h"
#include "cadenas.h"
#include "convertir.h"
#include "repetidos.h"
#include "bloques.h"

using namespace std;

int main()
{
    int opcion;

    do
    {
        cout << "\nMENU\n";
        cout << "1. Problema dinero\n";
        cout << "2. Comparar cadenas\n";
        cout << "3. Convertir int a cadena\n";
        cout << "4. Eliminar repetidos\n";
        cout << "5. Sumar bloques\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion)
        {

        // ===== PROBLEMA 1 =====
        case 1:
        {
            int cantidad;
            cout << "Ingrese cantidad: ";
            cin >> cantidad;

            calcularDinero(cantidad);
            break;
        }

        // ===== PROBLEMA 3 =====
        case 2:
        {
            char cad1[100];
            char cad2[100];

            cout << "Cadena 1: ";
            cin >> cad1;

            cout << "Cadena 2: ";
            cin >> cad2;

            if(compararCadenas(cad1, cad2))
                cout << "Son iguales\n";
            else
                cout << "Son diferentes\n";

            break;
        }

        // ===== PROBLEMA 5 =====
        case 3:
        {
            int numero;
            char *cadena = nullptr;

            cout << "Ingrese numero: ";
            cin >> numero;

            intACadena(numero, cadena);

            cout << "Cadena: " << cadena << endl;

            delete[] cadena;

            break;
        }

        // ===== PROBLEMA 7 =====
        case 4:
        {
            cin.ignore();

            char original[100];
            char *sinRep = nullptr;

            cout << "Ingrese cadena: ";
            cin.getline(original, 100);

            eliminarRepetidos(original, sinRep);

            cout << "Original: " << original << endl;
            cout << "Sin repetidos: " << sinRep << endl;

            delete[] sinRep;

            break;
        }

        // ===== PROBLEMA 9 =====
        case 5:
        {
            int n;
            char cadena[200];

            cout << "Ingrese n: ";
            cin >> n;

            cin.ignore();

            cout << "Ingrese cadena numerica: ";
            cin.getline(cadena, 200);

            int resultado = sumarBloques(cadena, n);

            cout << "Resultado: " << resultado << endl;

            break;
        }

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while(opcion != 0);

    return 0;
}