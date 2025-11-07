/**
* @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 */

#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <cstdio>

TramaMap::TramaMap(int n) : rotacion(n) {
    buffer[0] = '\0';
}

TramaMap::~TramaMap() {
    // Limpieza si fuera necesaria
}

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Simplemente rotar el rotor
    rotor->rotar(rotacion);
}

const char* TramaMap::toString() const {
    // Usar un buffer mutable para construir la cadena
    char* buf = const_cast<char*>(buffer);
    snprintf(buf, 20, "M,%d", rotacion);
    return buffer;
}