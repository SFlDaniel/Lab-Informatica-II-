#include "red.h"

void Red::agregarRouter(string id) {
    routers.insert({id, Router(id)});
}

void Red::eliminarRouter(string id) {
    routers.erase(id);
}