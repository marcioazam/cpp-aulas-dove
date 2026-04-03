// =============================================================================
// AULA 03 - TIPOS MODERNOS C++11 / C++17 / C++20
// =============================================================================
//
// C++11 foi uma revolução na linguagem. Antes dele, C++ era verboso e
// propenso a erros em coisas simples. Os tipos e palavras-chave modernos
// tornam o código mais seguro, mais legível e mais expressivo.
//
// Tópicos desta aula:
//   1. auto       — dedução automática de tipo
//   2. decltype   — tipo de uma expressão em compilação
//   3. int32_t / uint64_t — inteiros de tamanho fixo (<cstdint>)
//   4. size_t     — tipo correto para tamanhos e índices
//   5. std::string vs char[]
//   6. std::optional<T> (C++17) — valor que pode não existir
//   7. constexpr  — constante avaliada em tempo de compilação (C++11)
//
//   Nota: nullptr foi coberto na Aula 02 (Ponteiros), onde se encaixa melhor.
//
// =============================================================================

#include "aula03_tipos_modernos.h"
#include <iostream>
#include <iomanip>
#include <string>       // std::string
#include <cstdint>      // int32_t, uint64_t, int8_t, etc.
#include <optional>     // std::optional (C++17)

static void demonstrarTodosTiposModernos();

