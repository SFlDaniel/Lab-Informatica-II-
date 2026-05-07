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

    void agregarRouter(string id);
    void eliminarRouter(string id);


    void conectarRouters(string id1, string id2, int costo);
    void eliminarConexion(string id1, string id2);
    void mostrarRed();

    map<string, int> dijkstra(string origen);

    void actualizarTablas();

    void mostrarTablas();
};

#endif