#include <iostream>
#include "red.h"

using namespace std;

int main() {

    Red red;

    int cantidadRouters;
    cout << "Cantidad de routers: ";
    cin >> cantidadRouters;

    // Agregar routers
    for (int i = 0; i < cantidadRouters; i++) {

        string id;

        cout << "Ingrese ID del router "
             << i + 1
             << ": ";

        cin >> id;

        red.agregarRouter(id);
    }

    int conexiones;

    cout << "\nCantidad de conexiones: ";
    cin >> conexiones;

    // Conectar routers
    for (int i = 0; i < conexiones; i++) {

        string r1, r2;
        int costo;

        cout << "\nConexion "
             << i + 1
             << endl;

        cout << "Router origen: ";
        cin >> r1;

        cout << "Router destino: ";
        cin >> r2;

        cout << "Costo: ";
        cin >> costo;

        red.conectarRouters(r1, r2, costo);
    }

    cout << "\n===== TOPOLOGIA =====\n";

    red.mostrarRed();

    // Actualizar tablas
    red.actualizarTablas();

    cout << "\n===== TABLAS =====\n";

    red.mostrarTablas();

    // Dijkstra
    string origen;

    cout << "\nIngrese router origen para Dijkstra: ";
    cin >> origen;

    map<string, int> distancias =
        red.dijkstra(origen);

    cout << "\nDistancias desde "
         << origen
         << ":\n";

    for (auto &par : distancias) {

        cout << origen
             << " -> "
             << par.first
             << " = ";

        if (par.second == numeric_limits<int>::max()) {

            cout << "INF";
        }
        else {

            cout << par.second;
        }

        cout << endl;
    }

    return 0;
}