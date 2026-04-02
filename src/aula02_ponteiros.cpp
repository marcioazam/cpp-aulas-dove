// =============================================================================
// AULA 02 - PONTEIROS, PILHA, FILA E MATRIZ
// =============================================================================
//
// Tópicos desta aula:
//   1. Ponteiros          — endereços de memória, * e &
//   2. Pilha (stack)      — estrutura LIFO (último a entrar, primeiro a sair)
//   3. Fila (queue)       — estrutura FIFO (primeiro a entrar, primeiro a sair)
//   4. Matriz             — array bidimensional (tabela de linhas e colunas)
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
    std::cout << "=============================================" << std::endl;
    std::cout << "  AULA 02 - PONTEIROS, PILHA, FILA, MATRIZ  " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;


    // =========================================================================
    // 1. PONTEIROS
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
    // =========================================================================

    int  numero   = 100;
    int* ponteiro = &numero;    // ponteiro guarda o endereço de 'numero'

    std::cout << "--- PONTEIROS ---" << std::endl;
    std::cout << "Valor de numero:           " << numero     << std::endl;
    std::cout << "Endereco de numero (&):    " << &numero    << std::endl;
    std::cout << "Valor do ponteiro (p):     " << ponteiro   << "  (mesmo endereco)" << std::endl;
    std::cout << "Valor apontado (*p):       " << *ponteiro  << "  (mesmo valor de numero)" << std::endl;

    // Modificar via ponteiro modifica o original
    *ponteiro = 200;
    std::cout << "Apos *p = 200:" << std::endl;
    std::cout << "  numero agora vale:       " << numero     << "  (foi alterado pelo ponteiro!)" << std::endl;

    // Ponteiro nulo — nunca acesse sem verificar
    int* nulo = nullptr;
    std::cout << "Ponteiro nulo == nullptr?  " << (nulo == nullptr ? "sim" : "nao") << std::endl;
    if (nulo != nullptr) {
        std::cout << *nulo << std::endl;   // nunca executa — seguro
    } else {
        std::cout << "Acesso bloqueado: ponteiro esta nulo" << std::endl;
    }

    // Ponteiro para ponteiro
    int** pp = &ponteiro;   // pp guarda o endereço do ponteiro p
    std::cout << "**pp (ponteiro de ponteiro): " << **pp << "  (mesmo valor)" << std::endl << std::endl;


    // =========================================================================
    // 2. PILHA (STACK) — LIFO: Last In, First Out
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
    //   pop()    → remove o topo
    //   top()    → lê o topo sem remover
    //   empty()  → verifica se está vazia
    // =========================================================================

    std::stack<int> pilha;

    std::cout << "--- PILHA (LIFO) ---" << std::endl;
    std::cout << "Empilhando: 10, 20, 30" << std::endl;
    pilha.push(10);
    pilha.push(20);
    pilha.push(30);   // topo atual

    std::cout << "Topo da pilha: " << pilha.top() << "  (ultimo empilhado)" << std::endl;

    std::cout << "Desempilhando (pop): ";
    while (!pilha.empty()) {
        std::cout << pilha.top() << " ";
        pilha.pop();
    }
    std::cout << "(sai em ordem inversa ao que entrou)" << std::endl << std::endl;


    // =========================================================================
    // 3. FILA (QUEUE) — FIFO: First In, First Out
    // =========================================================================
    // ANALOGIA: fila de banco.
    //   - Quem chega primeiro entra no final da fila (push/enqueue).
    //   - Quem é atendido sai da frente (pop/dequeue).
    //   - O primeiro a entrar é o primeiro a sair.
    //
    // USO REAL:
    //   - Fila de impressão de documentos
    //   - Requisições HTTP em servidores web
    //   - Mensagens em sistemas de filas (Kafka, RabbitMQ)
    //   - BFS (busca em largura) em grafos
    //
    // OPERAÇÕES:
    //   push(x)  → entra no FINAL da fila
    //   pop()    → remove a FRENTE da fila
    //   front()  → lê a frente sem remover
    //   back()   → lê o final sem remover
    //   empty()  → verifica se está vazia
    // =========================================================================

    std::queue<std::string> fila;

    std::cout << "--- FILA (FIFO) ---" << std::endl;
    std::cout << "Entrando na fila: Ana, Bruno, Carla" << std::endl;
    fila.push("Ana");
    fila.push("Bruno");
    fila.push("Carla");

    std::cout << "Frente da fila: " << fila.front() << "  (primeira a entrar)" << std::endl;
    std::cout << "Final da fila:  " << fila.back()  << "  (ultima a entrar)"   << std::endl;

    std::cout << "Atendendo (sai pela frente): ";
    while (!fila.empty()) {
        std::cout << fila.front() << " ";
        fila.pop();
    }
    std::cout << "(mesma ordem que entrou)" << std::endl << std::endl;


    // =========================================================================
    // 4. MATRIZ — ARRAY BIDIMENSIONAL (tabela linhas × colunas)
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

    const int LINHAS = 3;
    const int COLUNAS = 3;

    int matriz[LINHAS][COLUNAS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::cout << "--- MATRIZ 3x3 ---" << std::endl;
    std::cout << "Visualizacao da tabela:" << std::endl;
    for (int i = 0; i < LINHAS; ++i) {
        std::cout << "  [ ";
        for (int j = 0; j < COLUNAS; ++j) {
            std::cout << matriz[i][j];
            if (j < COLUNAS - 1) std::cout << "  ";
        }
        std::cout << " ]" << std::endl;
    }

    std::cout << "Acesso direto: matriz[0][0]=" << matriz[0][0]
              << "  matriz[1][2]=" << matriz[1][2]
              << "  matriz[2][2]=" << matriz[2][2] << std::endl;

    // Soma da diagonal principal (canto superior esquerdo ao inferior direito)
    int somaDiagonal = 0;
    for (int i = 0; i < LINHAS; ++i) {
        somaDiagonal += matriz[i][i];
    }
    std::cout << "Soma da diagonal principal (1+5+9): " << somaDiagonal << std::endl;

    // Transposição: troca linhas por colunas
    std::cout << "Matriz transposta (linhas viram colunas):" << std::endl;
    for (int j = 0; j < COLUNAS; ++j) {
        std::cout << "  [ ";
        for (int i = 0; i < LINHAS; ++i) {
            std::cout << matriz[i][j];
            if (i < LINHAS - 1) std::cout << "  ";
        }
        std::cout << " ]" << std::endl;
    }
    std::cout << std::endl;
}
