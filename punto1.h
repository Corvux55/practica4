#ifndef PUNTO1_H
#define PUNTO1_H

#include <string>
#include <map>
#include <vector>

// Clase para representar un enrutador individual
class Enrutador {
private:
    std::string nombre; // El nombre del router (ej: "A", "B")

    // Guardamos los vecinos que estan conectados directamente y el costo del enlace
    std::map<std::string, int> vecinos;

    // Guardamos los costos minimos finales a cada destino[cite: 1, 3]
    std::map<std::string, int> costos;

    // Guardamos el camino completo (los nombres de los nodos) para llegar a cada destino
    std::map<std::string, std::vector<std::string>> caminos;

public:
    // Constructor de la clase
    Enrutador(std::string nom = "");

    // Devuelve el nombre de este enrutador
    std::string getNombre() const;

    // Metodos para manejar los vecinos directos
    void agregarVecino(std::string vec, int costo); // Agrega o cambia la conexion con un vecino
    void quitarVecino(std::string vec);             // Elimina un vecino directo
    std::map<std::string, int> getVecinos() const;  // Retorna el mapa de vecinos directos

    // Metodos para la tabla de enrutamiento
    void limpiarTabla(); // Borra las rutas guardadas para volver a calcularlas
    void guardarRuta(std::string dest, int costo, std::vector<std::string> cam); // Guarda la mejor ruta encontrada hacia un destino

    // Funciones para imprimir la informacion por consola
    void verVecinos() const; // Muestra solo los vecinos directos
    void verTabla() const;   // Muestra la tabla de enrutamiento completa con sus caminos
};

#endif // PUNTO1_H