#include "red.h"

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