// =============================================================================
// PONTO DE ENTRADA DA AULA 03
// =============================================================================
void rodarAula03()
{
    std::cout << "=============================================" << std::endl;
    std::cout << "   AULA 03 - TIPOS MODERNOS C++11/17/20     " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;


    // =========================================================================
    // 1. AUTO (C++11)
    // =========================================================================
    // auto pede ao COMPILADOR que deduza o tipo automaticamente.
    // O tipo é decidido em TEMPO DE COMPILAÇÃO, não em execução.
    // Não é um tipo dinâmico — é 100% tipado e seguro.
    //
    // REGRA DE OURO: o compilador deduz o tipo a partir do valor do lado direito.
    //   auto x = 42;        → compilador vê 42 (int literal)   → x é int
    //   auto x = 42.0;      → compilador vê 42.0 (double)       → x é double
    //   auto x = 42.0f;     → compilador vê 42.0f (float)       → x é float
    //   auto x = 42LL;      → compilador vê 42LL (long long)    → x é long long
    //
    // Quando usar:
    //   - Quando o tipo é óbvio pelo valor da inicialização
    //   - Tipos longos e verbosos (veremos com containers mais à frente)
    //
    // Quando NÃO usar:
    //   - Quando o tipo não é óbvio — prefira ser explícito para quem lê
    //   - Parâmetros de função (não é permitido sem templates)
    // =========================================================================

    auto numero     = 42;               // int     — literal inteiro = int
    auto decimal    = 3.14;             // double  — literal double = double
    auto decimalF   = 3.14f;            // float   — sufixo 'f' = float
    auto grande     = 9000000000LL;     // long long — sufixo 'LL'
    auto letra      = 'Z';              // char    — literal char = char
    auto texto      = std::string("Ola C++"); // std::string
    auto verdadeiro = true;             // bool

    // auto também deduz o tipo de expressões:
    auto somaReal = 10 + 3.14;          // int + double → double (promoção automática)
    auto produto  = 5 * 2;              // int * int   → int

    std::cout << "--- AUTO (C++11) ---" << std::endl;
    std::cout << "auto numero     = " << numero     << "  (int)"       << std::endl;
    std::cout << "auto decimal    = " << decimal    << "  (double)"    << std::endl;
    std::cout << "auto decimalF   = " << decimalF   << "f (float)"     << std::endl;
    std::cout << "auto grande     = " << grande     << " (long long)"  << std::endl;
    std::cout << "auto letra      = " << letra      << "  (char)"      << std::endl;
    std::cout << "auto texto      = " << texto      << "  (std::string)" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "auto verdadeiro = " << verdadeiro << "  (bool)"      << std::endl;
    std::cout << "auto somaReal   = " << somaReal   << "  (double — int+double promove)" << std::endl;
    std::cout << "auto produto    = " << produto    << "  (int)"       << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 2. DECLTYPE (C++11)
    // =========================================================================
    // ANALOGIA: é como perguntar ao compilador "qual é o tipo disso?"
    //   e usar a resposta para declarar outra variável.
    //
    // Imagine que você tem:
    //   int x = 10;
    //
    // Em vez de escrever "int" de novo, você faz:
    //   decltype(x) y = 20;   ← o compilador olha para x, vê que é int,
    //                            e declara y como int também.
    //
    // DIFERENÇA entre auto e decltype:
    //   auto y = x;           → y recebe o VALOR de x (y = 10)
    //   decltype(x) y = 20;   → y recebe o TIPO de x, mas com o valor que você escolher (y = 20)
    //
    //   auto    = "copie o valor e deduza o tipo"
    //   decltype = "use o tipo desta expressão, mas o valor eu defino"
    //
    // QUANDO VOCÊ VAI USAR NA PRÁTICA:
    //   - Garantir que duas variáveis têm exatamente o mesmo tipo
    //   - Em templates avançados (não se preocupe agora — virá mais à frente)
    // =========================================================================

    int    baseInt    = 10;
    double baseDouble = 3.14;

    decltype(baseInt)             copia            = 99;   // int  — mesmo tipo de baseInt
    decltype(baseInt + baseDouble) resultado        = 5.5;  // double — tipo da expressão
    decltype(baseInt)             contadorAuxiliar = 0;    // int  — garante mesmo tipo

    std::cout << "--- DECLTYPE (C++11) ---" << std::endl;
    std::cout << "baseInt    = " << baseInt    << "  (int)"    << std::endl;
    std::cout << "baseDouble = " << baseDouble << "  (double)" << std::endl;
    std::cout << "decltype(baseInt) copia = " << copia     << "  (int)"    << std::endl;
    std::cout << "decltype(int+double) resultado = " << resultado << "  (double)" << std::endl;
    std::cout << "decltype(baseInt) contadorAuxiliar = " << contadorAuxiliar << std::endl;
    std::cout << "sizeof( decltype(int+double) ) = "
              << sizeof(decltype(baseInt + baseDouble)) << " bytes (double)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 3. INTEIROS DE TAMANHO FIXO — int32_t, uint64_t, etc. (<cstdint>)
    // =========================================================================
    // O PROBLEMA com int/long:
    //   - int tem 4 bytes na maioria das plataformas, mas não é garantido.
    //   - long tem 4 bytes no Windows e 8 bytes no Linux — ambíguo!
    //
    // SOLUÇÃO: tipos de tamanho fixo do cabeçalho <cstdint>
    //   int8_t    → exatamente  8 bits (1 byte),  -128 a 127
    //   int16_t   → exatamente 16 bits (2 bytes), -32768 a 32767
    //   int32_t   → exatamente 32 bits (4 bytes), -2bi a 2bi
    //   int64_t   → exatamente 64 bits (8 bytes), -9.2qi a 9.2qi
    //   uint8_t   → unsigned  8 bits, 0 a 255
    //   uint16_t  → unsigned 16 bits, 0 a 65535
    //   uint32_t  → unsigned 32 bits, 0 a 4.29bi
    //   uint64_t  → unsigned 64 bits, 0 a 18.4qi
    //
    // Quando usar:
    //   - Protocolos de rede e arquivos binários (tamanho DEVE ser exato)
    //   - Compatibilidade cross-platform garantida
    //   - Comunicação com hardware, drivers, sistemas embarcados
    // =========================================================================

    int8_t   byteComSinal  = -100;          // 1 byte  com sinal
    uint8_t  byteSemSinal  = 200;           // 1 byte  sem sinal (ex: valor de pixel RGB)
    int16_t  inteiro16     = -30000;        // 2 bytes com sinal
    uint16_t inteiro16u    = 60000;         // 2 bytes sem sinal (ex: porta de rede)
    int32_t  inteiro32     = -2000000000;   // 4 bytes com sinal (=int garantido)
    uint32_t inteiro32u    = 4000000000U;   // 4 bytes sem sinal
    int64_t  inteiro64     = -9000000000000000000LL; // 8 bytes (=long long)
    uint64_t inteiro64u    = 18000000000000000000ULL; // 8 bytes sem sinal

    std::cout << "--- INTEIROS DE TAMANHO FIXO <cstdint> ---" << std::endl;
    std::cout << "int8_t   (-100):   " << static_cast<int>(byteComSinal)
              << " | " << sizeof(int8_t)   << " byte(s)" << std::endl;
    std::cout << "uint8_t  (200):    " << static_cast<int>(byteSemSinal)
              << " | " << sizeof(uint8_t)  << " byte(s)" << std::endl;
    std::cout << "int16_t  (-30000): " << inteiro16
              << " | " << sizeof(int16_t)  << " byte(s)" << std::endl;
    std::cout << "uint16_t (60000):  " << inteiro16u
              << " | " << sizeof(uint16_t) << " byte(s)" << std::endl;
    std::cout << "int32_t  (-2bi):   " << inteiro32
              << " | " << sizeof(int32_t)  << " byte(s)" << std::endl;
    std::cout << "uint32_t (4bi):    " << inteiro32u
              << " | " << sizeof(uint32_t) << " byte(s)" << std::endl;
    std::cout << "int64_t  (-9qi):   " << inteiro64
              << " | " << sizeof(int64_t)  << " byte(s)" << std::endl;
    std::cout << "uint64_t (18qi):   " << inteiro64u
              << " | " << sizeof(uint64_t) << " byte(s)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 4. SIZE_T — O TIPO CORRETO PARA TAMANHOS E ÍNDICES
    // =========================================================================
    // size_t é um tipo sem sinal definido pelo sistema operacional.
    //   - Em sistemas 32-bit: equivale a uint32_t (0 a 4.29bi)
    //   - Em sistemas 64-bit: equivale a uint64_t (0 a 18.4qi)
    //
    // Quando usar:
    //   - Índices de arrays (evita o warning "signed/unsigned mismatch")
    //   - Resultados de sizeof() e de .size() em strings e containers
    //   - Tamanho de objetos e buffers
    //
    // Por que não usar int para índice?
    //   sizeof() e .size() retornam size_t.
    //   Comparar int com size_t gera warning de compilação — e pode ter bug
    //   em sistemas 64-bit onde size_t supera o limite de int.
    // =========================================================================

    int nums[] = {100, 200, 300, 400, 500};
    std::string exemplo = "Aprendendo C++ moderno";

    size_t tamArray  = sizeof(nums) / sizeof(nums[0]);  // 5 elementos
    size_t tamString = exemplo.size();                  // quantidade de caracteres
    size_t indice    = 2;                               // índice correto para array

    std::cout << "--- SIZE_T ---" << std::endl;
    std::cout << "Array nums[5]: tamanho (size_t) = " << tamArray << std::endl;
    std::cout << "String exemplo: tamanho (size_t) = " << tamString << " caracteres" << std::endl;
    std::cout << "Acesso nums[" << indice << "] = " << nums[indice]
              << "  (indice size_t, sem warning)" << std::endl;
    std::cout << "sizeof(size_t) = " << sizeof(size_t) << " bytes (depende do OS)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 5. STD::STRING vs CHAR[]
    // =========================================================================
    // char[] é herança do C. std::string é o jeito moderno e seguro.
    //
    //  char[]        → array de chars terminado em '\0'. Tamanho FIXO em stack.
    //                  Sem funções de conveniência. Fácil de causar bugs.
    //
    //  std::string   → objeto que gerencia memória automaticamente.
    //                  Pode crescer/diminuir. Tem métodos úteis.
    //                  É o padrão em C++ moderno.
    //
    // Quando ainda usar char[]:
    //   - Compatibilidade com APIs em C (use .c_str() para converter)
    //   - Raramente em código de aplicação nova
    // =========================================================================

    char        nomeAntigo[] = "Carlos";          // jeito C (herança)
    std::string nomeModerno  = "Carlos";           // jeito C++ moderno
    std::string frase        = "Aprendendo C++ moderno";

    std::cout << "--- STD::STRING vs CHAR[] ---" << std::endl;
    std::cout << "char[]:              " << nomeAntigo  << std::endl;
    std::cout << "std::string:         " << nomeModerno << std::endl;
    std::cout << "Tamanho da frase:    " << frase.size()      << " caracteres" << std::endl;
    std::cout << "Primeiros 10 chars:  " << frase.substr(0, 10) << std::endl;

    // .find() retorna a posição (size_t) onde a substring começa.
    // Se não encontrar, retorna std::string::npos (um valor enorme — significa "não encontrado").
    size_t pos = frase.find("C++");
    std::cout << "Posicao de 'C++':    " << pos << "  <- indice onde 'C++' comeca na frase" << std::endl;
    std::cout << "string::npos = " << std::string::npos << "  <- valor especial para 'nao encontrado'" << std::endl;

    // Concatenação simples (impossível com char[] sem funções de C)
    std::string saudacao = "Ola, " + nomeModerno + "!";
    std::cout << "Concatenacao:        " << saudacao << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 6. STD::OPTIONAL<T> (C++17)
    // =========================================================================
    // ANALOGIA: uma caixa que pode estar vazia ou ter algo dentro.
    //
    //   std::optional<int> caixa = 42;           → caixa com o número 42
    //   std::optional<int> caixa = std::nullopt; → caixa vazia (sem valor)
    //
    // PROBLEMA que optional resolve:
    //   Imagine uma função que busca um usuário pelo id.
    //   Se não encontrar, o que ela retorna?
    //
    //   Jeito antigo (ruim):
    //     int buscarIdade(int id) {
    //         if (!encontrado) return -1;   ← -1 pode ser uma idade válida?
    //     }
    //
    //   Jeito correto com optional:
    //     std::optional<int> buscarIdade(int id) {
    //         if (!encontrado) return std::nullopt;  ← "não encontrei nada"
    //         return idade;                          ← "encontrei, aqui está"
    //     }
    //
    // COMO USAR:
    //   .has_value()  → "tem algo na caixa?" (true/false)
    //   .value()      → "me dá o que está dentro" (CUIDADO: lança exceção se vazio!)
    //   .value_or(X)  → "me dá o que está dentro, ou X se estiver vazia"
    //
    // REGRA: prefira .value_or() — ela é segura mesmo se a caixa estiver vazia.
    // =========================================================================

    std::optional<int>         idadeEncontrada = 25;            // tem valor
    std::optional<int>         idadeNaoAchada  = std::nullopt;  // sem valor
    std::optional<std::string> nomeEncontrado  = "Roger";       // tem valor
    std::optional<std::string> nomeNaoAchado   = std::nullopt;  // sem valor

    std::cout << "--- STD::OPTIONAL<T> (C++17) ---" << std::endl;
    std::cout << std::boolalpha;

    std::cout << "idadeEncontrada tem valor? " << idadeEncontrada.has_value() << std::endl;
    std::cout << "idadeNaoAchada  tem valor? " << idadeNaoAchada.has_value()  << std::endl;

    // .value_or() é seguro: retorna o valor, ou o fallback se vazio — sem if/else
    std::cout << "Idade encontrada (ou -1): " << idadeEncontrada.value_or(-1) << std::endl;
    std::cout << "Idade nao achada (ou -1): " << idadeNaoAchada.value_or(-1)  << std::endl;
    std::cout << "Nome encontrado:          " << nomeEncontrado.value_or("Desconhecido") << std::endl;
    std::cout << "Nome nao achado:          " << nomeNaoAchado.value_or("Desconhecido")  << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // 7. CONSTEXPR (C++11)
    // =========================================================================
    // ANALOGIA: se `const` é uma promessa de que ninguém muda o valor,
    // `constexpr` é uma promessa DUPLA: ninguém muda E o valor é calculado
    // antes do programa iniciar (em tempo de compilação).
    //
    // const    → o valor é fixo durante a execução
    // constexpr → o valor é fixo E calculado na compilação
    //
    // VANTAGEM:
    //   - Mais rápido: o compilador substitui as constantes no código gerado
    //   - Mais seguro: erros detectados em compilação, não em execução
    //   - Substitui #define — que era o jeito antigo e inseguro
    //
    // CONVENÇÃO: igual a const — UPPER_SNAKE_CASE para constantes.
    //
    // Quando usar constexpr em vez de const:
    //   - Valores matemáticos fixos (PI, e, raizes)
    //   - Limites de sistema (MAX_JOGADORES, BUFFER_SIZE, BITS_POR_BYTE)
    //   - Qualquer const que possa ser calculada em compilação (a maioria!)
    // =========================================================================

    constexpr double PI            = 3.14159265358979;
    constexpr int    MAX_JOGADORES = 10;
    constexpr int    BITS_POR_BYTE = 8;
    constexpr int    BITS_NUM_INT  = static_cast<int>(sizeof(int)) * BITS_POR_BYTE;

    std::cout << "--- CONSTEXPR (C++11) ---" << std::endl;
    std::cout << "PI            = " << PI            << "  (calculado na compilacao)" << std::endl;
    std::cout << "MAX_JOGADORES = " << MAX_JOGADORES << std::endl;
    std::cout << "BITS_POR_BYTE = " << BITS_POR_BYTE << std::endl;
    std::cout << "Bits em int   = " << BITS_NUM_INT  << "  (sizeof(int) * 8)" << std::endl;

    // Diferenca pratica entre const e constexpr:
    const     int limiteConst     = 100;    // pode ser definido em tempo de execucao
    constexpr int limiteConstexpr = 100;    // DEVE ser definido em tempo de compilacao

    std::cout << "const     limiteConst    = " << limiteConst     << std::endl;
    std::cout << "constexpr limiteConstexpr= " << limiteConstexpr << std::endl;
    std::cout << "  (no output, ambos valem 100 — a diferenca e interna ao compilador)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // FUNÇÃO QUE USA TODOS OS TIPOS MODERNOS JUNTOS
    // =========================================================================
    std::cout << "=============================================" << std::endl;
    std::cout << "   FUNCAO USANDO TODOS OS TIPOS MODERNOS    " << std::endl;
    std::cout << "=============================================" << std::endl;
    demonstrarTodosTiposModernos();
}


