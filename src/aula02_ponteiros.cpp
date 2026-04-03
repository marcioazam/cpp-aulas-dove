// =============================================================================
// AULA 02 - ARRAY, PONTEIROS, PILHA, FILA E MATRIZ
// =============================================================================
//
// Tópicos desta aula:
//   1. Array (vetor)      — sequência de valores do mesmo tipo
//   2. Ponteiros          — endereços de memória, * e &
//   3. Pilha (stack)      — estrutura LIFO (último a entrar, primeiro a sair)
//   4. Fila (queue)       — estrutura FIFO (primeiro a entrar, primeiro a sair)
//   5. Matriz             — array bidimensional (tabela de linhas e colunas)
//
// =============================================================================

#include "aula02_ponteiros.h"
#include <iostream>
#include <stack>    // std::stack  (pilha)
#include <queue>    // std::queue  (fila)

// =============================================================================
// PONTO DE ENTRADA DA AULA 02
// =============================================================================
void rodarAula02()
{
    std::cout << "============================================================" << std::endl;
    std::cout << "  AULA 02 - ARRAY, PONTEIROS, PILHA, FILA, MATRIZ          " << std::endl;
    std::cout << "============================================================" << std::endl << std::endl;


    // =========================================================================
    // 1. ARRAY (VETOR) — sequência de valores do mesmo tipo
    // =========================================================================
    // ANALOGIA: uma fileira de caixas numeradas, uma ao lado da outra.
    //   Cada caixa guarda um valor do mesmo tipo.
    //   Cada caixa tem um ÍNDICE (posição), começando SEMPRE em 0.
    //
    //   int arr[5] = {10, 20, 30, 40, 50};
    //
    //   Índice:   [0]  [1]  [2]  [3]  [4]
    //   Valor:     10   20   30   40   50
    //
    // DECLARAÇÃO:
    //   int arr[5];                         → 5 caixas, valores não inicializados
    //   int arr[5] = {10, 20, 30, 40, 50};  → 5 caixas com valores definidos
    //   int arr[]  = {10, 20, 30, 40, 50};  → tamanho deduzido automaticamente
    //
    // ACESSO:
    //   arr[0]  → primeiro elemento (índice 0, não 1!)
    //   arr[4]  → último elemento de um array com 5 posições
    //
    // CUIDADO: arr[5] em um array de 5 elementos não existe!
    //   Isso causa comportamento indefinido (bug silencioso ou crash).
    // =========================================================================

    int arr[5] = {10, 20, 30, 40, 50};

    std::cout << "--- ARRAY (VETOR) ---" << std::endl;
    std::cout << "Array declarado com 5 elementos: {10, 20, 30, 40, 50}" << std::endl;
    std::cout << "  arr[0] = " << arr[0] << "  <- primeiro elemento (indice 0)" << std::endl;
    std::cout << "  arr[1] = " << arr[1] << std::endl;
    std::cout << "  arr[2] = " << arr[2] << std::endl;
    std::cout << "  arr[3] = " << arr[3] << std::endl;
    std::cout << "  arr[4] = " << arr[4] << "  <- ultimo elemento (indice 4, nao 5!)" << std::endl;

    // Modificar um elemento: basta atribuir pelo índice
    arr[2] = 999;
    std::cout << "Apos arr[2] = 999:" << std::endl;
    std::cout << "  arr[2] = " << arr[2] << "  (so esse elemento mudou)" << std::endl;

    // Tamanho do array: sizeof(arr) retorna o total de bytes do array.
    // sizeof(arr[0]) retorna quantos bytes ocupa UM elemento.
    // Dividindo, obtemos o número de elementos — funciona apenas para arrays
    // declarados localmente (não para ponteiros ou parâmetros de função).
    int tamanho = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Tamanho do array: " << tamanho << " elementos" << std::endl;
    std::cout << "  sizeof(arr)    = " << sizeof(arr)    << " bytes  (5 ints * 4 bytes cada)" << std::endl;
    std::cout << "  sizeof(arr[0]) = " << sizeof(arr[0]) << " bytes  (1 int)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 2. PONTEIROS
    // =========================================================================
    // ANALOGIA: imagine que a memória do computador é um grande prédio com
    // apartamentos numerados. Cada variável mora em um apartamento (endereço).
    //
    // Um PONTEIRO é um papel onde você anota o NÚMERO DO APARTAMENTO.
    // Ele não guarda o valor — guarda o ENDEREÇO de onde o valor está.
    //
    //   int x = 42;      → cria a variável x no "apartamento" 0x1A2B
    //   int* p = &x;     → p guarda o endereço 0x1A2B (o número do apt de x)
    //   *p               → "vá até o endereço em p e pegue o valor de lá" = 42
    //
    // OPERADORES:
    //   &variavel  → "qual é o endereço desta variável?" (address-of)
    //   *ponteiro  → "qual é o valor no endereço deste ponteiro?" (dereference)
    //
    // REGRA DE OURO: sempre verifique se o ponteiro != nullptr antes de usar *p
    // (aprenderemos a fazer essa verificação quando estudarmos condicionais)
    // =========================================================================

    int  numero   = 100;
    int* ponteiro = &numero;    // ponteiro guarda o endereço de 'numero'

    // O endereço de memória é um número hexadecimal (base 16, ex: 0x7ffe3a1b).
    // Pense nele como o "numero do apartamento" — um identificador único na RAM.
    // Você nunca escreve esse número à mão; o sistema operacional escolhe.

    std::cout << "--- PONTEIROS ---" << std::endl;
    std::cout << "Valor de numero:           " << numero     << std::endl;
    std::cout << "Endereco de numero (&):    " << &numero    << "  <- numero do 'apartamento' na RAM" << std::endl;
    std::cout << "Valor do ponteiro (p):     " << ponteiro   << "  <- mesmo endereco" << std::endl;
    std::cout << "Valor apontado (*p):       " << *ponteiro  << "  <- vai ate o endereco e pega o valor" << std::endl;

    // Modificar via ponteiro modifica o original
    *ponteiro = 200;
    std::cout << "Apos *p = 200:" << std::endl;
    std::cout << "  numero agora vale:       " << numero     << "  (foi alterado pelo ponteiro!)" << std::endl;

    // ---- nullptr ----
    //
    // ANALOGIA: placa em branco oficial.
    //   int* p = &x;     → a placa tem o endereço de x
    //   int* p = nullptr; → a placa está EM BRANCO (não aponta para nada)
    //
    // nullptr vs NULL vs 0 (por que usar nullptr?):
    //   Antes do C++11, usava-se NULL ou o número 0 para indicar ponteiro nulo.
    //   O problema: NULL era definido como #define NULL 0 — um número inteiro
    //   disfarçado de ponteiro. O compilador podia confundir:
    //     void f(int);    f(NULL);  ← chamava f com o número 0, não um ponteiro!
    //   nullptr é do tipo std::nullptr_t — só pode ser atribuído a ponteiros.
    //   É inequívoco e seguro. Nunca use NULL ou 0 em C++ moderno.
    //
    // REGRA DE OURO: nunca acesse *p sem verificar se p != nullptr primeiro.
    //   Acessar um ponteiro nulo causa segmentation fault (crash imediato).
    //   Na Aula 04 aprenderemos a fazer essa verificação com if/else.
    int* nulo = nullptr;

    std::cout << std::boolalpha;   // imprime true/false em vez de 1/0
    std::cout << "nullptr — ponteiro nulo:" << std::endl;
    std::cout << "  nulo == nullptr:     " << (nulo == nullptr)     << "  (esta nulo)"     << std::endl;
    std::cout << "  ponteiro == nullptr: " << (ponteiro == nullptr)  << "  (aponta para numero)" << std::endl;
    std::cout << "  Acessar *nulo causaria segmentation fault — nunca faca sem verificar." << std::endl;
    std::cout << "  (Aprenderemos a verificar com if/else na Aula 04.)" << std::endl;


    // =========================================================================
    // 3. PILHA (STACK) — LIFO: Last In, First Out
    // =========================================================================
    // ANALOGIA: uma pilha de pratos.
    //   - Você coloca pratos UM A UM por cima (push).
    //   - Quando pega, pega sempre o DO TOPO (pop).
    //   - O último prato colocado é o primeiro a sair.
    //
    // USO REAL:
    //   - Histórico de "desfazer" (Ctrl+Z) em editores
    //   - Chamadas de funções (o programa usa uma pilha internamente)
    //   - Avaliação de expressões matemáticas
    //
    // OPERAÇÕES:
    //   push(x)  → coloca x no topo
    //   pop()    → remove o topo (sem retornar o valor)
    //   top()    → lê o topo sem remover
    //   empty()  → verdadeiro se a pilha estiver vazia
    //   size()   → quantos elementos há na pilha
    // =========================================================================

    std::stack<int> pilha;

    std::cout << "--- PILHA (LIFO) ---" << std::endl;
    std::cout << "Empilhando: push(10), push(20), push(30)" << std::endl;
    pilha.push(10);
    pilha.push(20);
    pilha.push(30);   // topo atual

    std::cout << "Topo da pilha: " << pilha.top() << "  (ultimo empilhado)" << std::endl;
    std::cout << "Tamanho:       " << pilha.size() << " elementos" << std::endl;

    std::cout << "Desempilhando (ordem LIFO — sai ao contrario de como entrou):" << std::endl;
    std::cout << "  topo: " << pilha.top() << std::endl;  pilha.pop();   // sai 30
    std::cout << "  topo: " << pilha.top() << std::endl;  pilha.pop();   // sai 20
    std::cout << "  topo: " << pilha.top() << std::endl;  pilha.pop();   // sai 10
    std::cout << "Pilha vazia agora. Entrou: 10 20 30 | Saiu: 30 20 10" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 4. FILA (QUEUE) — FIFO: First In, First Out
    // =========================================================================
    // ANALOGIA: fila de banco.
    //   - Quem chega primeiro fica na frente (push).
    //   - O primeiro a entrar é o primeiro a ser atendido (pop pela frente).
    //
    // USO REAL:
    //   - Fila de impressão: o primeiro documento enviado é o primeiro a imprimir
    //   - Atendimento de suporte: o primeiro cliente que abriu chamado é atendido primeiro
    //   - Download em sequência: arquivos baixam na ordem em que foram pedidos
    //
    // OPERAÇÕES:
    //   push(x)  → entra no FINAL da fila
    //   pop()    → remove a FRENTE da fila (sem retornar o valor)
    //   front()  → lê a frente sem remover
    //   back()   → lê o final sem remover
    //   empty()  → verdadeiro se a fila estiver vazia
    //   size()   → quantos elementos há na fila
    // =========================================================================

    std::queue<std::string> fila;

    std::cout << "--- FILA (FIFO) ---" << std::endl;
    std::cout << "Entrando na fila: push(Ana), push(Bruno), push(Carla)" << std::endl;
    fila.push("Ana");
    fila.push("Bruno");
    fila.push("Carla");

    std::cout << "Frente da fila: " << fila.front() << "  (primeira a entrar)" << std::endl;
    std::cout << "Final da fila:  " << fila.back()  << "  (ultima a entrar)"   << std::endl;
    std::cout << "Tamanho:        " << fila.size()  << " pessoas" << std::endl;

    std::cout << "Atendendo (ordem FIFO — sai na mesma ordem que entrou):" << std::endl;
    std::cout << "  atendendo: " << fila.front() << std::endl;  fila.pop();   // sai Ana
    std::cout << "  atendendo: " << fila.front() << std::endl;  fila.pop();   // sai Bruno
    std::cout << "  atendendo: " << fila.front() << std::endl;  fila.pop();   // sai Carla
    std::cout << "Fila vazia agora. Entrou: Ana Bruno Carla | Saiu: Ana Bruno Carla" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 5. MATRIZ — ARRAY BIDIMENSIONAL (tabela linhas × colunas)
    // =========================================================================
    // ANALOGIA: uma tabela de Excel — tem linhas e colunas.
    //   matriz[linha][coluna]
    //
    //         col 0  col 1  col 2
    //  linha 0:  1      2      3
    //  linha 1:  4      5      6
    //  linha 2:  7      8      9
    //
    // DECLARAÇÃO:
    //   int m[3][3];            → matriz 3×3 (3 linhas, 3 colunas)
    //   int m[3][3] = {{...}};  → com valores iniciais
    //
    // ACESSO:
    //   m[0][0] → linha 0, coluna 0 → valor 1
    //   m[1][2] → linha 1, coluna 2 → valor 6
    //
    // USO REAL:
    //   - Imagens (cada pixel é uma célula da matriz)
    //   - Jogos de tabuleiro (xadrez, campo minado)
    //   - Planilhas, mapas, grades em geral
    // =========================================================================

    const int LINHAS  = 3;
    const int COLUNAS = 3;

    int matriz[LINHAS][COLUNAS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::cout << "--- MATRIZ 3x3 ---" << std::endl;
    std::cout << "Visualizacao da tabela:" << std::endl;
    std::cout << "  [ " << matriz[0][0] << "  " << matriz[0][1] << "  " << matriz[0][2] << " ]" << std::endl;
    std::cout << "  [ " << matriz[1][0] << "  " << matriz[1][1] << "  " << matriz[1][2] << " ]" << std::endl;
    std::cout << "  [ " << matriz[2][0] << "  " << matriz[2][1] << "  " << matriz[2][2] << " ]" << std::endl;

    std::cout << "Acesso direto: matriz[0][0]=" << matriz[0][0]
              << "  matriz[1][2]=" << matriz[1][2]
              << "  matriz[2][2]=" << matriz[2][2] << std::endl;

    // Soma da diagonal principal (canto superior esquerdo ao inferior direito)
    // diagonal: [0][0]=1, [1][1]=5, [2][2]=9
    int somaDiagonal = matriz[0][0] + matriz[1][1] + matriz[2][2];
    std::cout << "Soma da diagonal principal (1+5+9): " << somaDiagonal << std::endl;

    // Transposição: "virar" a matriz — linha vira coluna, coluna vira linha.
    // Para ler a transposta, basta trocar os índices: m[i][j] → m[j][i].
    //
    // Original:        Transposta:
    //  [ 1  2  3 ]      [ 1  4  7 ]
    //  [ 4  5  6 ]  ->  [ 2  5  8 ]
    //  [ 7  8  9 ]      [ 3  6  9 ]
    //
    // Primeira coluna original (1,4,7) vira a primeira linha transposta.
    std::cout << "Transposta (coluna vira linha):" << std::endl;
    std::cout << "  [ " << matriz[0][0] << "  " << matriz[1][0] << "  " << matriz[2][0] << " ]" << std::endl;
    std::cout << "  [ " << matriz[0][1] << "  " << matriz[1][1] << "  " << matriz[2][1] << " ]" << std::endl;
    std::cout << "  [ " << matriz[0][2] << "  " << matriz[1][2] << "  " << matriz[2][2] << " ]" << std::endl;
    std::cout << std::endl;
}
