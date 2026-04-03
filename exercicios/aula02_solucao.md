# Solução — Aula 02: Array, Ponteiros, Pilha, Fila e Matriz

> Tente resolver o exercício antes de consultar esta solução.

---

---

# Solução 1 — Array (Vetor)

## Código

```cpp
#include <iostream>

int main()
{
    int placar[5] = {120, 85, 200, 95, 150};

    std::cout << "=== PLACAR DO TORNEIO ===" << std::endl;
    std::cout << "Jogador 0: " << placar[0] << " pontos" << std::endl;
    std::cout << "Jogador 1: " << placar[1] << " pontos" << std::endl;
    std::cout << "Jogador 2: " << placar[2] << " pontos" << std::endl;
    std::cout << "Jogador 3: " << placar[3] << " pontos" << std::endl;
    std::cout << "Jogador 4: " << placar[4] << " pontos" << std::endl;

    placar[2] = 0;
    std::cout << "Jogador 2 desclassificado. Novo placar: " << placar[2] << " pontos" << std::endl;

    int total = placar[0] + placar[1] + placar[2] + placar[3] + placar[4];
    std::cout << "Total de pontos na competicao: " << total << std::endl;

    int numJogadores = sizeof(placar) / sizeof(placar[0]);
    std::cout << "Numero de jogadores: " << numJogadores << std::endl;

    return 0;
}
```

## Saída esperada

```
=== PLACAR DO TORNEIO ===
Jogador 0: 120 pontos
Jogador 1: 85 pontos
Jogador 2: 200 pontos
Jogador 3: 95 pontos
Jogador 4: 150 pontos
Jogador 2 desclassificado. Novo placar: 0 pontos
Total de pontos na competicao: 450
Numero de jogadores: 5
```

## Explicações

### Por que `placar[2] = 0` e não `placar[3]`?

Índices começam em 0. O "jogador 3" no enunciado é o terceiro jogador contando a partir do 1 —
mas no array ele ocupa o índice 2. Essa é a confusão mais comum de iniciantes com arrays: o
**índice é a posição contada a partir do zero**, não a partir do um.

### Por que a soma deu 450 e não 650?

Porque `placar[2]` foi alterado para 0 **antes** da soma. `120 + 85 + 0 + 95 + 150 = 450`.
A ordem das operações importa.

### O `sizeof` trick funciona sempre?

Só para arrays declarados localmente com tamanho fixo. Se você passar o array como parâmetro
para uma função, ele vira um ponteiro e `sizeof` retornará o tamanho do ponteiro (8 bytes em
64-bit), não do array inteiro. Quando chegarmos em funções, usaremos `std::array` ou passaremos
o tamanho separado.

---

---

# Solução 2 — Ponteiros

## Código

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    double  temperatura = 36.5;
    double* sensor      = &temperatura;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== SENSOR DE TEMPERATURA ===" << std::endl;
    std::cout << "Temperatura direta:       " << temperatura << " C" << std::endl;
    std::cout << "Endereco de temperatura:  " << &temperatura << std::endl;
    std::cout << "Endereco no ponteiro:     " << sensor       << "  (mesmo endereco)" << std::endl;
    std::cout << "Valor via ponteiro:       " << *sensor      << " C" << std::endl;

    *sensor = 37.8;
    std::cout << "Apos *sensor = 37.80:" << std::endl;
    std::cout << "  temperatura agora:      " << temperatura << " C  <- alterada pelo ponteiro!" << std::endl;

    return 0;
}
```

## Saída esperada

```
=== SENSOR DE TEMPERATURA ===
Temperatura direta:       36.50 C
Endereco de temperatura:  0x7fff... (varia a cada execucao)
Endereco no ponteiro:     0x7fff... (mesmo endereco)
Valor via ponteiro:       36.50 C
Apos *sensor = 37.80:
  temperatura agora:      37.80 C  <- alterada pelo ponteiro!
```

## Explicações

### Por que `sensor` e `&temperatura` exibem o mesmo valor?

Porque `sensor = &temperatura` armazenou o endereço de `temperatura` dentro de `sensor`. Imprimir
`sensor` (o conteúdo do ponteiro, que é um endereço) e `&temperatura` (o endereço da variável)
resulta no mesmo número — são a mesma caixa de memória.

### Por que alterar `*sensor` muda `temperatura`?

`*sensor` significa "vá até o endereço guardado em sensor e escreva lá". Como sensor aponta para
`temperatura`, você está escrevendo diretamente no espaço de memória de `temperatura`. Não existe
cópia — é a mesma memória.

---

---

# Solução 3 — Pilha (LIFO)

## Código

```cpp
#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::stack<std::string> historico;

    historico.push("Digitou: Ola mundo");
    historico.push("Apagou: mundo");
    historico.push("Digitou: C++");

    std::cout << "=== HISTORICO DO EDITOR ===" << std::endl;
    std::cout << "Acoes registradas: " << historico.size() << std::endl;
    std::cout << "Ultima acao: " << historico.top() << std::endl;

    std::cout << "Desfazendo acoes (LIFO):" << std::endl;

    std::cout << "  Desfez: " << historico.top() << std::endl;
    historico.pop();

    std::cout << "  Desfez: " << historico.top() << std::endl;
    historico.pop();

    std::cout << "  Desfez: " << historico.top() << std::endl;
    historico.pop();

    std::cout << "Historico vazio. Nenhuma acao para desfazer." << std::endl;

    return 0;
}
```

## Saída esperada

```
=== HISTORICO DO EDITOR ===
Acoes registradas: 3
Ultima acao: Digitou: C++
Desfazendo acoes (LIFO):
  Desfez: Digitou: C++
  Desfez: Apagou: mundo
  Desfez: Digitou: Ola mundo
