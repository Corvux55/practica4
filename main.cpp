#include <iostream>
#include <string>
#include "red.h"

int main() {
    red miRed;
    int opcion = 0;

    // Cargar archivo por defecto al iniciar
    miRed.cargarDesdeArchivo("red.txt");

    do {
        std::cout << "\n=========================================\n";
        std::cout << "         RED DE ENRUTADORES - MENU       \n";
        std::cout << "=========================================\n";
        std::cout << "1. Cargar red desde archivo TXT\n";
        std::cout << "2. Ver topologia de la red (vecinos directos)\n";
        std::cout << "3. Ver tablas de enrutamiento completas\n";
        std::cout << "4. Consultar camino y costo entre dos enrutadores\n";
        std::cout << "5. Agregar / Modificar enrutador o enlace\n";
        std::cout << "6. Eliminar enrutador\n";
        std::cout << "7. Eliminar enlace\n";
        std::cout << "8. Generar red aleatoria\n";
        std::cout << "0. Salir\n";
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            std::string archivo;
            std::cout << "Ingrese el nombre del archivo (ej: red.txt): ";
            std::cin >> archivo;
            if (miRed.cargarDesdeArchivo(archivo)) {
                std::cout << "¡Red cargada con exito desde " << archivo << "!\n";
            } else {
                std::cout << "Error: No se pudo abrir el archivo.\n";
            }
            break;
        }
        case 2:
            miRed.imprimirRed();
            break;

        case 3:
            miRed.imprimirTablas();
            break;

        case 4: {
            std::string origen, destino;
            std::cout << "Ingrese el enrutador de ORIGEN: ";
            std::cin >> origen;
            std::cout << "Ingrese el enrutador de DESTINO: ";
            std::cin >> destino;
            miRed.consultarCamino(origen, destino);
            break;
        }
        case 5: {
            std::string origen, destino;
            int costo;
            std::cout << "Ingrese enrutador 1: ";
            std::cin >> origen;
            std::cout << "Ingrese enrutador 2: ";
            std::cin >> destino;
            std::cout << "Ingrese el costo del enlace: ";
            std::cin >> costo;
            miRed.agregarEnlace(origen, destino, costo);
            std::cout << "Enlace agregado / actualizado correctamente.\n";
            break;
        }
        case 6: {
            std::string nodo;
            std::cout << "Ingrese el nombre del enrutador a eliminar: ";
            std::cin >> nodo;
            miRed.eliminarEnrutador(nodo);
            std::cout << "Enrutador eliminado correctamente.\n";
            break;
        }
        case 7: {
            std::string origen, destino;
            std::cout << "Ingrese enrutador 1 del enlace: ";
            std::cin >> origen;
            std::cout << "Ingrese enrutador 2 del enlace: ";
            std::cin >> destino;
            miRed.eliminarEnlace(origen, destino);
            std::cout << "Enlace eliminado correctamente.\n";
            break;
        }
        case 8: {
            int numNodos, prob, costoMax;
            std::cout << "Ingrese la cantidad de enrutadores a crear: ";
            std::cin >> numNodos;
            std::cout << "Ingrese la probabilidad de conexion (1 a 100%): ";
            std::cin >> prob;
            std::cout << "Ingrese el costo maximo de los enlaces: ";
            std::cin >> costoMax;
            miRed.generarRedAleatoria(numNodos, prob, costoMax);
            std::cout << "Red aleatoria generada exitosamente.\n";
            break;
        }
        case 0:
            std::cout << "Saliendo del programa...\n";
            break;

        default:
            std::cout << "Opcion invalida, intente de nuevo.\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}