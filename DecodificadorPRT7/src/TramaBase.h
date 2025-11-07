/**
* @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 * @details Define la interfaz común para tramas LOAD y MAP mediante polimorfismo
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase abstracta que representa una trama del protocolo PRT-7
 * @details Esta clase utiliza el patrón de diseño Strategy para permitir
 *          diferentes tipos de procesamiento según el tipo de trama
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual para limpieza polimórfica
     * @details CRÍTICO: Debe ser virtual para evitar fugas de memoria
     *          al eliminar objetos derivados a través de punteros base
     */
    virtual ~TramaBase() {}

    /**
     * @brief Procesa la trama según su tipo
     * @param carga Puntero a la lista de carga donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo que maneja la lógica de cifrado
     * @details Método virtual puro que DEBE ser implementado por las clases derivadas
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;

    /**
     * @brief Obtiene una representación en texto de la trama
     * @return Cadena con el contenido de la trama
     */
    virtual const char* toString() const = 0;
};

#endif // TRAMA_BASE_H