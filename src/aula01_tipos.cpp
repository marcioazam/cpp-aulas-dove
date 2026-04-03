// =============================================================================
// AULA 01 - TIPOS DE DADOS EM C++
// =============================================================================
//
// Todo valor que você armazena em memória precisa de um TIPO.
// O tipo define:
//   1. Quanta memória reservar (bytes)
//   2. Quais valores cabem nessa memória
//   3. O que você pode fazer com esse valor (operações)
//
// Tipos cobertos: bool · char · int · float · double · short · long long · unsigned
// Extras:         operadores aritméticos · casting · overflow · const
//
// =============================================================================

#include "aula01_tipos.h"
#include <iostream>
#include <iomanip>   // std::fixed, std::setprecision
#include <climits>   // INT_MAX, INT_MIN, SHRT_MAX, etc.

// Função interna - só visível neste arquivo
static void demonstrarTodosTipos();

// =============================================================================
// PONTO DE ENTRADA DA AULA 01
// =============================================================================
void rodarAula01()
{
    std::cout << "=============================================" << std::endl;
    std::cout << "       AULA 01 - TIPOS DE DADOS C++         " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;


    // =========================================================================
    // BOOL
    // =========================================================================
    // Tamanho : 1 byte
    // Valores : true (1) ou false (0)
    // Quando usar: flags de estado, resultados de condições, ligado/desligado
    //
    // Pense assim: qualquer pergunta de SIM ou NÃO é um bool.
    // =========================================================================

    bool jogoEstaPausado      = false;
    bool personagemEstaMorto  = false;
    bool temConexaoInternet   = true;

    std::cout << "--- BOOL ---" << std::endl;
    std::cout << "Jogo pausado?     " << std::boolalpha << jogoEstaPausado     << std::endl;
    std::cout << "Personagem morto? " << personagemEstaMorto                   << std::endl;
    std::cout << "Tem internet?     " << temConexaoInternet                    << std::endl;
    std::cout << "Tamanho: " << sizeof(bool) << " byte(s)" << std::endl << std::endl;


    // =========================================================================
    // CHAR
    // =========================================================================
    // Tamanho : 1 byte
    // Valores : representa um único caractere ASCII
    // Quando usar: um único caractere (letra, dígito, símbolo)
    //
    // ATENÇÃO: Para texto use std::string. Use char só para UM caractere.
    // =========================================================================

    char letraInicial          = 'M';
    char genero                = 'F'; // M=Masculino, F=Feminino, O=Outro
    char primeiroDigitoPlaca   = '7';
    char nomeEmCharArray[]     = "Carlos";

    std::cout << "--- CHAR ---" << std::endl;
    std::cout << "Inicial do nome:     " << letraInicial        << std::endl;
    std::cout << "Gênero:              " << genero                << std::endl;
    std::cout << "Digito da placa:     " << primeiroDigitoPlaca  << std::endl;
    std::cout << "Nome (char[]):       " << nomeEmCharArray      << std::endl;
    std::cout << "Valor numerico 'A':  " << static_cast<int>('A') << std::endl;
    std::cout << "Tamanho: " << sizeof(char) << " byte(s)" << std::endl << std::endl;


    // =========================================================================
    // INT
    // =========================================================================
    // Tamanho : 4 bytes
    // Valores : -2.147.483.648 a +2.147.483.647 (~2 bilhões em cada direção)
    // Quando usar: PADRÃO para inteiros no dia a dia.
    //              Contadores, idade, quantidade, pontuação, índice de array.
    //
    // Regra: se o número não tem vírgula e cabe em 2 bilhões, use int.
    // =========================================================================

    int idade               = 25;
    int pontosNoJogo        = 1500;
    int temperaturaEmCelsius = -15;
    int quantidadeDeVidas   = 3;

    std::cout << "--- INT ---" << std::endl;
    std::cout << "Idade:           " << idade                << std::endl;
    std::cout << "Pontos:          " << pontosNoJogo         << std::endl;
    std::cout << "Temperatura:     " << temperaturaEmCelsius << " C" << std::endl;
    std::cout << "Vidas:           " << quantidadeDeVidas    << std::endl;
    std::cout << "Maximo possivel: " << INT_MAX              << std::endl;
    std::cout << "Minimo possivel: " << INT_MIN              << std::endl;
    std::cout << "Tamanho: " << sizeof(int) << " byte(s)" << std::endl << std::endl;


    // =========================================================================
    // FLOAT vs DOUBLE  (os dois armazenam números com vírgula/decimal)
    // =========================================================================
    //
    //  FLOAT:  4 bytes | ~7  dígitos de precisão
    //  DOUBLE: 8 bytes | ~15 dígitos de precisão
    //
    //  POR QUE DOUBLE É MELHOR NO DIA A DIA?
    //    - Dobro de precisão: erros de arredondamento muito menores
    //    - Processadores 64-bit calculam double tão rápido quanto float
    //    - O padrão do C++ é double (3.14 é double, 3.14f é float)
    //
    //  QUANDO FLOAT É CORRETO:
    //    - GPU/shaders (hardware otimizado para 32-bit)
    //    - Arrays com milhões de elementos (economiza RAM)
    //    - Bibliotecas de física/gráficos que exigem float
    // =========================================================================

    float  somaFloat  = 0.1f + 0.2f;
    double somaDouble = 0.1  + 0.2;

    float  precoFloat  = 19.99f;
    double precoDouble = 19.99;

    std::cout << "--- FLOAT vs DOUBLE ---" << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "float  0.1 + 0.2 = " << somaFloat  << "  <- erro visivel" << std::endl;
    std::cout << "double 0.1 + 0.2 = " << somaDouble << "  <- mais preciso"  << std::endl;
    std::cout << std::setprecision(2);
    std::cout << "Preco float:  R$ " << precoFloat  << std::endl;
    std::cout << "Preco double: R$ " << precoDouble << std::endl;
    std::cout << "Tamanho float:  " << sizeof(float)  << " byte(s)" << std::endl;
    std::cout << "Tamanho double: " << sizeof(double) << " byte(s)" << std::endl << std::endl;


    // =========================================================================
    // SHORT
    // =========================================================================
    // Tamanho : 2 bytes
    // Valores : -32.768 a +32.767
    // Quando usar: quando você SABE que o valor nunca passa de 32 mil
    //              e memória importa (arrays de imagem, protocolos de rede,
    //              sensores com range pequeno, áudio PCM 16-bit).
    //
    // Na prática: use int por padrão. Escolha short quando:
    //   - Compatibilidade com protocolo que define 16-bit
    //   - Array com milhões de elementos onde short economiza metade da RAM
    // =========================================================================

    short portaDeRede        = 8080;
    short temperaturaDoSensor = -40;
    short valorRGBDoPixel    = 255;

    std::cout << "--- SHORT ---" << std::endl;
    std::cout << "Porta de rede:  " << portaDeRede         << std::endl;
    std::cout << "Temperatura:    " << temperaturaDoSensor << " C" << std::endl;
    std::cout << "Cor do pixel:   " << valorRGBDoPixel     << std::endl;
    std::cout << "Maximo:         " << SHRT_MAX            << std::endl;
    std::cout << "Minimo:         " << SHRT_MIN            << std::endl;
    std::cout << "Tamanho: " << sizeof(short) << " byte(s)" << std::endl << std::endl;


    // =========================================================================
    // LONG LONG
    // =========================================================================
    //
    //  LONG:      4 ou 8 bytes (VARIA por plataforma — evite)
    //  LONG LONG: 8 bytes GARANTIDO em qualquer plataforma
    //
    //  Valores: ±9,2 quintilhões
    //  Quando usar:
    //    - Valores que ultrapassam 2 bilhões (int não aguenta)
    //    - Timestamps Unix em milissegundos
    //    - Tamanho de arquivos grandes (bytes)
    //    - IDs de banco de dados com muitas linhas
    //
    //  DICA: Use sufixo 'LL' para literais: 9000000000LL
    // =========================================================================

    long long timestampEmMs    = 1711234567890LL;
    long long populacaoMundial = 8100000000LL;        // não cabe em int!
    long long tamanhoArquivo   = 50LL * 1024 * 1024 * 1024; // 50 GB em bytes
    long long idNoBanco        = 9876543210LL;

    std::cout << "--- LONG LONG ---" << std::endl;
    std::cout << "Timestamp (ms):      " << timestampEmMs    << std::endl;
    std::cout << "Populacao mundial:   " << populacaoMundial << std::endl;
    std::cout << "Arquivo 50GB (bytes):" << tamanhoArquivo   << std::endl;
    std::cout << "ID no banco:         " << idNoBanco        << std::endl;
    std::cout << "Tamanho long:        " << sizeof(long)      << " byte(s) (varia por OS)" << std::endl;
    std::cout << "Tamanho long long:   " << sizeof(long long) << " byte(s) (fixo)"         << std::endl << std::endl;


    // =========================================================================
    // UNSIGNED
    // =========================================================================
    // Modificador que remove o sinal negativo, dobrando o range positivo.
    //
    //  unsigned int      : 0 a 4.294.967.295 (~4 bilhões)
    //  unsigned short    : 0 a 65.535
    //  unsigned long long: 0 a ~18 quintilhões
    //
    // Quando usar:
    //   - Valores que NUNCA serão negativos (contadores, tamanhos, índices)
    //   - Portas de rede (0-65535)
    //   - Operações bit a bit (bitmasks)
    //
    // CUIDADO: unsigned int x = 0; x = x - 1; → x vira 4.294.967.295 !!
    //
    //  DICA: Use sufixo 'ULL' para literais: 9000000000ULL
    // =========================================================================

    unsigned long  quantidadeDeJogadores = 4;
    unsigned int  larguraDaTela         = 1920;
    unsigned int  alturaDaTela          = 1080;
    unsigned short portaHTTP            = 80;
    unsigned long long bytesTransferidos = 12345678901234ULL;

    std::cout << "--- UNSIGNED ---" << std::endl;
    std::cout << "Jogadores:          " << quantidadeDeJogadores  << std::endl;
    std::cout << "Resolucao:          " << larguraDaTela << "x" << alturaDaTela << std::endl;
    std::cout << "Porta HTTP:         " << portaHTTP              << std::endl;
    std::cout << "Bytes transferidos: " << bytesTransferidos      << std::endl;
    std::cout << "unsigned int max:   " << UINT_MAX               << std::endl;
    std::cout << "int max (signed):   " << INT_MAX << " (metade)" << std::endl << std::endl;


    // =========================================================================
    // OPERADORES ARITMÉTICOS
    // =========================================================================
    // Os operadores definem o que você pode FAZER com os tipos numéricos.
    //
    //   +   soma
    //   -   subtração
    //   *   multiplicação
    //   /   divisão  ← CUIDADO: comportamento diferente para int e double!
    //   %   módulo (resto da divisão inteira) — só funciona com inteiros
    //
    // DIVISÃO INTEIRA — a armadilha mais comum para iniciantes:
    //   int / int sempre trunca (joga fora) a parte decimal.
    //   7 / 2 = 3  (não 3.5!)
    //   Para obter 3.5, pelo menos um dos lados precisa ser double:
    //   7 / 2.0 = 3.5   ou   static_cast<double>(7) / 2 = 3.5
    //
    // MÓDULO `%` — retorna o RESTO da divisão inteira:
    //   10 % 3 = 1  porque 10 = 3×3 + 1
    //   Usos: verificar paridade (x % 2 == 0 → par), ciclos, índices circulares
    // =========================================================================

    std::cout << "--- OPERADORES ARITMETICOS ---" << std::endl;

    int a = 7, b = 2;
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << "  <- divisao INTEIRA (trunca!)" << std::endl;
    std::cout << "a / 2.0 = " << std::fixed << std::setprecision(1)
              << a / 2.0 << "  <- divisao REAL (um lado e double)" << std::endl;
    std::cout << "a % b = " << a % b << "  <- resto: 7 = 2x3 + 1" << std::endl;

    std::cout << "10 % 2 = " << 10 % 2 << "  (par: resto zero)"     << std::endl;
    std::cout << "11 % 2 = " << 11 % 2 << "  (impar: resto um)"      << std::endl;
    std::cout << "10 % 3 = " << 10 % 3 << "  (10 = 3x3 + 1)"        << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // CONVERSÃO DE TIPOS (TYPE CASTING)
    // =========================================================================
    // Às vezes você precisa converter um valor de um tipo para outro.
    // Há dois jeitos: implícito (automático) e explícito (você decide).
    //
    // IMPLÍCITO — o compilador converte automaticamente:
    //   int x = 3.9;     → x vale 3  (trunca, não arredonda!)
    //   double d = 5;    → d vale 5.0 (seguro, sem perda)
    //
    //   Narrowing (perigoso, pode perder dados):  double → int, int → char
    //   Widening (seguro, sem perda):              int → double, char → int
    //
    // EXPLÍCITO — static_cast<TIPO>(valor):
    //   static_cast<int>(3.9)         → 3   (você decide conscientemente)
    //   static_cast<double>(7) / 2    → 3.5 (força divisão real)
    //   static_cast<int>('A')         → 65  (valor ASCII do caractere)
    //   static_cast<char>(65)         → 'A' (65 na tabela ASCII = 'A')
    //
    // REGRA: prefira static_cast ao invés de conversão implícita — deixa claro
    //        para o leitor (e para o compilador) que a conversão é intencional.
    // =========================================================================

    std::cout << "--- CONVERSAO DE TIPOS (CASTING) ---" << std::endl;

    // Implícita: double → int (trunca, não arredonda)
    // Em código real: int iValor = dValor;  ← compila mas gera warning -Wconversion
    double dValor  = 3.9;
    int    iValor  = static_cast<int>(dValor);   // explícita — mesmo resultado, sem warning
    std::cout << "double 3.9 -> int (truncado):          " << iValor
              << "  (truncou, nao arredondou!)" << std::endl;

    // Explícita com static_cast
    std::cout << "static_cast<int>(3.9):                 "
              << static_cast<int>(3.9) << std::endl;
    std::cout << "static_cast<int>(3.1):                 "
              << static_cast<int>(3.1) << std::endl;

    // Forçar divisão real
    int x = 7, y = 2;
    std::cout << "7 / 2 (int/int):                       "
              << x / y << "  (inteiro)" << std::endl;
    std::cout << "static_cast<double>(7) / 2:            "
              << std::setprecision(1) << static_cast<double>(x) / y
              << "  (real)" << std::endl;

    // char ↔ int (tabela ASCII)
    char letra = 'A';
    std::cout << "static_cast<int>('A'):                 "
              << static_cast<int>(letra) << "  (valor ASCII de 'A')" << std::endl;
    std::cout << "static_cast<char>(66):                 "
              << static_cast<char>(66) << "  (ASCII 66 = 'B')" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // OVERFLOW E UNDERFLOW
    // =========================================================================
    // Cada tipo tem um limite. O que acontece ao ultrapassar esse limite?
    //
    // OVERFLOW (passou do máximo):
    //   INT_MAX + 1 → comportamento indefinido em signed (na prática: vira INT_MIN)
    //   É como um velocímetro que passa de 999km/h e volta para 000km/h.
    //
    // UNDERFLOW UNSIGNED (passou do mínimo):
    //   0u - 1 → 4.294.967.295  (wraparound garantido para unsigned)
    //   Unsigned nunca é negativo — "volta" para o máximo.
    //
    // COMO EVITAR:
    //   - Escolha o tipo certo para o range do valor
    //   - Antes de somar, verifique se o resultado cabe no tipo
    //   - Use tipos maiores (long long) para valores que podem crescer muito
    // =========================================================================

    std::cout << "--- OVERFLOW / UNDERFLOW ---" << std::endl;

    // volatile impede que o compilador calcule em tempo de compilação,
    // permitindo demonstrar o overflow em execução sem warning
    volatile int maxInt = INT_MAX;
    int overflowInt = maxInt + 1;
    std::cout << "INT_MAX:               " << maxInt      << std::endl;
    std::cout << "INT_MAX + 1:           " << overflowInt
              << "  <- overflow! voltou para INT_MIN" << std::endl;

    unsigned int underflowUnsigned = 0u - 1u; // underflow unsigned: wraparound garantido
    std::cout << "unsigned 0 - 1:        " << underflowUnsigned
              << "  <- underflow! voltou para UINT_MAX" << std::endl;

    // Escolha certa evita overflow
    long long populacao = (long long)INT_MAX + 1;  // sem overflow: cabe em long long
    std::cout << "long long INT_MAX + 1: " << populacao
              << "  <- sem overflow (tipo maior)" << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // CONST — VARIÁVEIS IMUTÁVEIS
    // =========================================================================
    // `const` declara que o valor NÃO pode ser alterado após a inicialização.
    // Tentar alterar uma const → ERRO DE COMPILAÇÃO (não deixa nem compilar).
    //
    // Por que usar const?
    //   1. Documenta a intenção: "este valor não deve mudar"
    //   2. O compilador protege: você não muda por acidente
    //   3. Permite otimizações pelo compilador
    //
    // CONVENÇÃO DE NOMENCLATURA:
    //   Constantes usam UPPER_SNAKE_CASE (tudo maiúsculo com underscores):
    //   MAX_VIDAS, PRECO_BASE, LARGURA_TELA, TAXA_JUROS
    //
    // DIFERENÇA DE #define (jeito antigo):
    //   #define MAX 10        → substituição de texto, sem tipo, sem escopo
    //   const int MAX = 10;   → tem tipo, tem escopo, é verificada pelo compilador
    //   Prefira sempre const (ou constexpr para valores em tempo de compilação).
    // =========================================================================

    std::cout << "--- CONST ---" << std::endl;

    const int    MAX_VIDAS        = 3;
    const double TAXA_DESCONTO    = 0.15;   // 15%
    const char   TECLA_SAIR       = 'Q';

    std::cout << "MAX_VIDAS:      " << MAX_VIDAS     << std::endl;
    std::cout << "TAXA_DESCONTO:  " << std::setprecision(0)
              << TAXA_DESCONTO * 100 << "%" << std::endl;
    std::cout << "TECLA_SAIR:     " << TECLA_SAIR    << std::endl;

    double precoOriginal  = 200.0;
    double precoFinal     = precoOriginal * (1.0 - TAXA_DESCONTO);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Preco R$ " << precoOriginal << " com desconto de "
              << TAXA_DESCONTO * 100 << "%% = R$ " << precoFinal << std::endl;

    // MAX_VIDAS = 5;   ← isto causaria ERRO DE COMPILACAO — const nao pode mudar
    std::cout << "Tentar MAX_VIDAS = 5 causaria erro de compilacao." << std::endl;
    std::cout << std::endl;


    // =========================================================================
    // FUNÇÃO COM TODOS OS TIPOS JUNTOS
    // =========================================================================
    std::cout << "=============================================" << std::endl;
    std::cout << "   FUNCAO USANDO TODOS OS TIPOS JUNTOS      " << std::endl;
    std::cout << "=============================================" << std::endl;
    demonstrarTodosTipos();
}