Historico vazio. Nenhuma acao para desfazer.
```

## Explicações

### Por que ler com `top()` antes de `pop()`?

`pop()` remove o elemento mas **não retorna** o valor. Se você chamar `pop()` primeiro, perde o
valor para sempre sem ter conseguido exibi-lo. O padrão correto é sempre: leia com `top()`,
depois remova com `pop()`.

### Por que a saída é inversa à ordem de entrada?

LIFO (Last In, First Out): o último a entrar (`"Digitou: C++"`) é o primeiro a sair. Pense na
pilha de pratos — você não consegue pegar o prato de baixo sem retirar os de cima primeiro.

---

---

# Solução 4 — Fila (FIFO)

## Código

```cpp
#include <iostream>
#include <queue>
#include <string>

int main()
{
    std::queue<std::string> chamados;

    chamados.push("Chamado #001: Impressora nao funciona");
    chamados.push("Chamado #002: Sem acesso a internet");
    chamados.push("Chamado #003: Computador lento");

    std::cout << "=== FILA DE SUPORTE ===" << std::endl;
    std::cout << "Chamados na fila: " << chamados.size() << std::endl;
    std::cout << "Proximo a ser atendido: " << chamados.front() << std::endl;
    std::cout << "Ultimo da fila:         " << chamados.back()  << std::endl;

    std::cout << "Atendendo (FIFO):" << std::endl;

    std::cout << "  Atendendo: " << chamados.front() << std::endl;
    chamados.pop();

    std::cout << "  Atendendo: " << chamados.front() << std::endl;
    chamados.pop();

    std::cout << "  Atendendo: " << chamados.front() << std::endl;
    chamados.pop();

    std::cout << "Fila vazia. Todos atendidos!" << std::endl;

    return 0;
}
```

## Saída esperada

```
=== FILA DE SUPORTE ===
Chamados na fila: 3
Proximo a ser atendido: Chamado #001: Impressora nao funciona
Ultimo da fila:         Chamado #003: Computador lento
Atendendo (FIFO):
  Atendendo: Chamado #001: Impressora nao funciona
  Atendendo: Chamado #002: Sem acesso a internet
  Atendendo: Chamado #003: Computador lento
Fila vazia. Todos atendidos!
```

## Explicações

### Qual a diferença entre `front()` e `back()`?

`front()` lê o elemento na **frente** da fila (o mais antigo, o próximo a ser removido).
`back()` lê o elemento no **final** da fila (o mais recente, o último a entrar). Ambos leem
sem remover. `pop()` remove apenas a frente.

### Por que a ordem de saída é igual à de entrada?

FIFO (First In, First Out): o primeiro a entrar (`#001`) é o primeiro a ser atendido. É o
comportamento justo de uma fila — quem chegou primeiro é atendido primeiro.

---

---

# Solução 5 — Matriz

## Código

```cpp
#include <iostream>

int main()
{
    int pontos[3][3] = {
        {3, 0, 3},   // Time A: R1=3, R2=0, R3=3
        {1, 3, 1},   // Time B: R1=1, R2=3, R3=1
        {0, 1, 3}    // Time C: R1=0, R2=1, R3=3
    };

    std::cout << "=== TABELA DO CAMPEONATO ===" << std::endl;
    std::cout << "         R1  R2  R3" << std::endl;
    std::cout << "Time A:   " << pontos[0][0] << "   " << pontos[0][1] << "   " << pontos[0][2] << std::endl;
    std::cout << "Time B:   " << pontos[1][0] << "   " << pontos[1][1] << "   " << pontos[1][2] << std::endl;
    std::cout << "Time C:   " << pontos[2][0] << "   " << pontos[2][1] << "   " << pontos[2][2] << std::endl;

    std::cout << "Time B, Rodada 3: " << pontos[1][2] << " ponto(s)" << std::endl;
    std::cout << "Time C, Rodada 1: " << pontos[2][0] << " ponto(s)" << std::endl;

    int totalTimeA  = pontos[0][0] + pontos[0][1] + pontos[0][2];
    int totalRod2   = pontos[0][1] + pontos[1][1] + pontos[2][1];

    std::cout << "Total Time A: " << totalTimeA << " pontos" << std::endl;
    std::cout << "Total Rodada 2: " << totalRod2 << " pontos" << std::endl;

    return 0;
}
```

## Saída esperada

```
=== TABELA DO CAMPEONATO ===
         R1  R2  R3
Time A:   3   0   3
Time B:   1   3   1
Time C:   0   1   3
Time B, Rodada 3: 1 ponto(s)
Time C, Rodada 1: 0 ponto(s)
Total Time A: 6 pontos
Total Rodada 2: 4 pontos
```

## Explicações

### Como interpretar `pontos[time][rodada]`?

O primeiro índice é a **linha** (time) e o segundo é a **coluna** (rodada). Seguindo a convenção
matemática de matrizes: `[linha][coluna]`. Então `pontos[1][2]` = linha 1 (Time B), coluna 2
(Rodada 3) = 1 ponto.

### Por que `pontos[0][1] + pontos[1][1] + pontos[2][1]` dá o total da Rodada 2?

A Rodada 2 é a coluna de índice 1. Para somar toda uma coluna, fixamos o segundo índice (`1`) e
percorremos todas as linhas: `pontos[0][1]` (Time A na R2) + `pontos[1][1]` (Time B na R2) +
`pontos[2][1]` (Time C na R2) = 0 + 3 + 1 = 4.
