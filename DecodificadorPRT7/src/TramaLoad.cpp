/**
* @file TramaLoad.cpp
 * @brief Implementación de la clase TramaLoad
 */

#include "TramaLoad.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <cstdio>

TramaLoad::TramaLoad(char c) : caracter(c) {
    buffer[0] = '\0';
}

TramaLoad::~TramaLoad() {
    // Limpieza si fuera necesaria
}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Decodificar el carácter usando el rotor
    char decodificado = rotor->getMapeo(caracter);

    // Insertar el carácter decodificado en la lista
    carga->insertarAlFinal(decodificado);
}

const char* TramaLoad::toString() const {
    // Usar un buffer mutable para construir la cadena
    char* buf = const_cast<char*>(buffer);
    snprintf(buf, 20, "L,%c", caracter);
    return buffer;
}