// =============================================================================
// FUNÇÃO INTERNA: demonstrarTodosTipos()
// Usa todos os tipos num contexto coeso (personagem de RPG)
// =============================================================================
static void demonstrarTodosTipos()
{
    bool         estaVivo            = true;
    bool         temEscudo           = false;
    char         classePersonagem    = 'G';    // G=Guerreiro, M=Mago, A=Arqueiro
    int          nivel               = 42;
    int          pontoDeVida         = 850;
    int          ouroNoInventario    = 15000;
    float        corVermelhaF        = 0.85f;  // componente RGB normalizado
    float        corVerdeF           = 0.20f;
    double       posicaoX            = -1234.567890123;
    double       danoCalculado       = 125.75 * 1.5;
    short        velocidade          = 320;
    short        defesaFisica        = 85;
    long long    totalDeXp           = 4500000000LL;
    long long    idNoServidor        = 7234567890123LL;
    unsigned int totalMonstrosMortos = 99999;
    unsigned int totalDePartidas     = 3210;

    std::cout << std::endl;
    std::cout << "=== STATUS DO PERSONAGEM ===" << std::endl;
    std::cout << std::boolalpha;

    std::cout << "[bool]      Esta vivo?       " << estaVivo         << std::endl;
    std::cout << "[bool]      Tem escudo?      " << temEscudo        << std::endl;
    std::cout << "[char]      Classe:          " << classePersonagem  << std::endl;
    std::cout << "[int]       Nivel:           " << nivel            << std::endl;
    std::cout << "[int]       Vida:            " << pontoDeVida      << std::endl;
    std::cout << "[int]       Ouro:            " << ouroNoInventario << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[float]     Cor RGB:         ("
              << corVermelhaF << ", " << corVerdeF << ", 0.10)" << std::endl;

    std::cout << std::setprecision(6);
    std::cout << "[double]    Posicao X:       " << posicaoX       << std::endl;
    std::cout << std::setprecision(2);
    std::cout << "[double]    Dano critico:    " << danoCalculado  << std::endl;

    std::cout << "[short]     Velocidade:      " << velocidade    << " u/s" << std::endl;
    std::cout << "[short]     Defesa fisica:   " << defesaFisica  << std::endl;
    std::cout << "[long long] XP total:        " << totalDeXp     << std::endl;
    std::cout << "[long long] ID no servidor:  " << idNoServidor  << std::endl;
    std::cout << "[unsigned]  Monstros mortos: " << totalMonstrosMortos << std::endl;
    std::cout << "[unsigned]  Partidas:        " << totalDePartidas     << std::endl;

    std::cout << std::endl;
    std::cout << "=== TAMANHOS ===" << std::endl;
    std::cout << "bool        = " << sizeof(bool)      << " byte(s)" << std::endl;
    std::cout << "char        = " << sizeof(char)      << " byte(s)" << std::endl;
    std::cout << "short       = " << sizeof(short)     << " byte(s)" << std::endl;
    std::cout << "int         = " << sizeof(int)       << " byte(s)" << std::endl;
    std::cout << "long long   = " << sizeof(long long) << " byte(s)" << std::endl;
    std::cout << "float       = " << sizeof(float)     << " byte(s)" << std::endl;
    std::cout << "double      = " << sizeof(double)    << " byte(s)" << std::endl;
}
