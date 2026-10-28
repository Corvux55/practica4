#include "punto1.h"
#include <iostream>
#include <iomanip>

// Constructor: le asignamos el nombre al router y ponemos costo 0 hacia el mismo
Enrutador::Enrutador(std::string nom) {
    nombre = nom;
    costos[nombre] = 0;
    caminos[nombre] = {nombre};
}

// Devuelve el nombre actual del router
std::string Enrutador::getNombre() const {
    return nombre;
}

// Guarda un vecino y el costo de su enlace directo en el mapa
void Enrutador::agregarVecino(std::string vec, int costo) {
    vecinos[vec] = costo;
}

// Elimina a un vecino directo usando su nombre
void Enrutador::quitarVecino(std::string vec) {
    vecinos.erase(vec);
}

// Retorna los vecinos directos que tiene este router
std::map<std::string, int> Enrutador::getVecinos() const {
    return vecinos;
}

// Borra la tabla de costos y caminos, y solo deja el nodo actual con costo 0
void Enrutador::limpiarTabla() {
    costos.clear();
    caminos.clear();
    costos[nombre] = 0;
    caminos[nombre] = {nombre};
}

// Registra en el router la mejor ruta calculada hacia un destino concreto
void Enrutador::guardarRuta(std::string dest, int costo, std::vector<std::string> cam) {
    costos[dest] = costo;
    caminos[dest] = cam;
}

// Imprime en pantalla la lista de vecinos directos que conoce el router
void Enrutador::verVecinos() const {
    std::cout << "--- Enrutador " << nombre << " ---" << std::endl;
    std::cout << "Vecinos directos:" << std::endl;
    for (auto const& [vecino, costo] : vecinos) {
        std::cout << "  " << vecino << " -> Costo: " << costo << std::endl;
    }
}

// Imprime la tabla de enrutamiento local con destinos, costos y el camino completo
void Enrutador::verTabla() const {
    std::cout << "\nTabla de enrutamiento de " << nombre << ":" << std::endl;
    std::cout << std::left << std::setw(10) << "Destino"
              << std::setw(10) << "Costo"
              << "Camino" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    for (auto const& [dest, costo] : costos) {
        std::cout << std::left << std::setw(10) << dest
                  << std::setw(10) << costo;

        // Si existe un camino guardado para el destino, lo mostramos con flechas
        if (caminos.count(dest)) {
            auto cam = caminos.at(dest);
            for (size_t i = 0; i < cam.size(); ++i) {
                std::cout << cam[i];
                if (i + 1 < cam.size()) std::cout << "->";
            }
        }
        std::cout << std::endl;
    }
}