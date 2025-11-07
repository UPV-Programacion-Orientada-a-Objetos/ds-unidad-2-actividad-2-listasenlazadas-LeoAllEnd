/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la lista circular doblemente enlazada para el rotor
 */

#include "RotorDeMapeo.h"
#include <cstdio>
#include <cctype>

RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamano(0) {
    // Crear nodos para A-Z y espacio
    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    NodoRotor* primero = nullptr;
    NodoRotor* ultimo = nullptr;

    // Construir la lista circular
    for (int i = 0; alfabeto[i] != '\0'; i++) {
        NodoRotor* nuevo = new NodoRotor(alfabeto[i]);

        if (primero == nullptr) {
            // Primer nodo
            primero = nuevo;
            ultimo = nuevo;
            cabeza = nuevo;
        } else {
            // Enlazar con el anterior
            ultimo->siguiente = nuevo;
            nuevo->previo = ultimo;
            ultimo = nuevo;
        }
        tamano++;
    }

    // Cerrar el círculo
    if (ultimo != nullptr && primero != nullptr) {
        ultimo->siguiente = primero;
        primero->previo = ultimo;
    }
}

RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;

    // Romper el círculo temporalmente
    NodoRotor* ultimo = cabeza->previo;
    ultimo->siguiente = nullptr;

    // Eliminar todos los nodos
    NodoRotor* actual = cabeza;
    while (actual != nullptr) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void RotorDeMapeo::rotar(int n) {
    if (cabeza == nullptr || n == 0) return;

    // Normalizar la rotación al rango del tamaño
    n = n % tamano;
    if (n < 0) n += tamano;

    // Mover la cabeza n posiciones
    for (int i = 0; i < n; i++) {
        cabeza = cabeza->siguiente;
    }
}

NodoRotor* RotorDeMapeo::buscarNodo(char c) const {
    if (cabeza == nullptr) return nullptr;

    // Convertir a mayúscula para búsqueda
    char buscar = toupper(c);

    NodoRotor* actual = cabeza;
    do {
        if (actual->dato == buscar) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

int RotorDeMapeo::calcularDistancia(NodoRotor* desde, NodoRotor* hasta) const {
    if (desde == nullptr || hasta == nullptr) return 0;

    int distancia = 0;
    NodoRotor* actual = desde;

    while (actual != hasta) {
        actual = actual->siguiente;
        distancia++;

        // Prevención de bucle infinito
        if (distancia > tamano) return 0;
    }

    return distancia;
}

char RotorDeMapeo::getMapeo(char entrada) const {
    if (cabeza == nullptr) return entrada;

    // Convertir entrada a mayúscula
    char buscar = toupper(entrada);

    // Buscar el nodo con el carácter de entrada
    NodoRotor* nodoEntrada = buscarNodo(buscar);
    if (nodoEntrada == nullptr) {
        // Si no se encuentra, devolver el mismo carácter
        return entrada;
    }

    // Calcular la distancia desde cabeza hasta el nodo de entrada
    int distancia = calcularDistancia(cabeza, nodoEntrada);

    // El carácter mapeado está a la misma distancia desde cabeza
    // (esto implementa el cifrado César circular)
    NodoRotor* resultado = cabeza;
    for (int i = 0; i < distancia; i++) {
        resultado = resultado->siguiente;
    }

    return resultado->dato;
}

void RotorDeMapeo::imprimirEstado() const {
    if (cabeza == nullptr) {
        printf("Rotor vacío\n");
        return;
    }

    printf("Estado del Rotor (cabeza='%c'): ", cabeza->dato);
    NodoRotor* actual = cabeza;
    do {
        printf("%c", actual->dato);
        actual = actual->siguiente;
    } while (actual != cabeza);
    printf("\n");
}