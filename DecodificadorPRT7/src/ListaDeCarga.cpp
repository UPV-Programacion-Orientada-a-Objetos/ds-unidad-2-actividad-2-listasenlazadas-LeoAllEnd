/**
* @file ListaDeCarga.cpp
 * @brief Implementación de la lista doblemente enlazada
 */

#include "ListaDeCarga.h"
#include <cstdio>

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamano(0) {
}

ListaDeCarga::~ListaDeCarga() {
    // Liberar todos los nodos
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);

    if (cabeza == nullptr) {
        // Lista vacía
        cabeza = nuevo;
        cola = nuevo;
    } else {
        // Insertar al final
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }

    tamano++;
}

void ListaDeCarga::imprimirMensaje() const {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        printf("%c", actual->dato);
        actual = actual->siguiente;
    }
}

void ListaDeCarga::imprimirConFormato() const {
    printf("Mensaje: [");
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        printf("%c", actual->dato);
        if (actual->siguiente != nullptr) {
            printf("][");
        }
        actual = actual->siguiente;
    }
    printf("]\n");
}