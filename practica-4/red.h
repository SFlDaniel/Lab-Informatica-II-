#ifndef RED_H
#define RED_H

#include <map>
#include <string>
#include "Router.h"

using namespace std;

class Red {
private:
    map<string, Router> routers;

public:
    void agregarRouter(string id);
    void eliminarRouter(string id);
};

#endif