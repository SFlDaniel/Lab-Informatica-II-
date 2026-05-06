#ifndef RED_H
#define RED_H

#include <map>
#include <string>
#include <vector>
#include <limits>
#include "Router.h"

using namespace std;

class Red {
private:
    map<string, Router> routers;

public:
    //Se gestionara el router
    void agregarRouter(string id);
    void eliminarRouter(string id);

    //control de Conexiones
    void conectarRouters(string id1, string id2, int costo);
    void eliminarConexion(string id1, string id2);

    // Visualización de la red
    void mostrarRed();

    // Algoritmo de caminos
    map<string, int> dijkstra(string origen);
};

#endif