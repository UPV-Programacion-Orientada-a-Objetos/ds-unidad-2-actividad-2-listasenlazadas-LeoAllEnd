/**
* @file TramaLoad.h
 * @brief Trama de carga que contiene un fragmento de datos
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Representa una trama LOAD (L,X) del protocolo PRT-7
 * @details Almacena un carácter que será decodificado usando el rotor actual
 */
class TramaLoad : public TramaBase {
private:
    char caracter; ///< Carácter a decodificar
    char buffer[20]; ///< Buffer para toString()

public:
    /**
     * @brief Constructor de la trama LOAD
     * @param c Carácter a almacenar
     */
    explicit TramaLoad(char c);

    /**
     * @brief Destructor
     */
    ~TramaLoad();

    /**
     * @brief Procesa la trama LOAD
     * @param carga Lista donde se insertará el carácter decodificado
     * @param rotor Rotor que realizará el mapeo
     * @details Decodifica el carácter usando el rotor y lo inserta en la lista
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;

    /**
     * @brief Obtiene representación de la trama
     * @return Cadena con formato "L,X"
     */
    const char* toString() const override;

    /**
     * @brief Obtiene el carácter almacenado
     * @return Carácter de la trama
     */
    char getCaracter() const { return caracter; }
};

#endif // TRAMA_LOAD_H