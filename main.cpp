#include <iostream>
#include "red.h"
#include "punto1.h"
//solo para probar, se puede borrar
int main() {
    std::cout << "=== PRUEBA CON ARCHIVO TXT ===\n\n";

    red miRed;

    std::cout << "1. Cargando topologia desde 'red.txt'...\n";
    if (!miRed.cargarDesdeArchivo("red.txt")) {
        std::cout << "ERROR: No se encontro red.txt.\n";
        return 1;
    }
    std::cout << "   ¡Archivo cargado con exito!\n\n";

    std::cout << "2. Imprimiendo tablas calculadas:\n";
    miRed.imprimirTablas();

    return 0;
}