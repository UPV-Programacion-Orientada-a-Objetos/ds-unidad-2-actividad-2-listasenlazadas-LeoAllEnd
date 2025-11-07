/**
 * @file main.cpp
 * @brief Programa principal del Decodificador PRT-7
 * @details Sistema que decodifica mensajes del protocolo industrial PRT-7
 *          recibidos desde un Arduino vía puerto serial
 * @author Equipo de Desarrollo
 * @date 2025
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

#include "SerialPort.h"
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

/**
 * @brief Parsea una línea del protocolo PRT-7
 * @param linea Cadena recibida del puerto serial
 * @return Puntero a TramaBase (TramaLoad o TramaMap) o nullptr si es inválida
 * @details Formato esperado: "L,X" o "M,N"
 */
TramaBase* parsearTrama(const char* linea) {
    if (linea == nullptr || linea[0] == '\0') {
        return nullptr;
    }

    // Copiar la línea para no modificar el original
    char buffer[100];
    strncpy(buffer, linea, 99);
    buffer[99] = '\0';

    // Eliminar espacios en blanco al inicio y final
    char* inicio = buffer;
    while (*inicio == ' ' || *inicio == '\t' || *inicio == '\r' || *inicio == '\n') {
        inicio++;
    }

    int len = strlen(inicio);
    while (len > 0 && (inicio[len-1] == ' ' || inicio[len-1] == '\t' ||
           inicio[len-1] == '\r' || inicio[len-1] == '\n')) {
        inicio[--len] = '\0';
    }

    // Verificar formato mínimo
    if (len < 3) {
        return nullptr;
    }

    char tipo = toupper(inicio[0]);

    if (inicio[1] != ',') {
        return nullptr;
    }

    if (tipo == 'L') {
        // Trama LOAD: L,X
        char caracter = inicio[2];
        return new TramaLoad(caracter);

    } else if (tipo == 'M') {
        // Trama MAP: M,N
        int rotacion = atoi(&inicio[2]);
        return new TramaMap(rotacion);
    }

    return nullptr;
}

/**
 * @brief Imprime el banner de inicio del sistema
 */
void imprimirBanner() {
    printf("\n");
    printf("========================================\n");
    printf("   DECODIFICADOR PRT-7 v1.0\n");
    printf("   Sistema de Ciberseguridad Industrial\n");
    printf("========================================\n\n");
}

/**
 * @brief Solicita al usuario el puerto serial a usar
 * @param buffer Buffer donde se almacenará el nombre del puerto
 * @param bufferSize Tamaño del buffer
 */
void solicitarPuerto(char* buffer, int bufferSize) {
    printf("\nPuertos seriales disponibles:\n");
    listarPuertosDisponibles();

    printf("\nIngrese el puerto a usar\n");
    printf("  Windows: COM3, COM4, etc.\n");
    printf("  Linux: /dev/ttyUSB0, /dev/ttyACM0, etc.\n");
    printf("Puerto: ");

    if (fgets(buffer, bufferSize, stdin) != nullptr) {
        // Eliminar el salto de línea
        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    }
}

/**
 * @brief Función principal del decodificador
 * @return 0 si todo fue exitoso
 */
int main() {
    imprimirBanner();

    // Solicitar puerto al usuario
    char nombrePuerto[50];
    solicitarPuerto(nombrePuerto, sizeof(nombrePuerto));

    printf("\nIniciando Decodificador PRT-7...\n");
    printf("Conectando a puerto %s...\n", nombrePuerto);

    // Abrir puerto serial
    SerialHandle puerto = abrirPuertoSerial(nombrePuerto, 9600);
    if (puerto == INVALID_SERIAL_HANDLE) {
        printf("ERROR: No se pudo abrir el puerto serial.\n");
        printf("Verifique que:\n");
        printf("  1. El Arduino está conectado\n");
        printf("  2. El puerto es correcto\n");
        printf("  3. No está siendo usado por otro programa\n");
        return 1;
    }

    printf("Conexión establecida. Esperando tramas...\n\n");

    // Dar tiempo al Arduino para inicializar
    SLEEP_MS(2000);

    // Crear las estructuras de datos
    ListaDeCarga listaCarga;
    RotorDeMapeo rotor;

    // Buffer para leer líneas
    char linea[256];
    int tramasRecibidas = 0;
    bool finTransmision = false;

    // Bucle principal de procesamiento
    while (!finTransmision) {
        if (leerLineaSerial(puerto, linea, sizeof(linea))) {

            // Verificar mensajes especiales
            if (strstr(linea, "INICIO_TRANSMISION_PRT7") != nullptr) {
                printf(">>> Inicio de transmisión detectado <<<\n\n");
                continue;
            }

            if (strstr(linea, "FIN_TRANSMISION_PRT7") != nullptr) {
                printf("\n>>> Fin de transmisión detectado <<<\n");
                finTransmision = true;
                break;
            }

            // Ignorar líneas vacías
            if (linea[0] == '\0' || linea[0] == '\r' || linea[0] == '\n') {
                continue;
            }

            // Parsear la trama
            TramaBase* trama = parsearTrama(linea);

            if (trama != nullptr) {
                tramasRecibidas++;

                printf("Trama recibida: [%s] -> Procesando... ", trama->toString());

                // Procesar la trama (polimorfismo en acción)
                trama->procesar(&listaCarga, &rotor);

                // Mostrar resultado según el tipo
                TramaLoad* load = dynamic_cast<TramaLoad*>(trama);
                TramaMap* map = dynamic_cast<TramaMap*>(trama);

                if (load != nullptr) {
                    printf("-> Fragmento '%c' procesado. ", load->getCaracter());
                    listaCarga.imprimirConFormato();
                } else if (map != nullptr) {
                    printf("-> ROTANDO ROTOR %+d. (Cabeza ahora en '%c')\n",
                           map->getRotacion(), rotor.getCabeza());
                }

                // Liberar memoria de la trama
                delete trama;

            } else {
                // Trama mal formada
                printf("Trama inválida recibida: [%s]\n", linea);
            }
        }

        // Pequeña pausa para no saturar el CPU
        SLEEP_MS(50);
    }

    // Mostrar resultado final
    printf("\n");
    printf("========================================\n");
    printf("   DECODIFICACIÓN COMPLETADA\n");
    printf("========================================\n");
    printf("Tramas procesadas: %d\n", tramasRecibidas);
    printf("Caracteres decodificados: %d\n\n", listaCarga.getTamano());

    printf("MENSAJE OCULTO ENSAMBLADO:\n");
    printf(">>> ");
    listaCarga.imprimirMensaje();
    printf(" <<<\n");
    printf("========================================\n\n");

    // Cerrar puerto
    cerrarPuertoSerial(puerto);
    printf("Liberando memoria... Sistema apagado.\n\n");

    return 0;
}