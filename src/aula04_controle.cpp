// =============================================================================
// AULA 04 - ESTRUTURAS DE CONTROLE
// =============================================================================
//
// Estruturas de controle decidem O QUE e QUANTAS VEZES o código executa.
// Sem elas, o programa executaria linha por linha, do início ao fim, sempre.
//
// Tópicos desta aula:
//   10. if / else if / else  — execução condicional + operador ternário
//   11. switch / case        — múltiplas opções de forma organizada
//   12. for                  — loop com contador (clássico e range-based)
//   13. while                — loop enquanto condição for verdadeira
//   14. do-while             — loop que garante pelo menos uma execução
//   15. break e continue     — controle de fluxo dentro de loops
//   40. and, or, not         — tokens alternativos ISO C++ para operadores lógicos
//   41. bitand, bitor, xor, compl — tokens alternativos para operadores bitwise
//
// =============================================================================

#include "aula04_controle.h"
#include <iostream>
#include <string>
#include <stack>
#include <queue>

static void demonstrarEstruturas();
static void demonstrarPilhaFila();
static void demonstrarOperadoresLogicosAlt();
static void demonstrarOperadoresBit();

// =============================================================================
// PONTO DE ENTRADA DA AULA 04
// =============================================================================
void rodarAula04()
{
    std::cout << "=============================================" << std::endl;
    std::cout << "   AULA 04 - ESTRUTURAS DE CONTROLE         " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;


    // =========================================================================
    // 10. IF / ELSE IF / ELSE
    // =========================================================================
    // Executa um bloco de código SE uma condição for verdadeira.
    //
    // Estrutura:
    //   if (condicao) { ... }
    //   else if (outra condicao) { ... }   ← zero ou mais
    //   else { ... }                        ← zero ou um (bloco final)
    //
    // Operadores de comparação:
    //   ==  igual a          !=  diferente de
    //   >   maior que        <   menor que
    //   >=  maior ou igual   <=  menor ou igual
    //
    // Operadores lógicos (combinam condições):
    //   &&  E  — AMBAS precisam ser verdadeiras
    //   ||  OU — PELO MENOS UMA precisa ser verdadeira
    //   !   NÃO — inverte: true vira false, false vira true
    //
    // OPERADOR TERNÁRIO:
    //   variavel = (condicao) ? valor_se_true : valor_se_false;
    //   Use para condições SIMPLES de uma linha. Evite aninhar ternários.
    //
    // Quando usar if vs switch:
    //   if    → condições com ranges, expressões booleanas, tipos não inteiros
    //   switch → comparar UMA variável contra VÁRIOS valores fixos inteiros
    // =========================================================================

    int nota = 75;

    std::cout << "--- IF / ELSE IF / ELSE ---" << std::endl;
    std::cout << "Nota do aluno: " << nota << std::endl;

    if (nota >= 90) {
        std::cout << "Conceito: A" << std::endl;
    } else if (nota >= 70) {
        std::cout << "Conceito: B" << std::endl;
    } else if (nota >= 60) {
        std::cout << "Conceito: C" << std::endl;
    } else {
        std::cout << "Conceito: F — Reprovado" << std::endl;
    }

    // -------------------------------------------------------------------------
    // OPERADOR TERNÁRIO — forma compacta de if/else para expressões simples
    // -------------------------------------------------------------------------
    // Sintaxe: variavel = (condicao) ? valor_se_true : valor_se_false;
    //
    // Equivalência direta:
    //   string s = (nota >= 60) ? "Aprovado" : "Reprovado";
    //   É exatamente igual a:
    //   string s;
    //   if (nota >= 60) { s = "Aprovado"; } else { s = "Reprovado"; }
    //
    // REGRA: use apenas para condições de UMA linha e resultado simples.
    //        Nunca aninhe ternários — isso vira ilegível muito rápido.
    //        Se precisar de mais de um nível, use if/else.
    // -------------------------------------------------------------------------

    std::cout << "--- OPERADOR TERNÁRIO ---" << std::endl;
    std::cout << "nota = " << nota << std::endl;

    std::string aprovacaoStr = (nota >= 60) ? "Aprovado"  : "Reprovado";
    std::string paridade     = (nota % 2 == 0) ? "par"    : "impar";
    int         absoluto     = (nota >= 0)   ? nota       : -nota;

    std::cout << "  Status   (ternario): " << aprovacaoStr << std::endl;
    std::cout << "  Paridade (ternario): " << paridade     << std::endl;
    std::cout << "  Absoluto (ternario): " << absoluto     << std::endl;
    std::cout << std::endl;

    // Combinando condições com && e ||
    int idade    = 17;
    bool temRG   = true;
    bool temCNH  = false;

    if (idade >= 18 && temRG) {
        std::cout << "Pode entrar no evento" << std::endl;
    } else {
        std::cout << "Acesso negado ao evento" << std::endl;
    }

    if (temRG || temCNH) {
        std::cout << "Tem pelo menos um documento" << std::endl;
    }

    // Negação com !
    bool sistemaOffline = false;
    if (!sistemaOffline) {
        std::cout << "Sistema online — pode processar" << std::endl;
    }
    std::cout << std::endl;


    // =========================================================================
    // 11. SWITCH / CASE / DEFAULT
    // =========================================================================
    // Compara UMA variável contra VÁRIOS valores fixos.
    // Mais legível que uma cadeia de if/else if quando há muitas opções.
    //
    // REGRAS IMPORTANTES:
    //   - Só funciona com tipos inteiros: int, char, enum (não float, string)
    //   - Cada case PRECISA de break para não "cair" no próximo (fallthrough)
    //   - default é executado quando nenhum case bate (opcional, mas recomendado)
    //
    // FALLTHROUGH intencional:
    //   Às vezes você QUER que um case execute o próximo. Isso é válido, mas
    //   sempre comente [[fallthrough]] para deixar claro que é intencional.
    //
    // Quando NÃO usar switch:
    //   - Comparar strings (use if/else com ==)
    //   - Condições com ranges (nota >= 70) — use if/else
    //   - Tipos float ou double
    // =========================================================================

    int dia = 3;

    std::cout << "--- SWITCH / CASE ---" << std::endl;
    std::cout << "Dia " << dia << " da semana: ";

    switch (dia) {
        case 1: std::cout << "Domingo"   << std::endl; break;
        case 2: std::cout << "Segunda"   << std::endl; break;
        case 3: std::cout << "Terca"     << std::endl; break;
        case 4: std::cout << "Quarta"    << std::endl; break;
        case 5: std::cout << "Quinta"    << std::endl; break;
        case 6: std::cout << "Sexta"     << std::endl; break;
        case 7: std::cout << "Sabado"    << std::endl; break;
        default: std::cout << "Invalido" << std::endl; break;
    }

    // Fallthrough intencional: agrupando cases
    char tecla = 'A';
    std::cout << "Tecla '" << tecla << "': ";
    switch (tecla) {
        case 'W':
        case 'w':
            std::cout << "Mover para cima" << std::endl; break;
        case 'S':
        case 's':
            std::cout << "Mover para baixo" << std::endl; break;
        case 'A':
        case 'a':
            std::cout << "Mover para esquerda" << std::endl; break;
        case 'D':
        case 'd':
            std::cout << "Mover para direita" << std::endl; break;
        default:
            std::cout << "Tecla sem acao" << std::endl; break;
    }
    std::cout << std::endl;


    // =========================================================================
    // 12. FOR
    // =========================================================================
    // Loop com contador. Use quando SABE quantas iterações serão necessárias.
    //
    // Estrutura clássica:
    //   for (inicialização; condição; incremento) { ... }
    //   - inicialização: executada UMA vez antes do loop
    //   - condição:      verificada ANTES de cada iteração
    //   - incremento:    executado APÓS cada iteração
    //
    // Range-based for (C++11):
    //   for (tipo elemento : colecao) { ... }
    //   - Itera sobre TODOS os elementos de uma coleção automaticamente
    //   - Use 'auto' para evitar escrever o tipo
    //   - Use 'const auto&' para evitar cópia (especialmente com strings/objetos)
    //
    // Quando usar for vs while:
    //   for   → sabe o número de iterações ou itera sobre uma coleção
    //   while → não sabe quantas iterações (depende de evento externo)
    // =========================================================================

    std::cout << "--- FOR ---" << std::endl;

    // For clássico: contador de 1 a 5
    std::cout << "For de 1 a 5:    ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // For decrescente
    std::cout << "Contagem regressiva: ";
    for (int i = 5; i >= 1; --i) {
        std::cout << i << " ";
    }
    std::cout << "Go!" << std::endl;

    // For com incremento diferente (de 2 em 2)
    std::cout << "Numeros pares:   ";
    for (int i = 0; i <= 10; i += 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Range-based for (C++11) — jeito moderno de iterar coleções
    // Funciona com C-arrays (já conhecidos da Aula 02) — sem std::vector!
    std::string frutas[]          = {"Maca", "Banana", "Laranja", "Uva"};
    constexpr size_t NUM_FRUTAS   = sizeof(frutas) / sizeof(frutas[0]);

    std::cout << "Range-based for: ";
    for (const auto& fruta : frutas) {    // const auto& evita cópia de string
        std::cout << fruta << " ";
    }
    std::cout << std::endl;

    // Range-based for com índice (quando precisa do índice também)
    std::cout << "Com indice:      ";
    for (size_t i = 0; i < NUM_FRUTAS; ++i) {
        std::cout << "[" << i << "]" << frutas[i] << " ";
    }
    std::cout << std::endl << std::endl;


    // =========================================================================
    // 13. WHILE
    // =========================================================================
    // Executa o bloco ENQUANTO a condição for verdadeira.
    // A condição é verificada ANTES de cada iteração.
    // Se a condição já começa falsa, o bloco NUNCA executa.
    //
    // Quando usar:
    //   - Número de iterações desconhecido (depende de entrada do usuário,
    //     resultado de rede, estado de arquivo, etc.)
    //   - Aguardar um evento externo
    //   - Processar dados até um sentinel value (valor sentinela)
    //
    // CUIDADO com loop infinito:
    //   while (true) { ... }  é válido, mas PRECISA de um break interno.
    //   Esquecer de atualizar a variável da condição = loop infinito.
    // =========================================================================

    std::cout << "--- WHILE ---" << std::endl;

    // Contador simples com while
    int contador = 1;
    std::cout << "While de 1 a 5:  ";
    while (contador <= 5) {
        std::cout << contador << " ";
        ++contador;   // ESSENCIAL: sem isso, loop infinito!
    }
    std::cout << std::endl;

    // Processar enquanto há vida (simulação)
    int vida     = 100;
    int danoRodada = 30;
    int rodada   = 0;

    std::cout << "Simulacao de batalha:" << std::endl;
    while (vida > 0) {
        ++rodada;
        vida -= danoRodada;
        if (vida < 0) vida = 0;
        std::cout << "  Rodada " << rodada << ": vida = " << vida << std::endl;
    }
    std::cout << "Personagem derrotado na rodada " << rodada << std::endl << std::endl;


    // =========================================================================
    // 14. DO-WHILE
    // =========================================================================
    // GARANTE pelo menos UMA execução, pois verifica a condição DEPOIS do bloco.
    //
    // Diferença de while:
    //   while   → verifica ANTES: pode não executar nenhuma vez
    //   do-while → verifica DEPOIS: executa PELO MENOS uma vez
    //
    // Quando usar:
    //   - Menus de sistema (mostrar pelo menos uma vez, repetir se inválido)
    //   - Validação de entrada do usuário (pedir de novo se errado)
    //   - Qualquer fluxo de "tente ao menos uma vez, repita se necessário"
    // =========================================================================

    std::cout << "--- DO-WHILE ---" << std::endl;

    // Simulação de menu que executa pelo menos uma vez
    // (simulamos a escolha em vez de usar std::cin para não travar o output)
    int opcaoSimulada = 2; // simulando o usuário escolher "Sair"
    int tentativas    = 0;

    do {
        ++tentativas;
        std::cout << "  [Menu] 1-Jogar  2-Sair  (escolha simulada: " << opcaoSimulada << ")" << std::endl;
    } while (opcaoSimulada != 2);

    std::cout << "Saiu apos " << tentativas << " exibicao(oes) do menu" << std::endl;

    // Diferença clara: while vs do-while com condição já falsa
    int valorFalso = 100;

    std::cout << "while (100 < 5):    ";
    while (valorFalso < 5) {
        std::cout << "executou";  // NUNCA executa
    }
    std::cout << "[nao executou]" << std::endl;

    std::cout << "do-while (100 < 5): ";
    do {
        std::cout << "[executou pelo menos uma vez]";  // executa UMA vez
    } while (valorFalso < 5);
    std::cout << std::endl << std::endl;


    // =========================================================================
    // 15. BREAK E CONTINUE
    // =========================================================================
    //
    // BREAK:
    //   Sai IMEDIATAMENTE do loop ou switch mais próximo.
    //   O código depois do loop continua normalmente.
    //   Uso: encontrou o que procurava, erro detectado, condição de parada.
    //
    // CONTINUE:
    //   Pula o RESTANTE da iteração atual e vai para a próxima.
    //   O loop NÃO termina — só pula aquela iteração.
    //   Uso: ignorar itens que não passam em um filtro.
    //
    // CUIDADO: break/continue em loops aninhados afeta apenas o loop MAIS INTERNO.
    //          Para sair de loops externos, use variáveis flag ou refatore para função.
    // =========================================================================

    std::cout << "--- BREAK e CONTINUE ---" << std::endl;

    // BREAK: para ao encontrar o primeiro número divisível por 7
    std::cout << "BREAK — primeiro multiplo de 7: ";
    for (int i = 1; i <= 50; ++i) {
        if (i % 7 == 0) {
            std::cout << i << std::endl;
            break;  // sai do for imediatamente
        }
    }

    // CONTINUE: imprime só os ímpares (pula os pares)
    std::cout << "CONTINUE — impares de 1 a 10: ";
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            continue;  // pula para próxima iteração se for par
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Combinando break e continue: processar lista, parar em -1, pular zeros
    int dados[] = {5, 0, 3, 0, 8, -1, 99, 42};

    std::cout << "Processando lista (pula zeros, para no -1): ";
    for (const auto& valor : dados) {
        if (valor == -1) {
            std::cout << "[PAROU]" << std::endl;
            break;        // sentinel: para o processamento
        }
        if (valor == 0) {
            continue;     // ignora zeros
        }
        std::cout << valor << " ";
    }

    std::cout << std::endl;


    // =========================================================================
    // 40. OPERADORES LÓGICOS ALTERNATIVOS (and / or / not)
    // =========================================================================
    demonstrarOperadoresLogicosAlt();

    // =========================================================================
    // 41. OPERADORES BITWISE ALTERNATIVOS (bitand / bitor / xor / compl)
    // =========================================================================
    demonstrarOperadoresBit();


    // =========================================================================
    // FUNÇÃO COM TODAS AS ESTRUTURAS JUNTAS
    // =========================================================================
    std::cout << "=============================================" << std::endl;
    std::cout << "   FUNCAO COM TODAS AS ESTRUTURAS JUNTAS    " << std::endl;
    std::cout << "=============================================" << std::endl;
    demonstrarEstruturas();

    // =========================================================================
    // BONUS: PILHA (stack) E FILA (queue)
    // =========================================================================
    std::cout << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "   BONUS — PILHA (stack) e FILA (queue)     " << std::endl;
    std::cout << "=============================================" << std::endl;
    demonstrarPilhaFila();
}


// =============================================================================
// FUNÇÃO INTERNA: demonstrarPilhaFila()
// =============================================================================
static void demonstrarPilhaFila()
{
    // =========================================================================
    // PILHA — std::stack<T>
    // =========================================================================
    // Estrutura LIFO: Last In, First Out (último a entrar, primeiro a sair).
    // Pense em uma pilha de pratos: só acessa o do topo.
    //
    // Operações:
    //   push(valor)  — empilha um elemento no TOPO      O(1)
    //   pop()        — desempilha o elemento do TOPO    O(1)  [não retorna valor!]
    //   top()        — lê o elemento do TOPO SEM remover O(1)
    //   empty()      — true se a pilha estiver vazia
    //   size()       — número de elementos
    //
    // Implementação interna: adapta um container (padrão: std::deque).
    //   std::stack<int>              → usa deque (padrão)
    //   std::stack<int, std::vector<int>> → usa vector (mais eficiente para memória)
    //
    // Onde usar:
    //   - Undo/Redo (editor de texto, Ctrl+Z)
    //   - Backtracking (labirinto, sudoku)
    //   - Chamadas de função (a própria call stack do programa usa esse conceito)
    //   - Avaliação de expressões matemáticas: "2 + (3 * 4)" → converte para RPN
    //   - DFS (Busca em Profundidade) iterativa em grafos/árvores
    // =========================================================================

    std::cout << std::endl;
    std::cout << "--- PILHA (std::stack) ---" << std::endl;
    std::cout << "Estrutura LIFO: o ULTIMO a entrar e o PRIMEIRO a sair" << std::endl;

    // Exemplo 1: pilha básica
    std::stack<int> pilha;

    // Empilhando: 10, 20, 30, 40
    pilha.push(10);
    pilha.push(20);
    pilha.push(30);
    pilha.push(40);

    std::cout << "Empilhados: 10, 20, 30, 40" << std::endl;
    std::cout << "Topo atual: " << pilha.top() << std::endl;   // 40
    std::cout << "Tamanho:    " << pilha.size() << std::endl;  // 4

    // Desempilhando (sempre do topo para baixo)
    std::cout << "Desempilhando: ";
    while (!pilha.empty()) {
        std::cout << pilha.top() << " ";  // lê o topo
        pilha.pop();                       // remove o topo (não retorna!)
    }
    std::cout << std::endl;

    // Exemplo 2: simulação de histórico de ações (undo)
    std::cout << std::endl;
    std::cout << "Simulacao de historico Undo:" << std::endl;

    std::stack<std::string> historico;
    historico.push("Abrir arquivo");
    historico.push("Digitar texto");
    historico.push("Formatar negrito");
    historico.push("Inserir imagem");

    std::cout << "  Acoes realizadas: " << historico.size() << std::endl;

    // Desfazendo as últimas 2 ações (Ctrl+Z, Ctrl+Z)
    for (int i = 0; i < 2; ++i) {
        if (!historico.empty()) {
            std::cout << "  [Undo] Desfez: " << historico.top() << std::endl;
            historico.pop();
        }
    }
    std::cout << "  Ultima acao restante: " << historico.top() << std::endl;


    // =========================================================================
    // FILA — std::queue<T>
    // =========================================================================
    // Estrutura FIFO: First In, First Out (primeiro a entrar, primeiro a sair).
    // Pense em uma fila de banco: quem chegou primeiro, sai primeiro.
    //
    // Operações:
    //   push(valor)  — enfileira no FINAL da fila          O(1)
    //   pop()        — remove o elemento da FRENTE          O(1)  [não retorna valor!]
    //   front()      — lê o elemento da FRENTE SEM remover O(1)
    //   back()       — lê o elemento do FINAL SEM remover  O(1)
    //   empty()      — true se a fila estiver vazia
    //   size()       — número de elementos
    //
    // Implementação interna: adapta um container (padrão: std::deque).
    //   std::queue<int>              → usa deque (padrão)
    //   std::queue<int, std::list<int>> → usa list
    //
    // Onde usar:
    //   - Fila de impressão (spooler)
    //   - Fila de tarefas / jobs (task queue)
    //   - BFS (Busca em Largura) em grafos/árvores
    //   - Buffers de streaming e mensagens assíncronas
    //   - Simulações de atendimento (banco, hospital, call center)
    // =========================================================================

    std::cout << std::endl;
    std::cout << "--- FILA (std::queue) ---" << std::endl;
    std::cout << "Estrutura FIFO: o PRIMEIRO a entrar e o PRIMEIRO a sair" << std::endl;

    // Exemplo 1: fila básica
    std::queue<int> fila;

    // Enfileirando: 10, 20, 30, 40
    fila.push(10);
    fila.push(20);
    fila.push(30);
    fila.push(40);

    std::cout << "Enfileirados: 10, 20, 30, 40" << std::endl;
    std::cout << "Frente: " << fila.front() << std::endl;  // 10 (primeiro)
    std::cout << "Final:  " << fila.back()  << std::endl;  // 40 (último)
    std::cout << "Tamanho: " << fila.size() << std::endl;  // 4

    // Removendo na ordem de chegada
    std::cout << "Processando fila: ";
    while (!fila.empty()) {
        std::cout << fila.front() << " ";  // lê a frente
        fila.pop();                         // remove a frente (não retorna!)
    }
    std::cout << std::endl;

    // Exemplo 2: fila de atendimento (simulação de banco)
    std::cout << std::endl;
    std::cout << "Simulacao de fila de banco:" << std::endl;

    std::queue<std::string> atendimento;
    atendimento.push("Cliente Ana");
    atendimento.push("Cliente Bruno");
    atendimento.push("Cliente Carla");
    atendimento.push("Cliente Diego");

    std::cout << "  Fila inicial: " << atendimento.size() << " clientes" << std::endl;
    std::cout << "  Proximo: " << atendimento.front() << std::endl;

    int guiche = 1;
    while (!atendimento.empty()) {
        std::cout << "  Guiche " << guiche++ << " atendeu: " << atendimento.front() << std::endl;
        atendimento.pop();
    }
    std::cout << "  Fila vazia — todos atendidos!" << std::endl;


    // =========================================================================
    // PILHA vs FILA — comparação direta
    // =========================================================================
    std::cout << std::endl;
    std::cout << "--- PILHA vs FILA: comparacao direta ---" << std::endl;
    std::cout << "Inserindo 1, 2, 3 nos dois containers:" << std::endl;

    std::stack<int> s;
    std::queue<int> q;

    int vals[] = {1, 2, 3};
    for (int v : vals) {
        s.push(v);
        q.push(v);
    }

    std::cout << "  Pilha (LIFO, topo primeiro): ";
    while (!s.empty()) { std::cout << s.top()   << " "; s.pop(); }
    std::cout << std::endl;

    std::cout << "  Fila  (FIFO, frente primeiro): ";
    while (!q.empty()) { std::cout << q.front() << " "; q.pop(); }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Resumo:" << std::endl;
    std::cout << "  stack  → LIFO | topo com top()  | header: <stack>"  << std::endl;
    std::cout << "  queue  → FIFO | frente com front() | header: <queue>" << std::endl;
}


// =============================================================================
// FUNÇÃO INTERNA: demonstrarOperadoresLogicosAlt()
// =============================================================================
static void demonstrarOperadoresLogicosAlt()
{
    // =========================================================================
    // OPERADORES LÓGICOS ALTERNATIVOS — and / or / not
    // =========================================================================
    // O C++ define palavras-chave alternativas para os operadores lógicos.
    // São 100% equivalentes — o compilador trata identicamente.
    //
    //   Símbolo │ Alternativa │ Significado
    //   --------│-------------|----------------------------------------------
    //   &&      │ and         │ E lógico — AMBAS precisam ser verdadeiras
    //   ||      │ or          │ OU lógico — PELO MENOS UMA verdadeira
    //   !       │ not         │ NÃO lógico — inverte o valor booleano
    //
    // Por que existem?
    //   - Padrão ISO C++ (C++11 nativo, sem precisar incluir <iso646.h>)
    //   - Origem histórica: teclados que não tinham &, | e !
    //   - Melhoram legibilidade em condições complexas com muitos &&/||
    //
    // Ambos os estilos são válidos. Use o que o projeto adota por consistência.
    // =========================================================================

    std::cout << "--- OPERADORES LOGICOS ALTERNATIVOS (and / or / not) ---" << std::endl;

    int  idade  = 20;
    bool temRG  = true;
    bool temCNH = false;

    // && equivale a 'and'
    std::cout << "Simbolo: (idade >= 18 && temRG)  = " << (idade >= 18 && temRG)  << std::endl;
    std::cout << "Alt.   : (idade >= 18 and temRG) = " << (idade >= 18 and temRG) << std::endl;
    std::cout << std::endl;

    // || equivale a 'or'
    std::cout << "Simbolo: (temRG || temCNH)  = " << (temRG || temCNH)  << std::endl;
    std::cout << "Alt.   : (temRG or temCNH)  = " << (temRG or temCNH)  << std::endl;
    std::cout << std::endl;

    // ! equivale a 'not'
    std::cout << "Simbolo: (!temCNH)      = " << (!temCNH)      << std::endl;
    std::cout << "Alt.   : (not temCNH)   = " << (not temCNH)   << std::endl;
    std::cout << std::endl;

    // Combinando — frase quase em linguagem natural
    if (idade >= 18 and temRG and not temCNH) {
        std::cout << "Maior de idade com RG, mas sem CNH." << std::endl;
    }
    std::cout << std::endl;
}


// =============================================================================
// FUNÇÃO INTERNA: demonstrarOperadoresBit()
// =============================================================================
static void demonstrarOperadoresBit()
{
    // =========================================================================
    // OPERADORES BITWISE ALTERNATIVOS — bitand / bitor / xor / compl
    // =========================================================================
    // Assim como os lógicos, os operadores bitwise têm tokens alternativos.
    //
    //   Símbolo │ Alternativa │ Operação
    //   --------│-------------|----------------------------------------------
    //   &       │ bitand      │ AND bit a bit — 1 apenas se AMBOS forem 1
    //   |       │ bitor       │ OR  bit a bit — 1 se PELO MENOS UM for 1
    //   ^       │ xor         │ XOR bit a bit — 1 apenas se forem DIFERENTES
    //   ~       │ compl       │ Complemento   — inverte TODOS os bits
    //
    // LITERAIS BINÁRIOS (C++14):
    //   Prefixo 0b ou 0B → número escrito em base 2
    //   0b1010 = 10 em decimal  (bits: 1·8 + 0·4 + 1·2 + 0·1)
    //   0b1100 = 12 em decimal  (bits: 1·8 + 1·4 + 0·2 + 0·1)
    //
    // Onde operadores bitwise são usados na prática:
    //   - Flags de permissão (chmod Linux: rwxrwxrwx)
    //   - Máscaras de bits (setar, limpar, verificar bits específicos)
    //   - Compressão e criptografia
    //   - Protocolos de rede (IPv4, flags TCP)
    // =========================================================================

    std::cout << "--- OPERADORES BITWISE ALTERNATIVOS (bitand / bitor / xor / compl) ---" << std::endl;

    int a = 0b1010;  // 10 em decimal: bits 3 e 1 ligados (0=desligado, 1=ligado)
    int b = 0b1100;  // 12 em decimal: bits 3 e 2 ligados

    std::cout << "a = 0b1010 = " << a << " (decimal)" << std::endl;
    std::cout << "b = 0b1100 = " << b << " (decimal)" << std::endl;
    std::cout << std::endl;

    // & / bitand — AND: resultado 1 apenas onde AMBOS têm 1
    //   1 0 1 0   (a)
    //   1 1 0 0   (b)
    //   -------
    //   1 0 0 0   = 8
    std::cout << "AND  simbolo:  a  & b  = " << (a  & b)       << "  (esperado 8)"  << std::endl;
    std::cout << "AND  alt.   :  a bitand b = " << (a bitand b) << "  (esperado 8)"  << std::endl;
    std::cout << std::endl;

    // | / bitor — OR: resultado 1 onde PELO MENOS UM tem 1
    //   1 0 1 0   (a)
    //   1 1 0 0   (b)
    //   -------
    //   1 1 1 0   = 14
    std::cout << "OR   simbolo:  a  | b  = " << (a  | b)      << "  (esperado 14)" << std::endl;
    std::cout << "OR   alt.   :  a bitor b = " << (a bitor b)  << "  (esperado 14)" << std::endl;
    std::cout << std::endl;

    // ^ / xor — XOR: resultado 1 apenas onde os bits são DIFERENTES
    //   1 0 1 0   (a)
    //   1 1 0 0   (b)
    //   -------
    //   0 1 1 0   = 6
    std::cout << "XOR  simbolo:  a  ^ b  = " << (a  ^ b)    << "  (esperado 6)"  << std::endl;
    std::cout << "XOR  alt.   :  a xor b = " << (a xor b)   << "  (esperado 6)"  << std::endl;
    std::cout << std::endl;

    // ~ / compl — NOT: inverte TODOS os 32 bits do int
    std::cout << "NOT  simbolo:  ~a      = " << (~a)         << "  (complemento de " << a << ")" << std::endl;
    std::cout << "NOT  alt.   :  compl a = " << (compl a)   << "  (complemento de " << a << ")" << std::endl;
    std::cout << std::endl;

    // Exemplo prático: sistema de permissões com flags de bit
    std::cout << "Exemplo: flags de permissao (bitmask)" << std::endl;
    constexpr int LEITURA  = 0b0001;  // bit 0
    constexpr int ESCRITA  = 0b0010;  // bit 1
    constexpr int EXECUCAO = 0b0100;  // bit 2

    int permissoes = LEITURA bitor ESCRITA;  // ativa leitura E escrita
    std::cout << "  Permissoes ativas (leitura + escrita): " << permissoes << std::endl;

    // Verificar se um bit específico está ativo com bitand
    if (permissoes bitand LEITURA)  std::cout << "  Leitura:  permitida" << std::endl;
    if (permissoes bitand ESCRITA)  std::cout << "  Escrita:  permitida" << std::endl;
    if (not (permissoes bitand EXECUCAO))
        std::cout << "  Execucao: negada"    << std::endl;

    std::cout << std::endl;
}


// =============================================================================
// FUNÇÃO INTERNA: demonstrarEstruturas()
// Contexto: gerenciar notas de uma turma
// =============================================================================
static void demonstrarEstruturas()
{
    int notasDaTurma[]             = {92, 45, 78, 60, 88, 33, 71, 55, 95, 62};
    constexpr size_t NUM_ALUNOS    = sizeof(notasDaTurma) / sizeof(notasDaTurma[0]);

    int totalAprovados   = 0;
    int totalReprovados  = 0;
    int maiorNota        = 0;
    int menorNota        = 100;

    std::cout << std::endl;
    std::cout << "=== RELATORIO DA TURMA ===" << std::endl;

    // FOR + IF/ELSE: processar cada nota
    for (size_t i = 0; i < NUM_ALUNOS; ++i) {
        int nota     = notasDaTurma[i];
        std::string conceito;
        std::string resultado;

        // IF/ELSE IF — classificar a nota
        if (nota >= 90) {
            conceito  = "A";
        } else if (nota >= 70) {
            conceito  = "B";
        } else if (nota >= 60) {
            conceito  = "C";
        } else {
            conceito  = "F";
        }

        // OPERADOR TERNÁRIO — aprovado ou reprovado
        resultado = (nota >= 60) ? "Aprovado" : "Reprovado";

        // Atualizar maior e menor nota (sem break/continue aqui — processa tudo)
        if (nota > maiorNota) maiorNota = nota;
        if (nota < menorNota) menorNota = nota;

        // SWITCH — mensagem motivacional baseada no conceito
        std::string motivacao;
        switch (conceito[0]) {
            case 'A': motivacao = "Excelente!";        break;
            case 'B': motivacao = "Muito bom!";        break;
            case 'C': motivacao = "Passou raspando.";  break;
            case 'F': motivacao = "Precisa estudar.";  break;
            default:  motivacao = "?";                 break;
        }

        // CONTINUE — pula a impressão de quem tem nota entre 60-65 (borda)
        if (nota >= 60 && nota < 65) {
            ++totalAprovados;
            continue;  // aprovado, mas não exibe individualmente
        }

        // Contagem
        if (nota >= 60) {
            ++totalAprovados;
        } else {
            ++totalReprovados;
        }

        std::cout << "  Aluno " << (i + 1) << ": nota=" << nota
                  << "  conceito=" << conceito
                  << "  " << resultado
                  << "  — " << motivacao << std::endl;
    }

    // WHILE — exibir linha separadora dinâmica
    std::cout << "  ";
    int tracos = 0;
    while (tracos < 50) {
        std::cout << "-";
        ++tracos;
    }
    std::cout << std::endl;

    // BREAK em busca do primeiro reprovado
    int indPrimReprovado = -1;
    for (size_t i = 0; i < NUM_ALUNOS; ++i) {
        if (notasDaTurma[i] < 60) {
            indPrimReprovado = static_cast<int>(i) + 1;
            break;
        }
    }

    std::cout << "  Total aprovados:        " << totalAprovados               << std::endl;
    std::cout << "  Total reprovados:       " << totalReprovados              << std::endl;
    std::cout << "  Maior nota:             " << maiorNota                    << std::endl;
    std::cout << "  Menor nota:             " << menorNota                    << std::endl;
    std::cout << "  Primeiro reprovado (pos):" << indPrimReprovado            << std::endl;

    // DO-WHILE — exibir resumo pelo menos uma vez
    int tentativa = 0;
    do {
        ++tentativa;
        std::cout << "  Relatorio gerado (tentativa " << tentativa << ")" << std::endl;
    } while (tentativa < 1);  // executa exatamente 1 vez
}
