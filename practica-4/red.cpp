#include "red.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

void Red::asegurarRouter(const std::string& id) {
    if (routers.find(id) == routers.end()) {
        routers.emplace(id, Router(id));
    }
}

void Red::agregarRouter(const std::string& id) {
    asegurarRouter(id);
}

void Red::eliminarRouter(const string& id) {
    routers.erase(id);

    for (auto &par : routers) {
        par.second.eliminarVecino(id);
    }
}


void Red::conectarRouters(const std::string& id1, const std::string& id2, int costo) {
    if (id1 == id2 || costo < 0) {
        return;
    }

    asegurarRouter(id1);
    asegurarRouter(id2);

    routers.at(id1).agregarVecino(id2, costo);
    routers.at(id2).agregarVecino(id1, costo);
}
void Red::eliminarConexion(const std::string& id1,
     const std::string& id2) {

    auto it1 = routers.find(id1);
    auto it2 = routers.find(id2);

    if (it1 == routers.end() || it2 == routers.end()) {
        std::cout << "Uno de los routers no existe\n";
        return;
    }

    it1->second.eliminarVecino(id2);
    it2->second.eliminarVecino(id1);

    std::cout << "Conexion eliminada entre "
    << id1
    << " y "
    << id2
    << "\n";
}

void Red::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return;
    }

    std::string linea;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (linea[0] == '#') {
            continue;
        }

        std::stringstream ss(linea);
        std::string id1, id2;
        int costo;

        if (ss >> id1 >> id2 >> costo) {
            conectarRouters(id1, id2, costo);
        }
    }
}

void Red::mostrarRed() const {
    std::cout << "Topologia";

    for (const auto &par : routers) {
        par.second.imprimirVecinos();
        std::cout << endl;
    }
}

void Red::dijkstraConPredecesor(
    const std::string& origen,
    std::map<std::string, int>& distancias,
    std::map<std::string, std::string>& predecesor
    ) const {
    distancias.clear();
    predecesor.clear();

    if (routers.find(origen) == routers.end()) {
        return;
    }

    std::map<std::string, bool> visitado;

    for (const auto& par : routers) {
        distancias[par.first] = std::numeric_limits<int>::max();
        visitado[par.first] = false;
    }

    distancias[origen] = 0;

    for (size_t i = 0; i < routers.size(); i++) {
        std::string actual;
        int minDist = std::numeric_limits<int>::max();

        for (const auto& par : distancias) {
            if (!visitado[par.first] && par.second < minDist) {
                minDist = par.second;
                actual = par.first;
            }
        }

        if (actual.empty() || minDist == std::numeric_limits<int>::max()) {
            break;
        }

        visitado[actual] = true;

        for (const auto& vecino : routers.at(actual).getVecinos()) {
            const std::string& nombre = vecino.first;
            int costo = vecino.second;

            if (routers.find(nombre) == routers.end()) {
                continue;
            }

            if (distancias[actual] != std::numeric_limits<int>::max() &&
                distancias[actual] + costo < distancias[nombre]) {

                distancias[nombre] = distancias[actual] + costo;
                predecesor[nombre] = actual;
            }
        }
    }
}

std::map<std::string, int> Red::dijkstra(const std::string& origen) const {
    std::map<std::string, int> distancias;
    std::map<std::string, std::string> predecesor;

    dijkstraConPredecesor(origen, distancias, predecesor);
    return distancias;
}

std::vector<std::string> Red::obtenerCamino(const std::string& origen, const std::string& destino) const {
    std::vector<std::string> camino;

    if (routers.find(origen) == routers.end() || routers.find(destino) == routers.end()) {
        return camino;
    }

    std::map<std::string, int> distancias;
    std::map<std::string, std::string> predecesor;

    dijkstraConPredecesor(origen, distancias, predecesor);

    if (distancias.find(destino) == distancias.end() ||
        distancias[destino] == std::numeric_limits<int>::max()) {
        return camino;
    }

    std::string actual = destino;

    while (true) {
        camino.push_back(actual);

        if (actual == origen) {
            break;
        }

        auto it = predecesor.find(actual);
        if (it == predecesor.end()) {
            camino.clear();
            return camino;
        }

        actual = it->second;
    }

    std::reverse(camino.begin(), camino.end());
    return camino;
}

void Red::mostrarCamino(const std::string& origen, const std::string& destino) const {
    std::vector<std::string> camino = obtenerCamino(origen, destino);

    if (camino.empty()) {
        std::cout << "No existe camino entre " << origen << " y " << destino << "\n";
        return;
    }

    std::map<std::string, int> distancias = dijkstra(origen);
    int costo = distancias[destino];

    std::cout << "Camino de " << origen << " a " << destino << ": ";

    for (size_t i = 0; i < camino.size(); i++) {
        std::cout << camino[i];
        if (i + 1 < camino.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << " | costo: " << costo << "\n";
}

void Red::actualizarTablas() {
    for (auto &par : routers) {
        std::map<std::string, int> distancias = dijkstra(par.first);
        par.second.establecerTablaCostos(distancias);
    }
}


void Red::mostrarTablas() const {
    std::cout << "Tabla costo\n";

    for (const auto& par : routers) {
        par.second.imprimirTabla();
        std::cout << "\n";
    }
}