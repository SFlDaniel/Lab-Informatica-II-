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
    void asegurarRouter(const string& id);
    void dijkstraConPredecesor(
        const string& origen,
        map<string, int>& distancias,
        map<string, string>& predecesor
        ) const;
public:

    void agregarRouter(const string& id);
    void eliminarRouter(const string& id);


    void conectarRouters(const string& id1, const string& id2, int costo);
    void eliminarConexion(const string& id1, const string& id2);
    void cargarDesdeArchivo(const string& nombreArchivo);

    void mostrarRed() const;

    map<string, int> dijkstra(const string& origen) const;

    vector<string> obtenerCamino(const string& origen, const string& destino) const;
    void mostrarCamino(const string& origen, const string& destino) const;

    void actualizarTablas();

    void mostrarTablas() const;
};

#endif