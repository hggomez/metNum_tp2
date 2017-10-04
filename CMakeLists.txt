cmake_minimum_required(VERSION 3.8)
project(METODOS-TP2)

set(CMAKE_CXX_STANDARD 11)

# Algunos flags para pasar al compilador (gnu++11 en vez de c++11 para que sea cross-plat)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11  -ggdb3 -O3 -march=native")

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES  src/*.h src/*.cpp)

# Creamos el ejecutable para correr el main
add_executable(correrMain ${SOURCE_FILES})
