/**
 * @file RotorDeMapeo.h
 * @brief Lista circular doblemente enlazada que implementa un disco de cifrado
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo de la lista circular que contiene un carácter
 */
struct NodoRotor {
    char dato;           ///< Carácter almacenado
    NodoRotor* siguiente; ///< Puntero al siguiente nodo
    NodoRotor* previo;    ///< Puntero al nodo previo

    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Implementa un disco de cifrado mediante lista circular doblemente enlazada
 * @details Similar a una Rueda de César, mapea caracteres según su rotación actual.
 *          Contiene el alfabeto A-Z y un puntero cabeza que indica la posición 'cero'.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza; ///< Puntero a la posición 'cero' actual del rotor
    int tamano;        ///< Número de elementos en el rotor

    /**
     * @brief Encuentra un nodo por su carácter
     * @param c Carácter a buscar
     * @return Puntero al nodo encontrado o nullptr
     */
    NodoRotor* buscarNodo(char c) const;

    /**
     * @brief Calcula la distancia entre dos nodos
     * @param desde Nodo de inicio
     * @param hasta Nodo de destino
     * @return Distancia en número de nodos
     */
    int calcularDistancia(NodoRotor* desde, NodoRotor* hasta) const;

public:
    /**
     * @brief Constructor que inicializa el rotor con A-Z
     */
    RotorDeMapeo();

    /**
     * @brief Destructor que libera toda la memoria
     */
    ~RotorDeMapeo();

    /**
     * @brief Rota el rotor N posiciones
     * @param n Número de posiciones (+ derecha, - izquierda)
     * @details Mueve la cabeza circularmente sin mover los datos
     */
    void rotar(int n);

    /**
     * @brief Mapea un carácter según la rotación actual
     * @param entrada Carácter a mapear
     * @return Carácter mapeado
     * @details Encuentra el carácter de entrada, calcula su distancia a cabeza,
     *          y devuelve el carácter que está a esa distancia desde cabeza
     */
    char getMapeo(char entrada) const;

    /**
     * @brief Obtiene el carácter en la posición cabeza
     * @return Carácter actual en cabeza
     */
    char getCabeza() const { return cabeza ? cabeza->dato : '\0'; }

    /**
     * @brief Imprime el estado actual del rotor (debug)
     */
    void imprimirEstado() const;
};

#endif // ROTOR_DE_MAPEO_H