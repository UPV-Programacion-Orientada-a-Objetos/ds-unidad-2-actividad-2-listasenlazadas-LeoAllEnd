/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar el mensaje decodificado
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada
 */
struct NodoCarga {
    char dato;           ///< Carácter almacenado
    NodoCarga* siguiente; ///< Puntero al siguiente nodo
    NodoCarga* previo;    ///< Puntero al nodo previo

    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada que almacena el mensaje decodificado
 * @details Mantiene el orden de los fragmentos de datos según son procesados
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza; ///< Puntero al primer nodo
    NodoCarga* cola;   ///< Puntero al último nodo
    int tamano;        ///< Número de elementos

public:
    /**
     * @brief Constructor de la lista vacía
     */
    ListaDeCarga();

    /**
     * @brief Destructor que libera toda la memoria
     */
    ~ListaDeCarga();

    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     * @details Mantiene el orden de llegada de los datos decodificados
     */
    void insertarAlFinal(char dato);

    /**
     * @brief Imprime el mensaje completo ensamblado
     * @details Recorre la lista y muestra todos los caracteres en orden
     */
    void imprimirMensaje() const;

    /**
     * @brief Obtiene el tamaño de la lista
     * @return Número de caracteres almacenados
     */
    int getTamano() const { return tamano; }

    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const { return cabeza == nullptr; }

    /**
     * @brief Imprime el mensaje con formato detallado (para debug)
     */
    void imprimirConFormato() const;
};

#endif // LISTA_DE_CARGA_H