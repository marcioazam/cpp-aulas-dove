# C++ Aulas — Dove Language

Repositorio das minhas aulas de C++ no curso Dove Language.

Cada aula cobre um topico da linguagem com exemplos comentados e executaveis no console.

## Aulas

| #   | Topico                                                                                                  | Arquivo                          |
| --- | ------------------------------------------------------------------------------------------------------- | -------------------------------- |
| 01  | Tipos de dados (bool, char, int, float, double, short, long, unsigned)                                  | `src/aula01_tipos.cpp`           |
| 02  | Ponteiros (`*`, `&`, `nullptr`), Pilha (LIFO), Fila (FIFO), Matriz                                     | `src/aula02_ponteiros.cpp`       |
| 03  | Tipos modernos C++11/17 (auto, decltype, nullptr, int32_t, size_t, string, optional)                   | `src/aula03_tipos_modernos.cpp`  |
| 04  | Estruturas de controle (if/else, switch, for, while, do-while, break, continue)                         | `src/aula04_controle.cpp`        |

> Aulas 03 e 04 estao bloqueadas no menu — serao liberadas conforme o curso avanca.

---

## Pre-requisitos

| Ferramenta | Versao minima | Como verificar       |
| ---------- | ------------- | -------------------- |
| CMake      | 3.20          | `cmake --version`    |
| g++        | 12 (C++20)    | `g++ --version`      |
| gdb        | qualquer      | `gdb --version`      |

### Instalar no Ubuntu/Debian

```bash
sudo apt update
sudo apt install cmake g++ gdb
```

---

## Como compilar e rodar

### 1. Clonar o repositorio

```bash
git clone https://github.com/marcioazam/cpp-aulas-dove.git
cd cpp-aulas-dove
```

### 2. Configurar o CMake

```bash
# Modo Debug (recomendado para estudar — mantém símbolos para o debugger)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Modo Release (otimizado, sem símbolos de debug — para distribuição)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

> **Para novatos:** use sempre `Debug` enquanto estiver estudando.
> O modo `Release` remove informações que o debugger usa para mostrar
> o nome das variáveis, o número da linha, etc.

### 3. Compilar

```bash
cmake --build build
```

### 4. Executar

```bash
# Linux / macOS
./build/cppsmoke

# Windows (MinGW ou MSVC)
.\build\cppsmoke.exe
```

---

## Depuracao no VS Code (Debug com F5)

### Por que o programa pede input mas nao aceita digitacao?

O **Debug Console** do VS Code exibe a saida do programa mas **nao aceita
entrada de teclado** (`std::cin`). Para programas interativos, o `.vscode/launch.json`
ja esta configurado com `"externalConsole": true`, que abre um terminal separado
onde voce pode digitar normalmente.

**Fluxo correto:**

1. Compile primeiro: `Ctrl+Shift+B`
2. Abra o painel Run & Debug: `Ctrl+Shift+D`
3. Selecione **"Debug (CMake)"** no dropdown
4. Pressione `F5` — um terminal externo vai abrir
5. Digite o numero da aula nesse terminal e pressione Enter

### Por que os erros de IntelliSense somem depois de compilar?

O IntelliSense do VS Code usa o arquivo `build/compile_commands.json` para
saber quais headers estao disponiveis e quais flags de compilacao estao ativas.
Esse arquivo e gerado pelo CMake no passo 2 acima. Sem ele, o VS Code nao
consegue resolver os `#include` e mostra erros de "cannot open source file".

**Se os erros persistirem apos compilar:**
`Ctrl+Shift+P` → `C/C++: Reset IntelliSense Database`

### Por que o executavel nao existe na primeira vez?

O CMake tem duas etapas separadas:

| Etapa             | Comando                   | O que faz                                      |
| ----------------- | ------------------------- | ---------------------------------------------- |
| Configurar        | `cmake -S . -B build ...` | Gera Makefile + `compile_commands.json`        |
| Compilar          | `cmake --build build`     | Compila o codigo e gera o executavel           |

A pasta `build/` so e criada na etapa de configuracao.
O executavel `build/cppsmoke` so existe apos a etapa de compilacao.

---

## Estrutura do projeto

```
.
├── include/                  # Headers (.h) de cada aula
│   ├── aula01_tipos.h
│   ├── aula02_ponteiros.h
│   ├── aula03_tipos_modernos.h
│   └── aula04_controle.h
├── src/                      # Implementacoes (.cpp) + ponto de entrada
│   ├── main.cpp              # Menu de selecao de aula
│   ├── aula01_tipos.cpp
│   ├── aula02_ponteiros.cpp
│   ├── aula03_tipos_modernos.cpp
│   └── aula04_controle.cpp
├── exercicios/               # Exercicios e solucoes por aula
├── CMakeLists.txt            # Definicao do build (fontes, flags, C++20)
├── CMakePresets.json         # Presets opcionais do CMake
└── .vscode/
    ├── c_cpp_properties.json # IntelliSense: aponta para build/compile_commands.json
    ├── tasks.json            # Ctrl+Shift+B: configura e compila via CMake
    └── launch.json           # F5: debug com GDB + terminal externo
```

---

## Selecionando a aula

Ao executar, um menu aparece no terminal:

```
================================
   SELECIONE A AULA
================================
 1 - Tipos de dados
 2 - Ponteiros, Pilha, Fila e Matriz
================================
Aula:
```

Digite o numero da aula e pressione Enter.

---

## Windows (MinGW)

```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build
.\build\cppsmoke.exe
```
