/**
* @file TramaMap.h
 * @brief Trama de mapeo que modifica el estado del rotor
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Representa una trama MAP (M,N) del protocolo PRT-7
 * @details Almacena un valor de rotación que modificará el rotor de mapeo
 */
class TramaMap : public TramaBase {
private:
    int rotacion; ///< Cantidad de posiciones a rotar (+ o -)
    char buffer[20]; ///< Buffer para toString()

public:
    /**
     * @brief Constructor de la trama MAP
     * @param n Valor de rotación (positivo o negativo)
     */
    explicit TramaMap(int n);

    /**
     * @brief Destructor
     */
    ~TramaMap();

    /**
     * @brief Procesa la trama MAP
     * @param carga No utilizada en MAP
     * @param rotor Rotor que será rotado
     * @details Aplica la rotación al rotor, cambiando el mapeo de caracteres
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;

    /**
     * @brief Obtiene representación de la trama
     * @return Cadena con formato "M,N"
     */
    const char* toString() const override;

    /**
     * @brief Obtiene el valor de rotación
     * @return Valor de rotación
     */
    int getRotacion() const { return rotacion; }
};

#endif // TRAMA_MAP_H