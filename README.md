# C++ Aulas — Dove Language

Repositorio das minhas aulas de C++ no curso Dove Language.

Cada aula cobre um topico da linguagem com exemplos comentados e executaveis no console.

## Aulas

| #   | Topico                                                                                         | Arquivo                         |
| --- | ---------------------------------------------------------------------------------------------- | ------------------------------- |
| 01  | Tipos de dados (bool, char, int, float, double, short, long, unsigned)                         | `src/aula01_tipos.cpp`          |
| 02  | Tipos modernos C++11/17 (auto, decltype, nullptr, int32_t, size_t, string, optional)           | `src/aula02_tipos_modernos.cpp` |
| 03  | Estruturas de controle (if/else, switch, for, while, do-while, break, continue) + Pilha e Fila | `src/aula03_controle.cpp`       |

## Como rodar

### Requisitos

- CMake 3.20 ou superior
- g++ com suporte a C++20 (g++-13 recomendado)

### Linux / macOS

```bash
# 1. Clonar o repositorio
git clone https://github.com/marcioazam/cpp-aulas-dove.git
cd cpp-aulas-dove

# 2. Configurar e compilar
cmake -S . -B build
cmake --build build

# 3. Executar
./build/cppsmoke
```

### Windows (com MinGW ou MSVC)

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\build\cppsmoke.exe
```

### VS Code

Abra a pasta no VS Code e pressione `Ctrl+Shift+B` para compilar.
Use `F5` para compilar e executar com o debugger.

### Selecionando a aula

Ao executar, um menu aparece no terminal:

```
================================
   SELECIONE A AULA
================================
 1 - Tipos de dados
 2 - Tipos modernos C++11/17
 3 - Estruturas de controle
================================
Aula:
```

Digite o numero da aula e pressione Enter.

## Estrutura do projeto

```
.
├── include/          # Headers de cada aula
├── src/              # Implementacoes + main.cpp
├── CMakeLists.txt    # Build system
└── README.md
```
