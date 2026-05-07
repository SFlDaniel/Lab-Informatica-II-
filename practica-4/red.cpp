#include "red.h"

#include <iostream>


void Red::agregarRouter(string id) {
    routers.insert({id, Router(id)});
}

void Red::eliminarRouter(string id) {

    routers.erase(id);

    for (auto &par : routers) {
        par.second.eliminarVecino(id);
    }
}


void Red::conectarRouters(string id1, string id2, int costo) {

    routers[id1].agregarVecino(id2, costo);
    routers[id2].agregarVecino(id1, costo);
}

void Red::eliminarConexion(string id1, string id2) {

    routers[id1].eliminarVecino(id2);
    routers[id2].eliminarVecino(id1);
}


void Red::mostrarRed() {

    cout << "\n===== TOPOLOGIA DE RED =====\n";

    for (auto &par : routers) {
        par.second.imprimirVecinos();
        cout << endl;
    }
}



map<string, int> Red::dijkstra(string origen) {

    map<string, int> distancias;
    map<string, bool> visitado;

    for (auto &par : routers) {

        distancias[par.first] = numeric_limits<int>::max();

        visitado[par.first] = false;
    }

    distancias[origen] = 0;

    for (size_t i = 0; i < routers.size(); i++) {

        string actual;
        int minDist = numeric_limits<int>::max();


        for (auto &par : distancias) {

            if (!visitado[par.first] &&
                par.second < minDist) {

                minDist = par.second;
                actual = par.first;
            }
        }


        if (minDist == numeric_limits<int>::max()) {
            break;
        }

        visitado[actual] = true;


        for (auto &vecino : routers[actual].getVecinos()) {

            string nombre = vecino.first;
            int costo = vecino.second;

            if (distancias[actual] + costo <
                distancias[nombre]) {

                distancias[nombre] =
                    distancias[actual] + costo;
            }
        }
    }

    return distancias;
}



void Red::actualizarTablas() {

    for (auto &par : routers) {

        string origen = par.first;

        map<string, int> distancias =
            dijkstra(origen);

        for (auto &d : distancias) {

            par.second.actualizarCosto(
                d.first,
                d.second
                );
        }
    }
}


void Red::mostrarTablas() {

    cout << "\n===== TABLAS DE COSTOS =====\n";

    for (auto &par : routers) {

        par.second.imprimirTabla();

        cout << endl;
    }
}