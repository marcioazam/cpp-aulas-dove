# Exercício — Aula 02: Array, Ponteiros, Pilha, Fila e Matriz

## Como testar

Compile com:

```bash
cmake --build build
./build/cppsmoke
```

Ou crie um arquivo separado e compile diretamente:

```bash
g++ -std=c++20 -o exercicio src/main_exercicio.cpp
./exercicio
```

---

---

# Exercício 1 — Array (Vetor)

## Contexto

Você está desenvolvendo um sistema de placar para um torneio de 5 jogadores. Os pontos de cada
jogador são armazenados em um array.

## Tarefa

1. Declare um array `int placar[5]` com os valores `{120, 85, 200, 95, 150}`
2. Exiba o placar de cada jogador com o índice correspondente
3. O jogador 3 (índice 2) foi desclassificado — mude seu placar para `0`
4. Exiba o placar atualizado do jogador 3
5. Calcule a soma total dos pontos (sem usar loop — some explicitamente)
6. Exiba o tamanho do array usando o truque `sizeof(placar) / sizeof(placar[0])`

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

## Dicas

- Lembre: índices vão de `0` até `tamanho - 1`. Um array de 5 tem índices 0, 1, 2, 3, 4.
- Para a soma, basta escrever: `int total = placar[0] + placar[1] + placar[2] + placar[3] + placar[4];`
- `sizeof(placar)` retorna o total de bytes; divida por `sizeof(placar[0])` para obter o número de elementos.
- Não use `for` — ainda não vimos laços. Some elemento por elemento.

---

---

# Exercício 2 — Ponteiros

## Contexto

Um sensor de temperatura registra um valor em memória. Você vai acessar e modificar esse valor
usando um ponteiro — simulando como um driver de hardware leria e atualizaria um sensor real.

## Tarefa

1. Declare `double temperatura = 36.5`
2. Declare um ponteiro `double* sensor` que aponta para `temperatura`
3. Exiba:
   - O valor de `temperatura` diretamente
   - O endereço de `temperatura` (use `&temperatura`)
   - O endereço guardado no ponteiro (`sensor`)
   - O valor apontado pelo ponteiro (`*sensor`)
4. Atualize a temperatura para `37.8` usando o ponteiro (`*sensor = 37.8`)
5. Exiba o novo valor de `temperatura` — a variável original mudou!

## Saída esperada

```
=== SENSOR DE TEMPERATURA ===
Temperatura direta:       36.50 C
Endereco de temperatura:  0x... (varia a cada execucao)
Endereco no ponteiro:     0x... (mesmo endereco)
Valor via ponteiro:       36.50 C
Apos *sensor = 37.80:
  temperatura agora:      37.80 C  <- alterada pelo ponteiro!
```

## Dicas

- `double* sensor = &temperatura;` — o `&` captura o endereço da variável.
- `*sensor` acessa o valor no endereço armazenado pelo ponteiro.
- O endereço hexadecimal (`0x...`) varia a cada execução — isso é normal.
- Use `std::fixed << std::setprecision(2)` para exibir 2 casas decimais (inclua `<iomanip>`).

---

---

# Exercício 3 — Pilha (LIFO)

## Contexto

Você está implementando o histórico de "desfazer" (Ctrl+Z) de um editor de texto simples.
Cada ação realizada é empilhada. Desfazer significa tirar a última ação do topo.

## Tarefa

1. Declare uma `std::stack<std::string>` chamada `historico`
2. O usuário realizou 3 ações — empilhe-as em ordem:
   - `"Digitou: Ola mundo"`
   - `"Apagou: mundo"`
   - `"Digitou: C++"`
3. Exiba o tamanho da pilha e o topo (última ação)
4. Simule 3 desfazimentos: para cada um, exiba a ação desfeita e remova do topo

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

## Dicas

- `#include <stack>` e `#include <string>` são necessários.
- Use `pilha.top()` para ver o topo **antes** de chamar `pilha.pop()`.
- `pop()` remove o elemento mas **não retorna** o valor — leia com `top()` primeiro.
- Não use `while` — faça 3 blocos `top()` + `pop()` explícitos.
- Para a última linha, basta imprimir um `cout` fixo após os 3 pops.

---

---

# Exercício 4 — Fila (FIFO)

## Contexto

Uma empresa de suporte técnico recebe chamados e os atende na ordem de chegada. O primeiro
chamado aberto é o primeiro a ser atendido.

## Tarefa

1. Declare uma `std::queue<std::string>` chamada `chamados`
2. Três chamados chegaram em ordem — adicione-os à fila:
   - `"Chamado #001: Impressora nao funciona"`
   - `"Chamado #002: Sem acesso a internet"`
   - `"Chamado #003: Computador lento"`
3. Exiba a fila: tamanho, primeiro chamado (`front()`) e último (`back()`)
4. Atenda os 3 chamados em ordem: para cada um, exiba quem está sendo atendido e remova da fila

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

## Dicas

- `#include <queue>` e `#include <string>` são necessários.
- `fila.front()` lê a frente sem remover. `fila.pop()` remove a frente.
- Não use `while` — faça 3 blocos `front()` + `pop()` explícitos.
- Note que a ordem de saída é **igual** à de entrada — esse é o comportamento FIFO.

---

---

# Exercício 5 — Matriz

## Contexto

Um campeonato de futebol tem 3 times e 3 rodadas. A tabela de pontos é armazenada em uma
matriz onde `pontos[time][rodada]` representa os pontos do time naquela rodada.

## Tarefa

Dado o seguinte placar:

|         | Rodada 1 | Rodada 2 | Rodada 3 |
| ------- | -------- | -------- | -------- |
| Time A  | 3        | 0        | 3        |
| Time B  | 1        | 3        | 1        |
| Time C  | 0        | 1        | 3        |

1. Declare a matriz `int pontos[3][3]` com os valores acima
2. Exiba a tabela formatada (uma linha por time, sem usar `for`)
3. Acesse e exiba células específicas:
   - Pontos do Time B na Rodada 3 (`pontos[1][2]`)
   - Pontos do Time C na Rodada 1 (`pontos[2][0]`)
4. Calcule o total de pontos do Time A somando explicitamente suas 3 rodadas
5. Calcule o total de pontos da Rodada 2 somando explicitamente os 3 times

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

## Dicas

- `pontos[0][0]` = Time A, Rodada 1; `pontos[1][2]` = Time B, Rodada 3.
- O primeiro índice é o **time** (linha); o segundo é a **rodada** (coluna).
- Para o total do Time A: `pontos[0][0] + pontos[0][1] + pontos[0][2]`
- Para o total da Rodada 2: `pontos[0][1] + pontos[1][1] + pontos[2][1]`
- Não use `for` — acesse cada célula explicitamente.