// =============================================================================
// FUNÇÃO INTERNA: demonstrarTodosTiposModernos()
// Contexto: sistema de inventário de jogo
// =============================================================================
static void demonstrarTodosTiposModernos()
{
    // --- auto ---
    auto nomeDoJogo  = std::string("Dungeon Quest");
    auto versao      = 2;
    auto fatorDeDano = 1.75;

    // --- decltype ---
    int32_t pontosBase = 1000;
    decltype(pontosBase) pontosBonus = 500;   // mesmo tipo garantido

    // --- nullptr (coberto na Aula 02) ---
    int* itemEquipado = nullptr;    // nenhum item no slot
    int  espada       = 99;         // dano da espada
    int* armaAtual    = &espada;    // item equipado

    // --- int de tamanho fixo ---
    uint8_t  nivelPersonagem  = 42;             // 0-255 (nunca negativo)
    int16_t  defesa           = -5;             // pode ser negativo (debuff)
    uint32_t ouroTotal        = 1500000;        // nunca negativo, pode ser grande
    int64_t  experienciaTotal = 4500000000LL;   // supera int

    // --- size_t ---
    std::string inventario[4] = {"Espada", "Escudo", "Pocao", "Mapa"};
    size_t totalItens = sizeof(inventario) / sizeof(inventario[0]);

    // --- std::string ---
    std::string nomePersonagem = "Rogerio";
    std::string classe         = "Guerreiro";
    std::string statusCompleto = nomePersonagem + " - " + classe;

    // --- std::optional ---
    std::optional<std::string> missaoAtiva = "Derrotar o Dragao";
    std::optional<std::string> guildaAtual = std::nullopt; // sem guilda

    // --- constexpr ---
    constexpr int NIVEL_MAXIMO = 99;

    // --- IMPRESSÃO ---
    std::cout << std::endl;
    std::cout << "=== INVENTARIO DO JOGO ===" << std::endl;
    std::cout << std::boolalpha;

    std::cout << "[auto]       Nome do jogo:  " << nomeDoJogo  << std::endl;
    std::cout << "[auto]       Versao:        " << versao      << std::endl;
    std::cout << "[auto]       Fator dano:    " << fatorDeDano << std::endl;

    std::cout << "[decltype]   Pontos base:   " << pontosBase  << std::endl;
    std::cout << "[decltype]   Pontos bonus:  " << pontosBonus << "  (mesmo tipo de pontosBase)" << std::endl;

    std::cout << "[nullptr]    Slot vazio:    " << "nenhum — itemEquipado = nullptr" << std::endl;
    std::cout << "[nullptr]    Arma atual:    " << *armaAtual << " dano" << std::endl;
    (void)itemEquipado;   // demonstrado no comentário acima; suprime warning de unused

    std::cout << "[uint8_t]    Nivel:         " << static_cast<int>(nivelPersonagem) << std::endl;
    std::cout << "[int16_t]    Defesa:        " << defesa          << std::endl;
    std::cout << "[uint32_t]   Ouro:          " << ouroTotal       << std::endl;
    std::cout << "[int64_t]    Experiencia:   " << experienciaTotal << std::endl;

    std::cout << "[size_t]     Total itens:   " << totalItens << std::endl;
    std::cout << "[size_t]     Inventario:    "
              << inventario[0] << ", " << inventario[1] << ", "
              << inventario[2] << ", " << inventario[3] << std::endl;

    std::cout << "[std::string] Personagem:   " << statusCompleto << std::endl;

    std::cout << "[optional]   Missao ativa:  " << missaoAtiva.value_or("Nenhuma")    << std::endl;
    std::cout << "[optional]   Guilda:        " << guildaAtual.value_or("Sem guilda") << std::endl;

    std::cout << "[constexpr]  Nivel maximo:  " << NIVEL_MAXIMO << std::endl;

    std::cout << std::endl;
    std::cout << "=== TAMANHOS DOS TIPOS FIXOS ===" << std::endl;
    std::cout << "int8_t   = " << sizeof(int8_t)   << " byte(s) | range: -128 a 127"          << std::endl;
    std::cout << "uint8_t  = " << sizeof(uint8_t)  << " byte(s) | range: 0 a 255"             << std::endl;
    std::cout << "int16_t  = " << sizeof(int16_t)  << " byte(s) | range: -32768 a 32767"      << std::endl;
    std::cout << "uint16_t = " << sizeof(uint16_t) << " byte(s) | range: 0 a 65535"           << std::endl;
    std::cout << "int32_t  = " << sizeof(int32_t)  << " byte(s) | range: -2bi a 2bi"          << std::endl;
    std::cout << "uint32_t = " << sizeof(uint32_t) << " byte(s) | range: 0 a 4.29bi"          << std::endl;
    std::cout << "int64_t  = " << sizeof(int64_t)  << " byte(s) | range: -9.2qi a 9.2qi"      << std::endl;
    std::cout << "uint64_t = " << sizeof(uint64_t) << " byte(s) | range: 0 a 18.4qi"          << std::endl;
}
