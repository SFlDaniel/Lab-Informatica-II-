#include <iostream>
#include "red.h"

using namespace std;

int main() {

    Red red;

    red.agregarRouter("A");
    red.agregarRouter("B");
    red.agregarRouter("C");
    red.agregarRouter("D");

    red.conectarRouters("A", "B", 4);
    red.conectarRouters("A", "C", 10);
    red.conectarRouters("A", "D", 5);

    red.conectarRouters("B", "C", 3);
    red.conectarRouters("B", "D", 1);

    red.conectarRouters("C", "D", 2);

    red.mostrarRed();

    red.actualizarTablas();
//Tbala

    red.mostrarTablas();
//dijkstra

    cout << "Distancia desde A";

    map<string, int> distancias = red.dijkstra("A");

    for (auto &par : distancias) {

        cout << "A -> "
             << par.first
             << " = "
             << par.second
             << endl;
    }

    return 0;
}