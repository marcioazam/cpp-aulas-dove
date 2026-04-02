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
//   3. nullptr    — ponteiro nulo seguro
//   4. int32_t / uint64_t — inteiros de tamanho fixo (<cstdint>)
//   5. size_t     — tipo correto para tamanhos e índices
//   6. std::string vs char[]
//   7. std::optional<T> (C++17) — valor que pode não existir
//
// =============================================================================

#include "aula03_tipos_modernos.h"
#include <iostream>
#include <iomanip>
#include <string>       // std::string
#include <cstdint>      // int32_t, uint64_t, int8_t, etc.
#include <optional>     // std::optional (C++17)
#include <vector>       // usado nos exemplos de auto/size_t

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
    // O tipo é decidido em tempo de compilação, não em execução.
    // Não é uma variante de "tipo dinâmico" — é 100% tipado e seguro.
    //
    // Quando usar:
    //   - Tipos longos e verbosos (iteradores, tipos de retorno complexos)
    //   - Laços for-each (for auto valor : colecao)
    //   - Quando o tipo é óbvio pelo lado direito da expressão
    //
    // Quando NÃO usar:
    //   - Quando o tipo não é óbvio para quem lê o código
    //   - Parâmetros de função (não é permitido sem templates)
    //   - Quando você quer ser explícito por clareza
    // =========================================================================

    auto numero    = 42;            // int     — literal inteiro = int
    auto decimal   = 3.14;         // double  — literal double = double
    auto decimalF  = 3.14f;        // float   — sufixo 'f' = float
    auto grande    = 9000000000LL; // long long — sufixo 'LL'
    auto letra     = 'Z';          // char    — literal char = char
    auto texto     = std::string("Olá C++"); // std::string
    auto verdadeiro = true;        // bool

    std::cout << "--- AUTO (C++11) ---" << std::endl;
    std::cout << "auto numero    = " << numero    << "  (int)"       << std::endl;
    std::cout << "auto decimal   = " << decimal   << "  (double)"    << std::endl;
    std::cout << "auto decimalF  = " << decimalF  << "f (float)"     << std::endl;
    std::cout << "auto grande    = " << grande    << " (long long)"  << std::endl;
    std::cout << "auto letra     = " << letra     << "  (char)"      << std::endl;
    std::cout << "auto texto     = " << texto     << "  (std::string)" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "auto verdadeiro= " << verdadeiro << "  (bool)"     << std::endl;

    // auto brilha em loops com coleções
    std::vector<int> numeros = {10, 20, 30, 40, 50};
    std::cout << "for (auto v : vetor): ";
    for (auto x : numeros) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Sem auto, o iterador seria:
    // std::vector<int>::iterator it = numeros.begin();  ← verboso
    // Com auto:
    auto it = numeros.begin();  // limpo e correto
    std::cout << "Primeiro via iterator: " << *it << std::endl << std::endl;


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
    // DIFERENÇA em relação ao auto:
    //   auto y = x;           → y recebe o VALOR de x (y = 10)
    //   decltype(x) y = 20;   → y recebe o TIPO de x, mas o valor que você escolher (y = 20)
    //
    //   auto = "copie o valor e deduza o tipo"
    //   decltype = "use o tipo desta expressão, mas o valor eu defino"
    //
    // QUANDO VOCÊ VAI USAR NA PRÁTICA:
    //   - Garantir que duas variáveis têm exatamente o mesmo tipo
    //   - Em templates avançados (não se preocupe agora — virá mais à frente)
    // =========================================================================

    int    baseInt    = 10;
    double baseDouble = 3.14;

    // copia tem exatamente o tipo de baseInt (int), recebe valor 99
    decltype(baseInt)    copia    = 99;

    // resultado tem o tipo de (baseInt + baseDouble) = double
    decltype(baseInt + baseDouble) resultado = 5.5;

    // Útil: garantir que duas variáveis têm exatamente o mesmo tipo
    decltype(baseInt) contadorAuxiliar = 0;

    std::cout << "--- DECLTYPE (C++11) ---" << std::endl;
    std::cout << "baseInt = " << baseInt    << " (int)"    << std::endl;
    std::cout << "baseDouble = " << baseDouble << " (double)" << std::endl;
    std::cout << "decltype(baseInt) copia = " << copia     << " (int)"    << std::endl;
    std::cout << "decltype(int+double) resultado = " << resultado << " (double)" << std::endl;
    std::cout << "decltype(baseInt) contadorAuxiliar = " << contadorAuxiliar << std::endl;
    std::cout << "Tamanho de decltype(int+double): "
              << sizeof(decltype(baseInt + baseDouble)) << " bytes (double)" << std::endl << std::endl;


    // =========================================================================
    // 3. NULLPTR (C++11)
    // =========================================================================
    // ANALOGIA: um ponteiro é como uma placa com um endereço escrito.
    //   int* p = &x;   → a placa tem o endereço de x
    //   int* p = nullptr; → a placa está EM BRANCO (não aponta para nada)
    //
    // nullptr é essa "placa em branco" oficial do C++ moderno.
    //
    // REGRA FUNDAMENTAL:
    //   NUNCA acesse um ponteiro sem antes verificar se ele é nullptr.
    //   Se você tentar ler *p quando p = nullptr → o programa TRAVA (segfault).
    //
    //   if (p != nullptr) {
    //       std::cout << *p;   ← seguro: só acessa se há endereço válido
    //   }
    //
    // POR QUE NÃO usar NULL ou 0 (jeito antigo)?
    //   NULL era definido como o número 0 — o compilador não sabia se você
    //   queria o número zero ou um ponteiro nulo. nullptr é inequívoco:
    //   só pode ser um ponteiro. Nunca use NULL ou 0 em C++ moderno.
    // =========================================================================

    int* ponteiroNulo   = nullptr;    // ponteiro para int, mas aponta para nada
    int  valorReal      = 42;
    int* ponteiroValido = &valorReal; // ponteiro para int, aponta para valorReal

    std::cout << "--- NULLPTR (C++11) ---" << std::endl;
    std::cout << "ponteiroNulo == nullptr? " << (ponteiroNulo == nullptr ? "sim" : "nao") << std::endl;

    // Verificação segura antes de usar o ponteiro
    if (ponteiroNulo != nullptr) {
        std::cout << "Valor pelo ponteiro nulo: " << *ponteiroNulo << std::endl;
    } else {
        std::cout << "Ponteiro nulo: acesso bloqueado com seguranca" << std::endl;
    }

    if (ponteiroValido != nullptr) {
        std::cout << "Valor pelo ponteiro valido: " << *ponteiroValido << std::endl;
    }
    std::cout << std::endl;


    // =========================================================================
    // 4. INTEIROS DE TAMANHO FIXO — int32_t, uint64_t, etc. (<cstdint>)
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
    //   - Comunicação com hardware, drivers
    //   - Qualquer lugar onde "int tem 4 bytes aqui" não é suficiente
    // =========================================================================

    int8_t   byteComSinal    = -100;    // 1 byte  com sinal
    uint8_t  byteSemSinal    = 200;     // 1 byte  sem sinal (ex: valor de pixel)
    int16_t  inteiro16       = -30000;  // 2 bytes com sinal
    uint16_t inteiro16u      = 60000;   // 2 bytes sem sinal (ex: porta de rede)
    int32_t  inteiro32       = -2000000000; // 4 bytes com sinal (=int garantido)
    uint32_t inteiro32u      = 4000000000U; // 4 bytes sem sinal
    int64_t  inteiro64       = -9000000000000000000LL; // 8 bytes (=long long)
    uint64_t inteiro64u      = 18000000000000000000ULL; // 8 bytes sem sinal

    std::cout << "--- INTEIROS DE TAMANHO FIXO <cstdint> ---" << std::endl;
    std::cout << "int8_t   (-100):        " << static_cast<int>(byteComSinal)
              << " | " << sizeof(int8_t)   << " byte(s)" << std::endl;
    std::cout << "uint8_t  (200):         " << static_cast<int>(byteSemSinal)
              << " | " << sizeof(uint8_t)  << " byte(s)" << std::endl;
    std::cout << "int16_t  (-30000):      " << inteiro16
              << " | " << sizeof(int16_t)  << " byte(s)" << std::endl;
    std::cout << "uint16_t (60000):       " << inteiro16u
              << " | " << sizeof(uint16_t) << " byte(s)" << std::endl;
    std::cout << "int32_t  (-2bi):        " << inteiro32
              << " | " << sizeof(int32_t)  << " byte(s)" << std::endl;
    std::cout << "uint32_t (4bi):         " << inteiro32u
              << " | " << sizeof(uint32_t) << " byte(s)" << std::endl;
    std::cout << "int64_t  (-9qi):        " << inteiro64
              << " | " << sizeof(int64_t)  << " byte(s)" << std::endl;
    std::cout << "uint64_t (18qi):        " << inteiro64u
              << " | " << sizeof(uint64_t) << " byte(s)" << std::endl << std::endl;


    // =========================================================================
    // 5. SIZE_T — O TIPO CORRETO PARA TAMANHOS E ÍNDICES
    // =========================================================================
    // size_t é um tipo sem sinal definido pelo sistema operacional.
    //   - Em sistemas 32-bit: uint32_t (0 a 4.29bi)
    //   - Em sistemas 64-bit: uint64_t (0 a 18.4qi)
    //
    // Quando usar:
    //   - Índices de arrays e vetores (evita warning de signed/unsigned mismatch)
    //   - Tamanho de objetos, buffers, strings
    //   - Resultados de sizeof() e .size()
    //
    // Por que não usar int para índice?
    //   std::vector tem .size() que retorna size_t.
    //   Comparar int com size_t gera warning de compilação — e pode ter bug
    //   se o vetor for enorme (2bi+ elementos em sistema 64-bit).
    // =========================================================================

    std::vector<int> vetor = {100, 200, 300, 400, 500};

    size_t tamanho     = vetor.size();   // correto: size_t, não int
    size_t indice      = 2;

    std::cout << "--- SIZE_T ---" << std::endl;
    std::cout << "Tamanho do vetor (size_t): " << tamanho << std::endl;
    std::cout << "Elemento [" << indice << "]: " << vetor[indice] << std::endl;
    std::cout << "Tamanho de size_t: " << sizeof(size_t) << " byte(s) (depende do OS)" << std::endl;

    // Loop correto com size_t
    std::cout << "Loop com size_t: ";
    for (size_t i = 0; i < vetor.size(); ++i) {
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl << std::endl;


    // =========================================================================
    // 6. STD::STRING vs CHAR[]
    // =========================================================================
    // char[] é herança do C. std::string é o jeito moderno e seguro.
    //
    //  char[]        → array de chars terminado em '\0'. Tamanho FIXO em stack.
    //                  Sem funções de conveniência. Fácil de vazar memória.
    //
    //  std::string   → objeto que gerencia memória automaticamente.
    //                  Pode crescer/diminuir. Tem métodos úteis.
    //                  É o padrão em C++ moderno.
    //
    // Quando usar char[]:
    //   - Compatibilidade com APIs C (e ainda assim, prefira .c_str())
    //   - Buffers de tamanho fixo e conhecido em contexto de performance crítica
    //   - Nunca no código de aplicação nova
    // =========================================================================

    // Jeito antigo (C)
    char nomeAntigo[] = "Carlos";

    // Jeito moderno (C++)
    std::string nomeModerno = "Carlos";

    // std::string tem métodos úteis
    std::string frase = "Aprendendo C++ moderno";

    std::cout << "--- STD::STRING vs CHAR[] ---" << std::endl;
    std::cout << "char[]:            " << nomeAntigo  << std::endl;
    std::cout << "std::string:       " << nomeModerno << std::endl;
    std::cout << "Tamanho da frase:  " << frase.size() << " caracteres" << std::endl;
    std::cout << "Primeiros 10:      " << frase.substr(0, 10) << std::endl;
    std::cout << "Contem 'C++'?      " << (frase.find("C++") != std::string::npos ? "sim" : "nao") << std::endl;

    // Concatenação simples com std::string (impossível com char[] sem strcat)
    std::string saudacao = "Ola, " + nomeModerno + "!";
    std::cout << "Concatenação:      " << saudacao << std::endl << std::endl;


    // =========================================================================
    // 7. STD::OPTIONAL<T> (C++17)
    // =========================================================================
    // ANALOGIA: uma caixa que pode estar vazia ou ter algo dentro.
    //
    //   std::optional<int> caixa = 42;          → caixa com o número 42
    //   std::optional<int> caixa = std::nullopt; → caixa vazia (sem valor)
    //
    // PROBLEMA que optional resolve:
    //   Imagine uma função que busca um usuário pelo nome.
    //   Se não encontrar, o que ela retorna?
    //
    //   Jeito ruim (antes do C++17):
    //     int buscarIdade(string nome) {
    //         if (!encontrado) return -1;   ← PROBLEMA: -1 pode ser uma idade válida?
    //     }
    //
    //   Jeito correto com optional:
    //     std::optional<int> buscarIdade(string nome) {
    //         if (!encontrado) return std::nullopt;  ← "não encontrei nada"
    //         return idade;                          ← "encontrei, aqui está"
    //     }
    //
    // COMO USAR o valor:
    //   .has_value()    → "tem algo na caixa?" (retorna true/false)
    //   .value()        → "me dá o que está dentro" (CUIDADO: trava se vazio!)
    //   .value_or(X)    → "me dá o que está dentro, ou X se estiver vazia"
    //
    // REGRA: sempre use .has_value() antes de .value(), ou use .value_or().
    // =========================================================================

    std::optional<int>         idadeEncontrada  = 25;        // tem valor
    std::optional<int>         idadeNaoAchada   = std::nullopt; // sem valor
    std::optional<std::string> nomeEncontrado   = "Roger";   // tem valor
    std::optional<std::string> nomeNaoAchado    = std::nullopt; // sem valor

    std::cout << "--- STD::OPTIONAL<T> (C++17) ---" << std::endl;

    // .has_value() verifica se há valor
    std::cout << "idadeEncontrada tem valor? " << std::boolalpha << idadeEncontrada.has_value() << std::endl;
    std::cout << "idadeNaoAchada  tem valor? " << idadeNaoAchada.has_value()  << std::endl;

    // .value() acessa o valor (lança exceção se vazio)
    if (idadeEncontrada.has_value()) {
        std::cout << "Idade: " << idadeEncontrada.value() << std::endl;
    }

    // .value_or(default) — retorna valor ou fallback se vazio
    std::cout << "Idade (ou -1):  " << idadeNaoAchada.value_or(-1) << std::endl;
    std::cout << "Nome encontrado:" << nomeEncontrado.value_or("Desconhecido") << std::endl;
    std::cout << "Nome nao achado:" << nomeNaoAchado.value_or("Desconhecido")  << std::endl << std::endl;


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
    auto nomeDoJogo   = std::string("Dungeon Quest");
    auto versao       = 2;
    auto fatorDeDano  = 1.75;

    // --- decltype ---
    int32_t pontosBase = 1000;
    decltype(pontosBase) pontosBonus = 500;   // mesmo tipo garantido

    // --- nullptr ---
    int* itemEquipado = nullptr;              // nenhum item no slot
    int  espada       = 99;                   // dano da espada
    int* armaAtual    = &espada;              // item equipado

    // --- int de tamanho fixo ---
    uint8_t  nivelPersonagem  = 42;           // 0-255 (nunca negativo)
    int16_t  defesa           = -5;           // pode ser negativo (debuff)
    uint32_t ouroTotal        = 1500000;      // nunca negativo, pode ser grande
    int64_t  experienciaTotal = 4500000000LL; // supera int

    // --- size_t ---
    std::vector<std::string> inventario = {"Espada", "Escudo", "Pocao", "Mapa"};
    size_t totalItens = inventario.size();

    // --- std::string ---
    std::string nomePersonagem = "Rogério";
    std::string classe         = "Guerreiro";
    std::string statusCompleto = nomePersonagem + " — " + classe;

    // --- std::optional ---
    std::optional<std::string> missaoAtiva = "Derrotar o Dragão";
    std::optional<std::string> guildaAtual = std::nullopt; // sem guilda

    // --- IMPRESSÃO ---
    std::cout << std::endl;
    std::cout << "=== INVENTARIO DO JOGO ===" << std::endl;
    std::cout << std::boolalpha;

    std::cout << "[auto]       Nome do jogo:  " << nomeDoJogo          << std::endl;
    std::cout << "[auto]       Versao:        " << versao              << std::endl;
    std::cout << "[auto]       Fator dano:    " << fatorDeDano         << std::endl;

    std::cout << "[decltype]   Pontos base:   " << pontosBase          << std::endl;
    std::cout << "[decltype]   Pontos bonus:  " << pontosBonus         << " (mesmo tipo de pontosBase)" << std::endl;

    std::cout << "[nullptr]    Item equipado? " << (itemEquipado != nullptr ? "sim" : "nao") << std::endl;
    std::cout << "[nullptr]    Arma atual:    " << (armaAtual != nullptr ? std::to_string(*armaAtual) + " dano" : "nenhuma") << std::endl;

    std::cout << "[uint8_t]    Nivel:         " << static_cast<int>(nivelPersonagem) << std::endl;
    std::cout << "[int16_t]    Defesa:        " << defesa              << std::endl;
    std::cout << "[uint32_t]   Ouro:          " << ouroTotal           << std::endl;
    std::cout << "[int64_t]    Experiencia:   " << experienciaTotal    << std::endl;

    std::cout << "[size_t]     Total itens:   " << totalItens          << std::endl;
    std::cout << "[size_t]     Inventario:    ";
    for (size_t i = 0; i < inventario.size(); ++i) {
        std::cout << inventario[i];
        if (i < inventario.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "[std::string] Personagem:   " << statusCompleto      << std::endl;

    std::cout << "[optional]   Missao ativa:  "
              << missaoAtiva.value_or("Nenhuma") << std::endl;
    std::cout << "[optional]   Guilda:        "
              << guildaAtual.value_or("Sem guilda") << std::endl;

    std::cout << std::endl;
    std::cout << "=== TAMANHOS DOS TIPOS FIXOS ===" << std::endl;
    std::cout << "int8_t   = " << sizeof(int8_t)   << " byte(s) | range: -128 a 127"          << std::endl;
    std::cout << "uint8_t  = " << sizeof(uint8_t)  << " byte(s) | range: 0 a 255"             << std::endl;
    std::cout << "int16_t  = " << sizeof(int16_t)  << " byte(s) | range: -32768 a 32767"      << std::endl;
    std::cout << "uint16_t = " << sizeof(uint16_t) << " byte(s) | range: 0 a 65535"           << std::endl;
    std::cout << "int32_t  = " << sizeof(int32_t)  << " byte(s) | range: -2bi a 2bi"          << std::endl;
    std::cout << "uint32_t = " << sizeof(uint32_t) << " byte(s) | range: 0 a 4.29bi"         << std::endl;
    std::cout << "int64_t  = " << sizeof(int64_t)  << " byte(s) | range: -9.2qi a 9.2qi"     << std::endl;
    std::cout << "uint64_t = " << sizeof(uint64_t) << " byte(s) | range: 0 a 18.4qi"         << std::endl;
}
