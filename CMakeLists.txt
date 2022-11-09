cmake_minimum_required(VERSION 3.23)
project(codigo_projeteis C)

set(CMAKE_C_STANDARD 99)

add_executable(codigo_projeteis main.c objetos.h)

target_link_libraries(codigo_projeteis -lmingw32 -lallegro-5.0.10-monolith-md-debug)
