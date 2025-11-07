/**
 * @file transmisor_prt7.ino
 * @brief Transmisor del protocolo PRT-7 para Arduino
 * @details Este programa simula un sensor industrial que transmite
 *          datos codificados mediante el protocolo PRT-7.
 *          Envía tramas LOAD (L) y MAP (M) por el puerto serial.
 * @author walt
 * @date 2025
 */

/**
 * @brief Configuración inicial del Arduino
 * @details Inicializa la comunicación serial a 9600 baudios
 */
void setup() {
  Serial.begin(9600);
  delay(2000); // Espera para estabilizar la conexión
  Serial.println("INICIO_TRANSMISION_PRT7");
}

/**
 * @brief Bucle principal de transmisión
 * @details Envía la secuencia completa de tramas del protocolo PRT-7
 *          que codifica el mensaje "HELLO WORLD"
 */
void loop() {
  // Secuencia de tramas que codifica "HELLO WORLD"
  enviarTrama("L,H");
  enviarTrama("L,E");
  enviarTrama("L,L");
  enviarTrama("L,L");
  enviarTrama("L,O");
  
  enviarTrama("M,2");  // Rotación +2
  
  enviarTrama("L,Y");  // ' ' (espacio) con rotación +2 = Y
  
  enviarTrama("M,-2"); // Rotación -2 (vuelve a posición inicial)
  
  enviarTrama("L,W");
  enviarTrama("L,O");
  enviarTrama("L,R");
  enviarTrama("L,L");
  enviarTrama("L,D");
  
  Serial.println("FIN_TRANSMISION_PRT7");
  
  // Espera indefinida hasta reset
  while(true) {
    delay(10000);
  }
}

/**
 * @brief Envía una trama por el puerto serial
 * @param trama Cadena con el formato "L,X" o "M,N"
 */
void enviarTrama(const char* trama) {
  Serial.println(trama);
  delay(1000); // Pausa de 1 segundo entre tramas
}
