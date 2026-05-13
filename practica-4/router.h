#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>

class Router {
private:
    std::string id;

    std::map<std::string, int> vecinos;
    std::map<std::string, int> tablaCostos;

public:

    Router();
    Router(const std::string& id);

    std::string getId() const;
    std::map<std::string, int> getVecinos() const;
    std::map<std::string, int> getTablaCostos() const;

    void agregarVecino(const std::string& vecino, int costo);
    void eliminarVecino(const std::string& vecino);

    void inicializarTabla();
    void actualizarCosto(const std::string& destino, int costo);
    void establecerTablaCostos(const std::map<std::string, int>& nuevaTabla);

    void imprimirVecinos() const;
    void imprimirTabla() const;
};

#endif