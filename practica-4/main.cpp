#include <iostream>
#include <limits>
#include "red.h"

using namespace std;

int main() {
    Red red;
    string archivo;
    cout << "Ingrese nombre del archivo de topologia: ";
    cin >> archivo;
    red.cargarDesdeArchivo(archivo);
    red.actualizarTablas();
    int opcion = 0;
    while (true) {
        cout << "\n========== MENU ==========\n";
        cout << "1. Mostrar topologia\n";
        cout << "2. Mostrar tablas de costos\n";
        cout << "3. Agregar conexion\n";
        cout << "4. Eliminar conexion\n";
        cout << "5. Mostrar distancias desde un router\n";
        cout << "6. Mostrar camino entre routers\n";
        cout << "7. Agregar router\n";
        cout << "8. Eliminar router\n";
        cout << "9. Actualizar tablas\n";
        cout << "0. Salir\n";
        cout << "\nOpcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Entrada invalida\n";
            continue;
        }

        if (opcion == 0) {
            break;
        }

        switch (opcion) {

        case 1: {
            cout << "\n===== TOPOLOGIA =====\n";
            red.mostrarRed();
            break;
        }

        case 2: {
            cout << "\n===== TABLAS =====\n";
            red.mostrarTablas();
            break;
        }

        case 3: {
            string r1, r2;
            int costo;

            cout << "\nRouter origen: ";
            cin >> r1;
            cout << "Router destino: ";
            cin >> r2;
            cout << "Costo: ";
            cin >> costo;

            red.conectarRouters(r1, r2, costo);
            red.actualizarTablas();
            cout << "Conexion agregada\n";

            break;
        }

        case 4: {
            string r1, r2;

            cout << "\nRouter 1: ";
            cin >> r1;
            cout << "Router 2: ";
            cin >> r2;
            red.eliminarConexion(r1, r2);
            red.actualizarTablas();
            cout << "Conexion eliminada\n";

            break;
        }

        case 5: {
            string origen;
            cout << "\nIngrese router origen: ";
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

                if (par.second ==
                    numeric_limits<int>::max()) {
                    cout << "INF";
                }
                else {
                    cout << par.second;
                }
                cout << endl;
            }

            break;
        }

        case 6: {
            string origen, destino;
            cout << "\nRouter origen: ";
            cin >> origen;
            cout << "Router destino: ";
            cin >> destino;
            red.mostrarCamino(origen, destino);
            break;
        }

        case 7: {
            string id;
            cout << "\nID del nuevo router: ";
            cin >> id;
            red.agregarRouter(id);
            cout << "Router agregado\n";
            break;
        }

        case 8: {
            string id;
            cout << "\nID del router a eliminar: ";
            cin >> id;
            red.eliminarRouter(id);
            red.actualizarTablas();
            cout << "Router eliminado\n";
            break;
        }

        case 9: {
            red.actualizarTablas();
            cout << "Tablas actualizadas\n";
            break;
        }

        default:
            cout << "Opcion invalida\n";
        }
    }
    return 0;
}