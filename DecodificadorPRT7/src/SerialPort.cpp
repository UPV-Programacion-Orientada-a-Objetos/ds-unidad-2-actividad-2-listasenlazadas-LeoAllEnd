/**
 * @file SerialPort.cpp
 * @brief Implementación multiplataforma de comunicación serial
 */

#include "SerialPort.h"
#include <cstdio>
#include <cstring>

#ifdef _WIN32
// ============ IMPLEMENTACIÓN WINDOWS ============

SerialHandle abrirPuertoSerial(const char* portName, int baudRate) {
    char fullPortName[20];
    snprintf(fullPortName, sizeof(fullPortName), "\\\\.\\%s", portName);

    HANDLE hSerial = CreateFileA(
        fullPortName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        return INVALID_SERIAL_HANDLE;
    }

    // Configurar parámetros del puerto
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        return INVALID_SERIAL_HANDLE;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        return INVALID_SERIAL_HANDLE;
    }

    // Configurar timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        CloseHandle(hSerial);
        return INVALID_SERIAL_HANDLE;
    }

    return hSerial;
}

bool leerLineaSerial(SerialHandle handle, char* buffer, int bufferSize) {
    if (handle == INVALID_SERIAL_HANDLE || buffer == nullptr) {
        return false;
    }

    int pos = 0;
    DWORD bytesRead;
    char c;

    while (pos < bufferSize - 1) {
        if (!ReadFile(handle, &c, 1, &bytesRead, NULL) || bytesRead == 0) {
            if (pos > 0) break;
            return false;
        }

        if (c == '\n') {
            break;
        }

        if (c != '\r') {
            buffer[pos++] = c;
        }
    }

    buffer[pos] = '\0';
    return pos > 0;
}

void cerrarPuertoSerial(SerialHandle handle) {
    if (handle != INVALID_SERIAL_HANDLE) {
        CloseHandle(handle);
    }
}

void listarPuertosDisponibles() {
    printf("Buscando puertos COM1-COM20...\n");
    for (int i = 1; i <= 20; i++) {
        char portName[20];
        snprintf(portName, sizeof(portName), "COM%d", i);

        SerialHandle h = abrirPuertoSerial(portName, 9600);
        if (h != INVALID_SERIAL_HANDLE) {
            printf("  - %s (disponible)\n", portName);
            cerrarPuertoSerial(h);
        }
    }
}

#else
// ============ IMPLEMENTACIÓN LINUX ============

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <dirent.h>

SerialHandle abrirPuertoSerial(const char* portName, int baudRate) {
    int fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        return INVALID_SERIAL_HANDLE;
    }

    // Configurar puerto
    struct termios options;
    tcgetattr(fd, &options);

    // Configurar velocidad
    speed_t speed = B9600;
    if (baudRate == 115200) speed = B115200;
    else if (baudRate == 57600) speed = B57600;
    else if (baudRate == 38400) speed = B38400;
    else if (baudRate == 19200) speed = B19200;

    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);

    // Configurar modo
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Modo raw
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~OPOST;

    // Timeouts
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 5;

    tcsetattr(fd, TCSANOW, &options);

    return fd;
}

bool leerLineaSerial(SerialHandle handle, char* buffer, int bufferSize) {
    if (handle == INVALID_SERIAL_HANDLE || buffer == nullptr) {
        return false;
    }

    int pos = 0;
    char c;

    while (pos < bufferSize - 1) {
        int n = read(handle, &c, 1);

        if (n <= 0) {
            if (pos > 0) break;
            return false;
        }

        if (c == '\n') {
            break;
        }

        if (c != '\r') {
            buffer[pos++] = c;
        }
    }

    buffer[pos] = '\0';
    return pos > 0;
}

void cerrarPuertoSerial(SerialHandle handle) {
    if (handle != INVALID_SERIAL_HANDLE) {
        close(handle);
    }
}

void listarPuertosDisponibles() {
    printf("Puertos seriales comunes en Linux:\n");
    const char* puertos[] = {
        "/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2",
        "/dev/ttyACM0", "/dev/ttyACM1", "/dev/ttyACM2",
        "/dev/ttyS0", "/dev/ttyS1"
    };

    for (int i = 0; i < 8; i++) {
        if (access(puertos[i], F_OK) == 0) {
            printf("  - %s\n", puertos[i]);
        }
    }
}

#endif