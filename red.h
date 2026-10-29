#ifndef RED_H
#define RED_H
#include <map> //clave-valor
#include <string>
#include <vector>
#include "punto1.h"

class red{
private:
    std::map<std::string, Enrutador> enrutadores;
public:
    void agregarEnrutador(const std::string& nombre);
    void eliminarEnrutador(const std::string& nombre);
    void agregarEnlace(const std::string& a, const std::string& b, int costo);
    void eliminarEnlace(const std::string& a, const std::string& b);
    void recalcularTodo();
    bool cargarDesdeArchivo(const std::string& rutaArchivo);
    void imprimirRed() const;
    void imprimirTablas() const;

    // Metodo para consultar el costo y camino entre un origen y un destino
    bool consultarCamino(const std::string& origen, const std::string& destino) const;

    // Metodo para generar una red aleatoria con una cantidad de nodos y probabilidad de enlace
    void generarRedAleatoria(int numNodos, int probabilidadEnlace, int costoMaximo);
};

#endif // RED_H