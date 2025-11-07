/**
* @file SerialPort.h
 * @brief Manejo de comunicación serial multiplataforma
 * @details Proporciona funciones para abrir, leer y cerrar puertos seriales
 *          Compatible con Windows y Linux
 */

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#ifdef _WIN32
    #include <windows.h>
    typedef HANDLE SerialHandle;
#define INVALID_SERIAL_HANDLE INVALID_HANDLE_VALUE
#else
typedef int SerialHandle;
#define INVALID_SERIAL_HANDLE -1
#endif

/**
 * @brief Abre un puerto serial
 * @param portName Nombre del puerto (ej: "COM3" en Windows, "/dev/ttyUSB0" en Linux)
 * @param baudRate Velocidad en baudios (ej: 9600)
 * @return Handle del puerto o INVALID_SERIAL_HANDLE si falla
 */
SerialHandle abrirPuertoSerial(const char* portName, int baudRate);

/**
 * @brief Lee una línea desde el puerto serial
 * @param handle Handle del puerto
 * @param buffer Buffer donde se almacenará la línea leída
 * @param bufferSize Tamaño del buffer
 * @return true si se leyó correctamente, false en caso de error
 * @details Lee hasta encontrar '\n' o llenar el buffer
 */
bool leerLineaSerial(SerialHandle handle, char* buffer, int bufferSize);

/**
 * @brief Cierra el puerto serial
 * @param handle Handle del puerto a cerrar
 */
void cerrarPuertoSerial(SerialHandle handle);

/**
 * @brief Imprime los puertos seriales disponibles
 * @details Útil para que el usuario elija el puerto correcto
 */
void listarPuertosDisponibles();

#endif // SERIAL_PORT_H