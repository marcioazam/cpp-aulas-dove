// =============================================================================
// AULA 00 - INTRODUCAO: ANATOMIA DE UM PROGRAMA C++
// =============================================================================
//
// Antes de escrever qualquer coisa em C++, você precisa entender as peças
// que aparecem em TODO programa — mesmo no mais simples "Hello, World!".
//
// Tópicos desta aula:
//   1. O que é compilação      — código → compilador → executável
//   2. Comentários             — // e /* */
//   3. Ponto e vírgula e {}    — sintaxe base da linguagem
//   4. #include                — importar bibliotecas
//   5. main()                  — ponto de entrada do programa
//   6. Variáveis               — declaração, inicialização, atribuição
//   7. std::                   — namespaces e o prefixo padrão
//   8. std::cout e <<          — escrever no terminal
//   9. std::cin  e >>          — ler entrada do usuário
//  10. std::endl e \n          — quebra de linha
//  11. sizeof()                — tamanho em bytes de um tipo
//  12. std::fixed e
//      std::setprecision       — formatar casas decimais
//  13. Erros: compilação vs execução
//
// =============================================================================

#include "aula00_intro.h"
#include <iostream>   // std::cout, std::cin, std::endl
#include <iomanip>    // std::setprecision, std::fixed

// =============================================================================
// PONTO DE ENTRADA DA AULA 00
// =============================================================================
void rodarAula00()
{
    std::cout << "=============================================" << std::endl;
    std::cout << "   AULA 00 - ANATOMIA DE UM PROGRAMA C++    " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;


    // =========================================================================
    // 1. O QUE É COMPILAÇÃO
    // =========================================================================
    // O computador NÃO entende C++. Ele só entende zeros e uns (linguagem de
    // máquina). Então, para rodar um programa C++, é necessário um passo
    // intermediário: a COMPILAÇÃO.
    //
    // O fluxo completo é:
    //
    //   [1] Você escreve o código em C++ (.cpp)
    //         ↓
    //   [2] O COMPILADOR (g++, clang++) lê o código e verifica se está correto
    //         ↓
    //   [3] Se estiver correto, gera um EXECUTÁVEL (ex: build/cppsmoke)
    //         ↓
    //   [4] O sistema operacional EXECUTA o binário
    //
    // ANALOGIA: é como uma receita escrita em português.
    //   - O papel com a receita = seu arquivo .cpp
    //   - O tradutor           = o compilador
    //   - O prato pronto       = o executável
    //   - Comer o prato        = executar o programa
    //
    // CONSEQUÊNCIA IMPORTANTE:
    //   Toda vez que você mudar o código, precisa compilar de novo.
    //   O executável antigo ainda existe, mas reflete o código anterior.
    //
    // No terminal:
    //   cmake --build build   ← compila
    //   ./build/cppsmoke      ← executa
    // =========================================================================

    std::cout << "--- O QUE E COMPILACAO ---" << std::endl;
    std::cout << "Este texto aparece porque o codigo foi compilado e executado." << std::endl;
    std::cout << "Fluxo: .cpp -> compilador -> executavel -> SO executa" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 2. COMENTÁRIOS — // e /* */
    // =========================================================================
    // Comentários são texto ignorado pelo compilador.
    // Servem para explicar o código para humanos — inclusive para você mesmo
    // quando reler o código semanas depois.
    //
    // Dois tipos:
    //
    //   // Comentário de linha — ignora tudo até o fim da linha
    //
    //   /* Comentário de bloco
    //      pode ocupar várias linhas
    //      termina aqui: */
    //
    // O compilador descarta os comentários ANTES de processar o código.
    // Eles não afetam performance, tamanho do executável, nem comportamento.
    //
    // BOA PRÁTICA:
    //   - Comente o PORQUÊ, não o O QUÊ.
    //   - Ruim:  x = x + 1;  // soma 1 a x   ← óbvio demais
    //   - Bom:   x = x + 1;  // compensa o índice base-0 do array
    // =========================================================================

    // Isto é um comentário de linha — o compilador ignora este texto
    /* Isto é um comentário de bloco.
       Pode ocupar várias linhas. */

    std::cout << "--- COMENTARIOS ---" << std::endl;
    std::cout << "Comentarios nao aparecem no terminal — so existem no codigo." << std::endl;
    std::cout << "Use // para linha unica, /* */ para multiplas linhas." << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 3. PONTO E VÍRGULA `;` E BLOCOS `{}`
    // =========================================================================
    // C++ não usa indentação para definir onde um comando termina (diferente
    // de Python). Em vez disso, usa dois marcadores sintáticos:
    //
    // PONTO E VÍRGULA `;`
    //   Marca o FIM de um statement (instrução).
    //   Cada instrução completa precisa terminar com `;`.
    //   Esquecer o `;` é um dos erros mais comuns de iniciantes.
    //
    //   int x = 10;        ← statement completo
    //   std::cout << x;    ← statement completo
    //
    // CHAVES `{}`
    //   Definem um BLOCO — um grupo de statements que pertencem juntos.
    //   Usadas em: funções, if/else, for, while, etc.
    //
    //   void minhaFuncao() {   ← abre o bloco da função
    //       int x = 10;        ← pertence ao bloco
    //       std::cout << x;    ← pertence ao bloco
    //   }                      ← fecha o bloco
    //
    // INDENTAÇÃO (espaços/tabs antes do código)
    //   Não é obrigatória em C++, mas é ESSENCIAL para legibilidade.
    //   Use 4 espaços (ou 1 tab) por nível de bloco.
    //   Código sem indentação funciona, mas ninguém consegue ler.
    // =========================================================================

    std::cout << "--- PONTO E VIRGULA E BLOCOS {} ---" << std::endl;
    std::cout << "Cada instrucao termina com ; (ponto e virgula)." << std::endl;
    std::cout << "Blocos {} agrupam instrucoes que pertencem juntas." << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 4. #include — IMPORTAR BIBLIOTECAS
    // =========================================================================
    // ANALOGIA: #include é como "ligar uma tomada". Você não precisa construir
    // a eletricidade do zero — só conecta ao que já existe.
    //
    // C++ vem com uma biblioteca padrão enorme. Para usar qualquer parte dela,
    // você precisa "incluir" o cabeçalho correspondente no topo do arquivo.
    //
    //   #include <iostream>   → habilita std::cout, std::cin, std::endl
    //   #include <iomanip>    → habilita std::setprecision, std::fixed
    //   #include <string>     → habilita std::string
    //   #include <vector>     → habilita std::vector
    //   #include <cmath>      → habilita std::sqrt, std::pow, etc.
    //
    // REGRA: Se o compilador reclamar "not declared in this scope",
    //        provavelmente falta um #include.
    //
    // Diferença de aspas vs colchetes angulares:
    //   #include <iostream>      → biblioteca do sistema (instalação do C++)
    //   #include "aula00_intro.h" → arquivo seu, na pasta do projeto
    // =========================================================================

    std::cout << "--- #include ---" << std::endl;
    std::cout << "Este programa usa:" << std::endl;
    std::cout << "  #include <iostream>  -> std::cout, std::cin, std::endl" << std::endl;
    std::cout << "  #include <iomanip>   -> std::setprecision, std::fixed" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 5. main() — O PONTO DE ENTRADA DO PROGRAMA
    // =========================================================================
    // Todo programa C++ precisa de uma função chamada exatamente "main".
    // É o primeiro código que roda quando você executa o programa.
    // O sistema operacional chama main() — você não chama main() manualmente.
    //
    //   int main() {
    //       // seu código aqui
    //       return 0;   ← diz ao SO que terminou sem erro
    //   }
    //
    // O "int" antes de main significa que ela retorna um número inteiro.
    // Por convenção universal:
    //   return 0;   → tudo correu bem
    //   return 1;   → algo deu errado (qualquer número ≠ 0 = erro)
    //
    // Você pode verificar esse valor no terminal após executar:
    //   ./build/cppsmoke
    //   echo $?     ← imprime o valor retornado por main()
    //
    // Sem main(), o compilador recusa compilar. É obrigatória.
    // =========================================================================

    std::cout << "--- main() ---" << std::endl;
    std::cout << "main() e o ponto de entrada — o SO chama ela ao executar." << std::endl;
    std::cout << "return 0 ao final de main() = programa terminou com sucesso." << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 6. VARIÁVEIS — DECLARAÇÃO, INICIALIZAÇÃO E ATRIBUIÇÃO
    // =========================================================================
    // ANALOGIA: uma variável é uma CAIXA com dois atributos:
    //   - Um TIPO  (o tamanho e formato da caixa: int, double, etc.)
    //   - Um NOME  (a etiqueta colada na caixa)
    //
    // Dentro da caixa fica o VALOR.
    //
    // DECLARAÇÃO — criar a caixa (sem valor inicial):
    //   int idade;          ← existe, mas valor é indefinido (lixo de memória)
    //
    // INICIALIZAÇÃO — criar a caixa e colocar um valor já na criação:
    //   int idade = 20;     ← caixa criada com 20 dentro
    //   int idade{20};      ← sintaxe moderna equivalente (C++11)
    //
    // ATRIBUIÇÃO — trocar o valor de uma caixa que já existe:
    //   idade = 21;         ← sem o tipo! já existe, só muda o valor
    //
    // REGRAS DE NOMENCLATURA:
    //   - Pode usar letras, números e underscore (_)
    //   - Não pode começar com número
    //   - Maiúsculas e minúsculas são diferentes: "Idade" ≠ "idade"
    //   - Use nomes descritivos: "notaFinal" é melhor que "nf" ou "x"
    //
    // BOAS PRÁTICAS:
    //   - SEMPRE inicialize variáveis. Variáveis sem valor = comportamento
    //     imprevisível (o valor é o que estava na memória antes).
    //   - Use camelCase para variáveis: notaFinal, totalItens, nomeAluno
    // =========================================================================

    std::cout << "--- VARIAVEIS ---" << std::endl;

    int    idadeAluno  = 20;       // inteiro inicializado
    double notaFinal   = 9.5;      // decimal inicializado
    char   inicial     = 'M';      // um único caractere
    bool   aprovado    = true;     // verdadeiro ou falso

    std::cout << "int    idadeAluno  = " << idadeAluno  << std::endl;
    std::cout << "double notaFinal   = " << notaFinal   << std::endl;
    std::cout << "char   inicial     = " << inicial     << std::endl;
    std::cout << "bool   aprovado    = " << std::boolalpha << aprovado << std::endl;

    // Atribuição: trocar o valor de uma variável existente
    idadeAluno = 21;   // sem "int" — a variável já existe
    std::cout << "Apos idadeAluno = 21: " << idadeAluno << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 7. std:: — NAMESPACES E O PREFIXO PADRÃO
    // =========================================================================
    // ANALOGIA: dois colegas chamados "João" em salas diferentes.
    // Para não confundir, você fala "João da Sala A" ou "João da Sala B".
    // Namespace é o sobrenome que evita conflito de nomes.
    //
    // "std" é o namespace da biblioteca padrão do C++ (STandard).
    // Tudo que vem da biblioteca padrão mora dentro de "std::".
    //
    //   std::cout   → o "cout" que mora no namespace "std"
    //   std::cin    → o "cin" que mora no namespace "std"
    //   std::string → o "string" que mora no namespace "std"
    //
    // Você pode ver código assim em outros lugares:
    //   using namespace std;   ← permite escrever "cout" sem o "std::"
    //
    // Por que NÃO usamos "using namespace std" nestas aulas?
    //   - Em projetos maiores, pode gerar conflitos de nomes silenciosos.
    //   - Escrever "std::" deixa claro de onde vem cada símbolo.
    //   - É a prática recomendada em código profissional.
    // =========================================================================

    std::cout << "--- std:: (namespace) ---" << std::endl;
    std::cout << "std::cout  = cout do namespace 'std' (biblioteca padrao)" << std::endl;
    std::cout << "std::cin   = cin  do namespace 'std'" << std::endl;
    std::cout << "std::endl  = endl do namespace 'std'" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 8. std::cout E << — ESCREVER NO TERMINAL
    // =========================================================================
    // std::cout é o "canal de saída" do programa — tudo que você manda para
    // ele aparece no terminal.
    //
    // "cout" = Character OUTput
    //
    // O operador << (inserção) empurra dados para dentro do cout.
    // ANALOGIA: pense no << como uma esteira — você coloca itens na esteira
    // e eles chegam ao terminal.
    //
    //   std::cout << "texto";          → imprime texto
    //   std::cout << 42;               → imprime número
    //   std::cout << variavel;         → imprime valor da variável
    //   std::cout << "a=" << a << " b=" << b;  → encadeia múltiplos itens
    //
    // O << pode ser encadeado indefinidamente na mesma linha.
    // =========================================================================

    std::cout << "--- std::cout e << ---" << std::endl;
    std::cout << "Texto simples" << std::endl;
    std::cout << "Numero: " << 42 << std::endl;
    std::cout << "Variavel idadeAluno: " << idadeAluno << std::endl;
    std::cout << "Encadeado: idade=" << idadeAluno << "  nota=" << notaFinal << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 9. std::cin E >> — LER ENTRADA DO USUÁRIO
    // =========================================================================
    // std::cin é o "canal de entrada" — lê o que o usuário digita no terminal.
    //
    // "cin" = Character INput
    //
    // O operador >> (extração) puxa dados do cin para dentro de uma variável.
    // É o inverso do <<: em vez de mandar para o terminal, traz do terminal.
    //
    //   int x;
    //   std::cin >> x;   → espera o usuário digitar um número e pressionar Enter
    //
    // Encadeamento também funciona:
    //   std::cin >> nome >> idade;   → lê dois valores separados por espaço/Enter
    //
    // ATENÇÃO: std::cin >> para no primeiro espaço.
    //   Para ler uma linha inteira (com espaços): use std::getline(std::cin, variavel)
    // =========================================================================

    std::cout << "--- std::cin e >> ---" << std::endl;
    std::cout << "Digite um numero inteiro: ";
    int entradaUsuario;
    std::cin >> entradaUsuario;
    std::cout << "Voce digitou: " << entradaUsuario << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 10. std::endl E \n — QUEBRA DE LINHA
    // =========================================================================
    // Ambos quebram a linha — mas são diferentes:
    //
    //   std::endl  → quebra de linha + esvazia o buffer de saída (flush)
    //   "\n"       → só quebra de linha (mais rápido, sem flush)
    //
    // O que é "flush do buffer"?
    //   O terminal não imprime cada caractere imediatamente — acumula em um
    //   buffer e imprime de uma vez (mais eficiente).
    //   flush força a impressão imediata do que está acumulado.
    //
    // Quando usar cada um:
    //   std::endl → quando precisa garantir que o texto apareceu antes
    //               de uma operação lenta (arquivo, rede, etc.)
    //   "\n"      → no geral, é suficiente e mais rápido
    //
    // Na prática para iniciante: use std::endl. A diferença de performance
    // só importa em programas que imprimem milhões de linhas.
    // =========================================================================

    std::cout << "--- std::endl vs \\n ---" << std::endl;
    std::cout << "Linha 1 com std::endl" << std::endl;
    std::cout << "Linha 2 com \\n\n";
    std::cout << "Linha 3 — resultado visual identico" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 11. sizeof() — TAMANHO EM BYTES DE UM TIPO OU VARIÁVEL
    // =========================================================================
    // sizeof() retorna quantos bytes aquele tipo ocupa na memória.
    // Não é uma função normal — é um operador especial avaliado em compilação.
    //
    //   sizeof(int)     → normalmente 4 bytes (32 bits)
    //   sizeof(double)  → normalmente 8 bytes (64 bits)
    //   sizeof(char)    → sempre 1 byte (garantido pelo padrão C++)
    //   sizeof(bool)    → normalmente 1 byte
    //
    // Também funciona com variáveis:
    //   sizeof(idadeAluno)   → mesmo que sizeof(int) = 4
    //
    // Por que isso importa?
    //   - Entender quanto espaço cada tipo usa na memória
    //   - Pode variar entre sistemas (32-bit vs 64-bit, Windows vs Linux)
    //   - Por isso existem int32_t, int64_t — garantia de tamanho fixo (Aula 03)
    // =========================================================================

    std::cout << "--- sizeof() ---" << std::endl;
    std::cout << "sizeof(char)    = " << sizeof(char)    << " byte(s)  | 1 caractere"    << std::endl;
    std::cout << "sizeof(bool)    = " << sizeof(bool)    << " byte(s)  | true ou false"  << std::endl;
    std::cout << "sizeof(int)     = " << sizeof(int)     << " byte(s)  | inteiro"         << std::endl;
    std::cout << "sizeof(float)   = " << sizeof(float)   << " byte(s)  | decimal simples" << std::endl;
    std::cout << "sizeof(double)  = " << sizeof(double)  << " byte(s)  | decimal duplo"   << std::endl;
    std::cout << "sizeof(long)    = " << sizeof(long)    << " byte(s)  | inteiro longo"   << std::endl;
    std::cout << "sizeof(idadeAluno) = " << sizeof(idadeAluno) << " byte(s)  (mesmo que sizeof(int))" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 12. std::fixed E std::setprecision() — FORMATAR CASAS DECIMAIS
    // =========================================================================
    // Por padrão, std::cout decide sozinho quantas casas decimais mostrar.
    // Para controlar a aparência de números com vírgula, usamos:
    //
    //   std::fixed
    //     → ativa modo de ponto fixo: sempre mostra exatamente N casas decimais,
    //       incluindo zeros. Sem ele, setprecision conta dígitos significativos totais.
    //
    //   std::setprecision(N)
    //     → define N casas decimais após a vírgula (quando usado com fixed)
    //     → requer #include <iomanip>
    //
    // ATENÇÃO: são "manipuladores de stream" — uma vez ativados, afetam TODOS
    // os próximos valores impressos com std::cout, até você mudar novamente.
    // =========================================================================

    double pi    = 3.14159265358979;
    double preco = 29.9;

    std::cout << "--- std::fixed e std::setprecision() ---" << std::endl;
    std::cout << "pi sem formatacao:  " << pi << "  (padrao do cout)" << std::endl;

    std::cout << std::fixed;   // ativa ponto fixo para todos os proximos doubles

    std::cout << std::setprecision(0) << "setprecision(0): " << pi << std::endl;
    std::cout << std::setprecision(2) << "setprecision(2): " << pi << "  (ideal para dinheiro)" << std::endl;
    std::cout << std::setprecision(4) << "setprecision(4): " << pi << std::endl;
    std::cout << std::setprecision(8) << "setprecision(8): " << pi << std::endl;
    std::cout << std::setprecision(2) << "Preco R$ " << preco << "  (29.9 vira 29.90)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 13. ERROS DE COMPILAÇÃO vs ERROS DE EXECUÇÃO
    // =========================================================================
    // São categorias COMPLETAMENTE diferentes. Confundi-las é muito comum.
    //
    // ERRO DE COMPILAÇÃO (compile-time error)
    //   Acontece quando você tenta compilar um código com erros de sintaxe
    //   ou uso inválido da linguagem. O compilador recusa gerar o executável.
    //   O programa NUNCA chega a rodar.
    //
    //   Exemplos:
    //     int x = "texto";    ← tipo errado: int não pode receber string
    //     std::cout << x      ← faltou o ponto e vírgula ;
    //     rodarAulaNove();    ← função que não existe
    //
    //   Como identificar: o terminal mostra "error:" com o arquivo e linha.
    //   Como resolver: leia a mensagem, vá até a linha indicada e corrija.
    //
    // ERRO DE EXECUÇÃO (runtime error)
    //   O código compilou com sucesso, mas algo deu errado DURANTE a execução.
    //   O programa começa a rodar e trava ou produz resultado errado.
    //
    //   Exemplos:
    //     int* p = nullptr; *p = 5;   ← segfault: acesso a memória inválida
    //     int x = 1 / 0;              ← divisão por zero
    //     arr[100] em array de 3      ← acesso fora dos limites
    //
    //   Como identificar: programa roda mas trava, produz valor errado,
    //   ou exibe "Segmentation fault (core dumped)".
    //   Como resolver: use o debugger (F5 no VS Code) para inspecionar.
    //
    // ERRO DE LÓGICA (logic error)
    //   O código compila e roda sem travar, mas o resultado está errado.
    //   É o mais difícil de encontrar — nenhuma ferramenta aponta a linha.
    //
    //   Exemplo: calcular média somando sem dividir pelo total.
    //
    //   Como resolver: debugger, impressões intermediárias, testes unitários.
    // =========================================================================

    std::cout << "--- TIPOS DE ERRO ---" << std::endl;
    std::cout << "Compilacao: codigo invalido — compilador recusa, nada roda."  << std::endl;
    std::cout << "Execucao:   compilou, mas travou durante o programa."         << std::endl;
    std::cout << "Logica:     rodou sem travar, mas resultado esta errado."     << std::endl;
    std::cout << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "  FIM DA AULA 00 — base pronta para C++!    " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;
}
