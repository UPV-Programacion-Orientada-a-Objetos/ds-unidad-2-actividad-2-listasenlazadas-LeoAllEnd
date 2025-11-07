# Proyecto Decodificador PRT-7
# Sistema de Ciberseguridad Industrial

cmake_minimum_required(VERSION 3.10)
project(DecodificadorPRT7 VERSION 1.0 LANGUAGES CXX)

# Configurar estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorio de headers
include_directories(${PROJECT_SOURCE_DIR}/src)

# Archivos fuente
set(SOURCES
        src/main.cpp
        src/TramaLoad.cpp
        src/TramaMap.cpp
        src/RotorDeMapeo.cpp
        src/ListaDeCarga.cpp
        src/SerialPort.cpp
)

# Archivos header
set(HEADERS
        src/TramaBase.h
        src/TramaLoad.h
        src/TramaMap.h
        src/RotorDeMapeo.h
        src/ListaDeCarga.h
        src/SerialPort.h
)

# Crear ejecutable
add_executable(DecodificadorPRT7 ${SOURCES} ${HEADERS})

# Configuración específica para Windows
if(WIN32)
    # Nada especial necesario para Windows
endif()

# Configuración específica para Linux
if(UNIX)
    # Agregar bibliotecas necesarias en Linux
    target_link_libraries(DecodificadorPRT7)
endif()

# Opciones de compilación
if(MSVC)
    # Visual Studio

    target_compile_options(DecodificadorPRT7 PRIVATE /W4)
else()
    # GCC/Clang

    target_compile_options(DecodificadorPRT7 PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Instalación

install(TARGETS DecodificadorPRT7
        RUNTIME DESTINATION bin
)

# Mensaje de configuración
message(STATUS "===========================================")
message(STATUS "Proyecto: ${PROJECT_NAME}")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Sistema: ${CMAKE_SYSTEM_NAME}")
message(STATUS "===========================================")