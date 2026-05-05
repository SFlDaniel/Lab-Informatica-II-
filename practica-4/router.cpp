#include "Router.h"
#include <iostream>

Router::Router(const std::string& id) : id(id) {}

std::string Router::getId() const {
    return id;
}

std::map<std::string, int> Router::getVecinos() const {
    return vecinos;
}

std::map<std::string, int> Router::getTablaCostos() const {
    return tablaCostos;
}

void Router::agregarVecino(const std::string& vecino, int costo) {
    vecinos[vecino] = costo;
}

void Router::eliminarVecino(const std::string& vecino) {
    vecinos.erase(vecino);
}

void Router::inicializarTabla() {
    tablaCostos.clear();

    tablaCostos[id] = 0;

    for (const auto& par : vecinos) {
        tablaCostos[par.first] = par.second;
    }
}

void Router::actualizarCosto(const std::string& destino, int costo) {
    if (tablaCostos.find(destino) == tablaCostos.end() || costo < tablaCostos[destino]) {
        tablaCostos[destino] = costo;
    }
}

void Router::imprimirVecinos() const {
    std::cout << "Router " << id << " vecinos:\n";
    for (const auto& par : vecinos) {
        std::cout << "  -> " << par.first << " (costo: " << par.second << ")\n";
    }
}

void Router::imprimirTabla() const {
    std::cout << "Tabla de costos de " << id << ":\n";
    for (const auto& par : tablaCostos) {
        std::cout << "  -> " << par.first << " : " << par.second << "\n";
    }
}