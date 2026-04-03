// =============================================================================
// AULA 00 - INTRODUCAO: ANATOMIA DE UM PROGRAMA C++
// =============================================================================
//
// Antes de escrever qualquer coisa em C++, você precisa entender as peças
// que aparecem em TODO programa — mesmo no mais simples "Hello, World!".
//
// Tópicos desta aula:
//   1. #include          — importar bibliotecas
//   2. main()            — ponto de entrada do programa
//   3. std::             — namespaces e o prefixo padrão
//   4. std::cout e <<    — escrever no terminal
//   5. std::cin  e >>    — ler entrada do usuário
//   6. std::endl e \n    — quebra de linha
//   7. sizeof()          — tamanho em bytes de um tipo
//   8. std::fixed e
//      std::setprecision — formatar casas decimais
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
    // 1. #include — IMPORTAR BIBLIOTECAS
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
    // REGRA: Se você usar algo e o compilador reclamar "not declared",
    //        provavelmente falta um #include.
    //
    // Diferença de aspas vs colchetes angulares:
    //   #include <iostream>     → biblioteca da instalação do C++ (sistema)
    //   #include "meu_arquivo.h" → arquivo seu, na mesma pasta do projeto
    // =========================================================================

    std::cout << "--- #include ---" << std::endl;
    std::cout << "Este programa usa:" << std::endl;
    std::cout << "  #include <iostream>  -> std::cout, std::cin, std::endl" << std::endl;
    std::cout << "  #include <iomanip>   -> std::setprecision, std::fixed" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 2. main() — O PONTO DE ENTRADA DO PROGRAMA
    // =========================================================================
    // Todo programa C++ precisa de uma função chamada exatamente "main".
    // É o primeiro código que roda quando você executa o programa.
    // O sistema operacional chama main() — você não chama main() manualmente.
    //
    //   int main() {
    //       // seu código aqui
    //       return 0;   ← diz ao sistema operacional que terminou sem erro
    //   }
    //
    // O "int" antes de main significa que ela retorna um número inteiro.
    // Por convenção universal:
    //   return 0;   → tudo correu bem
    //   return 1;   → algo deu errado (qualquer número diferente de 0 = erro)
    //
    // Você pode verificar esse valor no terminal após executar:
    //   ./programa
    //   echo $?     ← imprime o valor retornado por main()
    //
    // Sem main(), o compilador recusa compilar. É obrigatória.
    // =========================================================================

    std::cout << "--- main() ---" << std::endl;
    std::cout << "Voce esta dentro de rodarAula00(), chamada por main()." << std::endl;
    std::cout << "main() e o ponto de entrada — o SO chama ela ao executar o programa." << std::endl;
    std::cout << "return 0 ao final de main() = programa terminou com sucesso." << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 3. std:: — NAMESPACES E O PREFIXO PADRÃO
    // =========================================================================
    // ANALOGIA: imagine que você tem dois colegas chamados "João" em salas
    // diferentes. Para não confundir, você fala "João da sala A" ou "João da B".
    // Namespace é exatamente isso — um sobrenome para evitar conflito de nomes.
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
    // 4. std::cout E << — ESCREVER NO TERMINAL
    // =========================================================================
    // std::cout é o "canal de saída" do programa — tudo que você manda para
    // ele aparece no terminal.
    //
    // "cout" = Character OUTput
    //
    // O operador << (inserção) empurra dados para dentro do cout.
    // ANALOGIA: pense no << como uma esteira: você coloca itens na esteira
    // e eles chegam ao terminal.
    //
    //   std::cout << "texto";          → imprime texto
    //   std::cout << 42;               → imprime número
    //   std::cout << variavel;         → imprime valor da variável
    //   std::cout << "a=" << a << "b=" << b;  → encadeia múltiplos itens
    //
    // O << pode ser encadeado indefinidamente na mesma linha.
    // =========================================================================

    std::cout << "--- std::cout e << ---" << std::endl;

    int    idade  = 22;
    double altura = 1.75;
    std::cout << "Texto simples" << std::endl;
    std::cout << "Numero: " << 42 << std::endl;
    std::cout << "Variavel idade: " << idade << std::endl;
    std::cout << "Encadeado: idade=" << idade << "  altura=" << altura << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 5. std::cin E >> — LER ENTRADA DO USUÁRIO
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
    int entrada;
    std::cin >> entrada;
    std::cout << "Voce digitou: " << entrada << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 6. std::endl E \n — QUEBRA DE LINHA
    // =========================================================================
    // Ambos quebram a linha — mas são diferentes:
    //
    //   std::endl  → quebra de linha + esvazia o buffer de saída (flush)
    //   "\n"       → só quebra de linha (mais rápido, sem flush)
    //
    // O que é "flush do buffer"?
    //   O terminal não imprime cada caractere imediatamente — ele acumula
    //   em um buffer e imprime de uma vez (mais eficiente).
    //   flush força a impressão imediata do que está acumulado.
    //
    // Quando usar cada um:
    //   std::endl → quando você precisa garantir que o texto apareceu antes
    //               de uma operação lenta (leitura de arquivo, rede, etc.)
    //   "\n"      → no geral, é suficiente e mais rápido
    //
    // Na prática para iniciante: use std::endl. A diferença de performance
    // só importa em programas que imprimem milhões de linhas.
    // =========================================================================

    std::cout << "--- std::endl vs \\n ---" << std::endl;
    std::cout << "Linha 1 com std::endl" << std::endl;
    std::cout << "Linha 2 com \\n\n";
    std::cout << "Linha 3 — ambos chegam ao mesmo resultado visual" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 7. sizeof() — TAMANHO EM BYTES DE UM TIPO OU VARIÁVEL
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
    //   int x = 42;
    //   sizeof(x)   → mesmo que sizeof(int) = 4
    //
    // Por que isso importa?
    //   - Entender quanto espaço cada tipo usa na memória
    //   - Pode variar entre sistemas (32-bit vs 64-bit, Windows vs Linux)
    //   - Por isso existem int32_t, int64_t — garantia de tamanho fixo (Aula 03)
    // =========================================================================

    std::cout << "--- sizeof() ---" << std::endl;
    std::cout << "sizeof(char)    = " << sizeof(char)    << " byte(s)  | 1 caractere"   << std::endl;
    std::cout << "sizeof(bool)    = " << sizeof(bool)    << " byte(s)  | true ou false" << std::endl;
    std::cout << "sizeof(int)     = " << sizeof(int)     << " byte(s)  | inteiro"        << std::endl;
    std::cout << "sizeof(float)   = " << sizeof(float)   << " byte(s)  | decimal simples" << std::endl;
    std::cout << "sizeof(double)  = " << sizeof(double)  << " byte(s)  | decimal duplo"  << std::endl;
    std::cout << "sizeof(long)    = " << sizeof(long)    << " byte(s)  | inteiro longo"  << std::endl;

    int x = 99;
    std::cout << "sizeof(x) onde x e int = " << sizeof(x) << " byte(s) (mesmo que sizeof(int))" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 8. std::fixed E std::setprecision() — FORMATAR CASAS DECIMAIS
    // =========================================================================
    // Por padrão, std::cout decide sozinho quantas casas decimais mostrar.
    // Para controlar exatamente a aparência de números com vírgula, usamos:
    //
    //   std::fixed
    //     → ativa o modo de ponto fixo: sempre mostra o número de casas
    //       definido por setprecision, mesmo que sejam zeros.
    //       Sem ele, setprecision conta dígitos significativos totais.
    //
    //   std::setprecision(N)
    //     → define N casas decimais após a vírgula (quando usado com fixed)
    //     → requer #include <iomanip>
    //
    // Ambos são "manipuladores de stream": uma vez ativados, afetam TODOS
    // os próximos valores impressos com std::cout, até você mudar.
    //
    // EXEMPLOS:
    //   double pi = 3.14159265;
    //   std::cout << pi;                              → "3.14159"  (padrão)
    //   std::cout << std::fixed << std::setprecision(2) << pi;  → "3.14"
    //   std::cout << std::fixed << std::setprecision(4) << pi;  → "3.1416"
    // =========================================================================

    double pi      = 3.14159265358979;
    double preco   = 29.9;
    double ciencia = 0.000123456;

    std::cout << "--- std::fixed e std::setprecision() ---" << std::endl;
    std::cout << "Valor de pi = " << pi << "  (padrao do cout)" << std::endl;

    std::cout << std::fixed;   // ativa ponto fixo para todos os proximos doubles

    std::cout << std::setprecision(0) << "setprecision(0): " << pi    << std::endl;
    std::cout << std::setprecision(2) << "setprecision(2): " << pi    << "  (2 casas — ideal para dinheiro)" << std::endl;
    std::cout << std::setprecision(4) << "setprecision(4): " << pi    << std::endl;
    std::cout << std::setprecision(8) << "setprecision(8): " << pi    << std::endl;

    std::cout << std::setprecision(2) << "Preco R$ " << preco   << "  (29.9 vira 29.90)" << std::endl;
    std::cout << std::setprecision(6) << "Ciencia:  " << ciencia << std::endl;

    std::cout << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "  FIM DA AULA 00 — base pronta para C++!    " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;
}
