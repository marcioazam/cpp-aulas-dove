cmake_minimum_required(VERSION 3.20)
project(Cppsmoke VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(cppsmoke
    src/main.cpp
    src/aula01_tipos.cpp
    src/aula02_ponteiros.cpp
    src/aula03_tipos_modernos.cpp
    src/aula04_controle.cpp
)
target_include_directories(cppsmoke PRIVATE include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(cppsmoke PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

enable_testing()
add_test(NAME run_cppsmoke COMMAND cppsmoke)
