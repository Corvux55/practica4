#include "red.h"
#include <iostream>
#include <fstream> //para leer archivos de texto
#include <sstream> //separa el texto del archivo
#include <queue> // estructuras de datos tipo cola. el primero que entra es el primero que sale
#include <limits>//representar el infinito
#include <algorithm>// darle la vuelta al camino
#include <map>
#include <string>
#include <cstdlib> // para generar numeros aleatorios (rand y srand)
#include <ctime>   // para inicializar la semilla con el tiempo actual

void red::agregarEnrutador(const std::string &nombre){
    if(enrutadores.find(nombre) == enrutadores.end()){//crea solo si no existe
        enrutadores[nombre] = Enrutador(nombre);
    }
}

void red::eliminarEnrutador(const std::string &nombre){
    for (auto& [_,otro]: enrutadores){//recorre todo para "avisar" que el que vamos a borrar ya no es vecino
        otro.quitarVecino(nombre);
    }
    enrutadores.erase(nombre);
    recalcularTodo();//como la topologia cambia, recalculamos
}

void red::agregarEnlace(const std::string &a, const std::string &b, int costo){
    if(a == b || costo<=0) return;//evitar bucles propios como A-A
    agregarEnrutador(a);
    agregarEnrutador(b);
    enrutadores[a].agregarVecino(b,costo);
    enrutadores[b].agregarVecino(a,costo);
}

void red::eliminarEnlace(const std::string &a, const std::string &b){
    //verificamos que existan
    if(enrutadores.count(a)) enrutadores[a].quitarVecino(b);
    if(enrutadores.count(b)) enrutadores[b].quitarVecino(a);
    recalcularTodo();
}

void red::recalcularTodo(){
    //calculamos las rutas desde la perspectiva de cada enrutador
    for(auto& [nombreOrigen, enrutador] : enrutadores){//"recorre enrutadores con esos parametros"
        enrutador.limpiarTabla();//limpiamos

        std::map<std::string, int> distancias;
        std::map<std::string, std::string> predecesores;

        for(auto&[n, _] : enrutadores){
            distancias[n] = std::numeric_limits<int>::max();//no conocemos distancias asi que las ponemos en "inf"
        }
        distancias[nombreOrigen]=0;

        //nos da el nodo con costo menor
        using P=std::pair<int, std::string>;
        std::priority_queue<P, std::vector<P>, std::greater<P>>pq;
        pq.push({0, nombreOrigen});

        while(!pq.empty()){
            auto[distActual,u]=pq.top();
            pq.pop();
            if(distActual>distancias[u]) continue;

            for(auto&[v, peso]: enrutadores[u].getVecinos()){
                //actualizamos si encontramos camino mas corto
                if (distancias[u]+peso < distancias[v]){
                    distancias[v] = distancias[u]+peso;
                    predecesores[v] = u;
                    pq.push({distancias[v],v});//agregamos a la cola para revision
                }
            }
        }

        //guardamos resultados en tabla enrutador
        for(auto&[destino,d]:distancias){
            if(destino == nombreOrigen || d== std::numeric_limits<int>::max())continue;//ignoramos el origen mismo y destinos donde no se puede llegar

            //vamos leyendo hacia atras
            std::vector<std::string>camino;
            for(std::string actual=destino; ; actual=predecesores[actual]){
                camino.push_back(actual);
                if(actual==nombreOrigen) break;
            }
            std::reverse(camino.begin(),camino.end());//volteamos para que quede origen - destino

            // CORRECCIÓN: Se cambió "Enrutador" por "enrutador" (minúscula) para llamar al método del objeto.
            enrutador.guardarRuta(destino,d,camino);
        }
    }
}

bool red::cargarDesdeArchivo(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo); // Abrimos el archivo de texto.
    if (!archivo.is_open()) return false; // Si no existe, avisamos que falló.

    std::string linea;
    // Leemos línea por línea.
    while (std::getline(archivo, linea)) {
        // Ignoramos líneas vacías o comentarios (los que empiezan con '#').
        if (linea.empty() || linea[0] == '#') continue;

        // Usamos sstream para separar las palabras de la línea fácilmente.
        std::istringstream ss(linea);
        std::string tipoComando;
        ss >> tipoComando; // Leemos la primera palabra (NODO o ENLACE).

        if (tipoComando == "NODO") {
            std::string nombreNodo;
            ss >> nombreNodo;
            agregarEnrutador(nombreNodo);
        } else if (tipoComando == "ENLACE") {
            std::string nodoOrigen, nodoDestino;
            int costoEnlace;
            if (ss >> nodoOrigen >> nodoDestino >> costoEnlace) {
                agregarEnlace(nodoOrigen, nodoDestino, costoEnlace);
            } else {
                // Seguro de vida: Si la línea dice ENLACE pero no tiene los 3 datos, avisa.
                std::cout << "Advertencia: linea mal formada -> " << linea << std::endl;
            }
        }
    }
    // Al terminar de leer todo, calculamos las rutas.
    recalcularTodo();
    return true;
}

void red::imprimirRed() const {
    std::cout << "=== Topologia de la Red ===" << std::endl;
    for (auto& [n, e] : enrutadores) {
        e.verVecinos(); // Usamos el método de impresión.
    }
}

void red::imprimirTablas() const {
    std::cout << "\n=== Tablas de Enrutamiento ===" << std::endl;
    for (auto& [n, e] : enrutadores) {
        e.verTabla(); // Usamos el método de tabla.
    }
}

// Consultar e imprimir la mejor ruta y el costo directo usando la tabla del origen
bool red::consultarCamino(const std::string& origen, const std::string& destino) const {
    // Verificamos que ambos enrutadores existan en el mapa
    if (enrutadores.find(origen) == enrutadores.end() || enrutadores.find(destino) == enrutadores.end()) {
        std::cout << "Error: Uno o ambos enrutadores no existen en la red." << std::endl;
        return false;
    }

    std::cout << "\n=== Consultar camino de " << origen << " a " << destino << " ===" << std::endl;
    // Mostramos la tabla del origen para ver la ruta resultante hacia el destino
    enrutadores.at(origen).verTabla();
    return true;
}

// Generar una red de forma aleatoria con cierta cantidad de nodos y enlaces
void red::generarRedAleatoria(int numNodos, int probabilidadEnlace, int costoMaximo) {
    // Limpiamos los enrutadores que teniamos cargados previamente
    enrutadores.clear();

    // Sembramos la semilla para los numeros aleatorios con el tiempo actual
    std::srand(std::time(nullptr));

    // Creamos los nombres de los nodos como Router_1, Router_2...
    std::vector<std::string> nombresNodos;
    for (int i = 1; i <= numNodos; ++i) {
        std::string nombre = "R" + std::to_string(i);
        nombresNodos.push_back(nombre);
        agregarEnrutador(nombre);
    }

    // Recorremos todos los pares de nodos para crear enlaces aleatorios
    for (size_t i = 0; i < nombresNodos.size(); ++i) {
        for (size_t j = i + 1; j < nombresNodos.size(); ++j) {
            // Evaluamos la probabilidad (de 0 a 100)
            int azar = std::rand() % 100;
            if (azar < probabilidadEnlace) {
                int costo = (std::rand() % costoMaximo) + 1; // costo aleatorio entre 1 y costoMaximo
                enrutadores[nombresNodos[i]].agregarVecino(nombresNodos[j], costo);
                enrutadores[nombresNodos[j]].agregarVecino(nombresNodos[i], costo);
            }
        }
    }

    // Recalculamos todas las tablas con la red recien creada
    recalcularTodo();
}