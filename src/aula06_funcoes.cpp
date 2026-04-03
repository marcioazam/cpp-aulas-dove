#include <iostream>
#include <string>
#include <iomanip>
#include "aula06_funcoes.h"

// ============================================================
// AULA 06 — FUNCOES
// Topicos: 20-26
// Pre-requisitos: Aulas 00–05
// ============================================================

// ============================================================
// FUNCOES HELPER — definidas ANTES das funcoes que as usam.
// Em projetos reais, as declaracoes (prototipos) ficam em .h
// e as definicoes ficam em .cpp — essa separacao vira na Aula 08.
// ============================================================

static int somar(int a, int b)
{
    return a + b;
}

static void imprimirDivisor()
{
    std::cout << "----------------------------" << std::endl;
}

static int maximo(int a, int b)
{
    return (a > b) ? a : b;
}

static bool ehPar(int n)
{
    return (n % 2 == 0);
}

// Topico 23 — por valor: n e uma COPIA do argumento
static void dobrarPorValor(int n)
{
    n *= 2;
    std::cout << "  [dentro dobrarPorValor]  n = " << n << std::endl;
    // alterou a copia — o chamador nao e afetado
}

// Topico 24 — por referencia: n e um ALIAS do argumento
static void dobrarPorRef(int& n)
{
    n *= 2;
    std::cout << "  [dentro dobrarPorRef]    n = " << n << std::endl;
    // alterou a variavel ORIGINAL do chamador
}

static void trocar(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Topico 25 — inline: sugestao ao compilador para inserir o corpo no local da chamada
static inline int quadrado(int x) { return x * x; }
static inline int cubo(int x)     { return x * x * x; }

// Topico 26 — sobrecarga: mesmo nome, diferentes assinaturas
static int    calcular(int    a, int    b) { return a + b; }
static double calcular(double a, double b) { return a + b; }

// Fechamento — retorna dois valores via referencias
static void divEMod(int n, int d, int& quociente, int& resto)
{
    quociente = n / d;
    resto     = n % d;
}

// ============================================================
// TOPICO 20 — Declaracao, definicao e chamada
// ============================================================
static void demonstrarDeclaracao()
{
    std::cout << "\n================================" << std::endl;
    std::cout << " TOPICO 20 — Funcoes: conceito" << std::endl;
    std::cout << "================================" << std::endl;

    // Analogia: receita de bolo.
    //   Declaracao  = titulo + lista de ingredientes (assinatura)
    //   Definicao   = modo de preparo (corpo com {})
    //   Chamada     = cozinhar o bolo (executar o codigo)
    //
    // Estrutura:
    //   tipo_retorno nome(tipo param1, tipo param2) { ... corpo ... }
    //
    //   int somar(int a, int b) {    <- declaracao + definicao juntas
    //       return a + b;
    //   }
    //
    // Chamada: executa a funcao e devolve o valor de retorno.
    //   int r = somar(3, 4);         <- 3 e 4 sao os ARGUMENTOS

    std::cout << "somar(3, 4)     = " << somar(3, 4)             << std::endl;
    std::cout << "somar(100, 200) = " << somar(100, 200)         << std::endl;
    std::cout << "maximo(10, 20)  = " << maximo(10, 20)          << std::endl;
    std::cout << "ehPar(7)        = " << (ehPar(7) ? "sim" : "nao") << std::endl;
    std::cout << "ehPar(8)        = " << (ehPar(8) ? "sim" : "nao") << std::endl;

    std::cout << "\nVantagens de funcoes:" << std::endl;
    std::cout << "  Reuso       — escreve uma vez, usa muitas vezes" << std::endl;
    std::cout << "  Legibilidade— somar(a, b) diz o que faz" << std::endl;
    std::cout << "  Manutencao  — muda em um lugar, correto em todos" << std::endl;
    std::cout << "  Testabilidade— cada funcao pode ser testada isolada" << std::endl;
}

// ============================================================
// TOPICO 21 — void: funcoes sem retorno
// ============================================================
static void demonstrarVoid()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 21 — void" << std::endl;
    std::cout << "============================" << std::endl;

    // void = "sem valor de retorno"
    // Usada quando a funcao executa uma ACAO mas nao precisa devolver nada.
    //
    //   static void imprimirDivisor() {
    //       std::cout << "---" << std::endl;
    //       // sem return — compilador adiciona return; implicito no final
    //   }
    //
    // Nao e possivel: int x = imprimirDivisor();  <- ERRO de compilacao
    // void nao e um valor; e a ausencia de valor.

    std::cout << "Chamando imprimirDivisor():" << std::endl;
    imprimirDivisor();
    std::cout << "Funcoes void sao usadas para:" << std::endl;
    std::cout << "  - Imprimir na tela" << std::endl;
    std::cout << "  - Modificar variaveis por referencia" << std::endl;
    std::cout << "  - Efeitos colaterais (salvar arquivo, enviar dado...)" << std::endl;
    std::cout << "\n  return; (sem valor) pode encerrar um void antecipadamente." << std::endl;
    std::cout << "  Ex: if (erro) return;  // early exit" << std::endl;
}

// ============================================================
// TOPICO 22 — return: retornando valores e early exit
// ============================================================
static void demonstrarReturn()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 22 — return" << std::endl;
    std::cout << "============================" << std::endl;

    // return faz DUAS coisas:
    //   1. Encerra a execucao da funcao IMEDIATAMENTE
    //   2. Devolve um valor ao chamador (se nao for void)
    //
    //   int maximo(int a, int b) {
    //       return (a > b) ? a : b;   // encerra e retorna o maior
    //   }
    //
    // Early return — util para guards (validacoes no inicio):
    //
    //   bool validarIdade(int idade) {
    //       if (idade < 0)   return false;  // encerra imediatamente se invalido
    //       if (idade > 150) return false;
    //       return true;                    // so chega aqui se valido
    //   }
    //
    // Regras:
    //   - Toda funcao nao-void DEVE retornar valor em todos os caminhos
    //   - void pode ter return; (sem valor) ou simplesmente terminar
    //   - Codigo apos return nunca e executado (dead code — compilador avisa)

    std::cout << "somar(3, 4)   retorna: " << somar(3, 4)   << std::endl;
    std::cout << "maximo(7, 3)  retorna: " << maximo(7, 3)  << std::endl;
    std::cout << "ehPar(10)     retorna: " << (ehPar(10) ? "true" : "false") << std::endl;
    std::cout << "ehPar(11)     retorna: " << (ehPar(11) ? "true" : "false") << std::endl;
}

// ============================================================
// TOPICO 23 — Parametros por valor
// ============================================================
static void demonstrarPorValor()
{
    std::cout << "\n====================================" << std::endl;
    std::cout << " TOPICO 23 — Parametros por valor" << std::endl;
    std::cout << "====================================" << std::endl;

    // Analogia: fotocopiadora — voce entrega uma COPIA do documento.
    // A funcao recebe a copia. O original nao e tocado.
    //
    //   static void dobrarPorValor(int n) {   // n e uma COPIA
    //       n *= 2;   // muda a copia — original intacto
    //   }

    int numero = 10;
    std::cout << "Antes de dobrarPorValor: numero = " << numero << std::endl;
    dobrarPorValor(numero);
    std::cout << "Apos  de dobrarPorValor: numero = " << numero << "  <- nao mudou!" << std::endl;

    std::cout << "\nPor valor e o PADRAO do C++." << std::endl;
    std::cout << "Use quando a funcao so precisa LER o valor (sem modificar)." << std::endl;
    std::cout << "Cuidado: copiar objetos grandes (struct, string longa) pode ser lento." << std::endl;
    std::cout << "  -> Solucao: const T& (referencia const, sem copia, sem modificar)." << std::endl;
}

// ============================================================
// TOPICO 24 — Parametros por referencia
// ============================================================
static void demonstrarPorReferencia()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " TOPICO 24 — Parametros por referencia" << std::endl;
    std::cout << "========================================" << std::endl;

    // Analogia: chave da casa — voce entrega a chave REAL.
    // Quem recebe acessa (e modifica) a casa original.
    //
    //   static void dobrarPorRef(int& n) {    // & = referencia, alias
    //       n *= 2;   // muda a variavel ORIGINAL do chamador
    //   }

    int numero = 10;
    std::cout << "Antes de dobrarPorRef:   numero = " << numero << std::endl;
    dobrarPorRef(numero);
    std::cout << "Apos  de dobrarPorRef:   numero = " << numero << "  <- mudou!" << std::endl;

    // trocar — so e possivel com referencias (ou ponteiros)
    int a = 3, b = 7;
    std::cout << "\nAntes de trocar: a = " << a << ", b = " << b << std::endl;
    trocar(a, b);
    std::cout << "Apos  de trocar: a = " << a << ", b = " << b << std::endl;

    std::cout << "\n--- Resumo: valor vs referencia ---" << std::endl;
    std::cout << "  int n          — por valor   : copia, chamador nao muda" << std::endl;
    std::cout << "  int& n         — por ref     : alias, chamador PODE mudar" << std::endl;
    std::cout << "  const int& n   — const ref   : alias sem copia, nao modifica" << std::endl;
    std::cout << "\n  Use & quando precisar MODIFICAR o original." << std::endl;
    std::cout << "  Use const& quando o objeto e grande e nao precisa mudar." << std::endl;
}

// ============================================================
// TOPICO 25 — inline
// ============================================================
static void demonstrarInline()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 25 — inline" << std::endl;
    std::cout << "============================" << std::endl;

    // Analogia: copiar a receita no livro vs ir ate a cozinha toda vez.
    // inline "cola" o corpo da funcao no local da chamada — elimina a "viagem".
    //
    //   static inline int quadrado(int x) { return x * x; }
    //
    // Sem inline (chamada normal):
    //   1. Salva registradores (push)
    //   2. Pula para o endereco da funcao
    //   3. Executa
    //   4. Restaura registradores (pop) e retorna
    //
    // Com inline (se o compilador aceitar a sugestao):
    //   O codigo e inserido diretamente, sem o custo do push/pop.
    //
    // IMPORTANTE: inline e uma SUGESTAO. O compilador pode ignorar.
    // Compiladores modernos (-O2/-O3) aplicam inlining automaticamente.

    std::cout << "quadrado(4)  = " << quadrado(4)  << std::endl;
    std::cout << "quadrado(7)  = " << quadrado(7)  << std::endl;
    std::cout << "cubo(3)      = " << cubo(3)      << std::endl;
    std::cout << "cubo(5)      = " << cubo(5)      << std::endl;

    std::cout << "\nRegras praticas:" << std::endl;
    std::cout << "  Use inline em funcoes PEQUENAS (1-3 linhas)" << std::endl;
    std::cout << "  Nao use em funcoes grandes — aumenta o tamanho do executavel" << std::endl;
    std::cout << "  inline em .h permite multiplas definicoes sem conflito no linker" << std::endl;
}

// ============================================================
// TOPICO 26 — Sobrecarga (function overloading)
// ============================================================
static void demonstrarSobrecarga()
{
    std::cout << "\n================================" << std::endl;
    std::cout << " TOPICO 26 — Sobrecarga" << std::endl;
    std::cout << "================================" << std::endl;

    // Analogia: verbo "ligar" — mesmo nome, contexto diferente.
    // Ligar a luz, ligar para alguem, ligar o carro.
    //
    // Em C++: mesma funcao, diferentes ASSINATURAS (tipo/quantidade de params).
    // O compilador escolhe qual versao usar pelos tipos dos argumentos.
    //
    //   static int    calcular(int    a, int    b) { return a + b; }
    //   static double calcular(double a, double b) { return a + b; }

    int    r1 = calcular(3, 4);
    double r2 = calcular(3.5, 4.2);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "calcular(3, 4)       = " << r1 << "  (versao int)"    << std::endl;
    std::cout << "calcular(3.5, 4.2)   = " << r2 << "  (versao double)" << std::endl;

    std::cout << "\nRegras de sobrecarga:" << std::endl;
    std::cout << "  O QUE diferencia : tipo e/ou quantidade de parametros" << std::endl;
    std::cout << "  O QUE NAO        : tipo de retorno (nao faz parte da assinatura)" << std::endl;
    std::cout << "  Quando resolver  : em tempo de COMPILACAO (nao em execucao)" << std::endl;

    // Mostra overloading com diferente numero de parametros seria tambem valido,
    // mas tipo de retorno sozinho NAO e suficiente para diferenciar:
    //   int    calcular(int a, int b) { return a + b; }
    //   double calcular(int a, int b) { return a + b; }  <- ERRO! mesma assinatura
}

// ============================================================
// FECHAMENTO — Calculadora (usa todos os conceitos juntos)
// ============================================================
static void demonstrarCalculadora()
{
    std::cout << "\n=====================================" << std::endl;
    std::cout << " FECHAMENTO — Calculadora" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "(declaracao + void + return + valor + ref + inline + sobrecarga)" << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    // Sobrecarga: calcular int vs double
    std::cout << "\ncalcular(10, 3)      = " << calcular(10, 3)     << "  (int)"    << std::endl;
    std::cout << "calcular(10.5, 3.3)  = " << calcular(10.5, 3.3) << "  (double)" << std::endl;

    // Referencia: divEMod retorna dois valores simultaneamente
    int quociente = 0;
    int resto     = 0;
    divEMod(17, 5, quociente, resto);
    std::cout << "\n17 dividido por 5:" << std::endl;
    std::cout << "  Quociente : " << quociente << std::endl;
    std::cout << "  Resto     : " << resto     << std::endl;

    divEMod(100, 7, quociente, resto);
    std::cout << "100 dividido por 7:" << std::endl;
    std::cout << "  Quociente : " << quociente << std::endl;
    std::cout << "  Resto     : " << resto     << std::endl;

    // inline em loop — sem overhead de chamada
    std::cout << "\nQuadrados (inline quadrado()):" << std::endl;
    for (int i = 1; i <= 6; ++i) {
        std::cout << "  " << i << "^2 = " << quadrado(i)
                  << "    " << i << "^3 = " << cubo(i) << std::endl;
    }

    std::cout << "\nTodos os conceitos da Aula 06 em acao!" << std::endl;
}

// ============================================================
// PONTO DE ENTRADA DA AULA 06
// ============================================================
void rodarAula06()
{
    std::cout << "\n================================" << std::endl;
    std::cout << " AULA 06 - FUNCOES" << std::endl;
    std::cout << "================================\n" << std::endl;

    demonstrarDeclaracao();
    demonstrarVoid();
    demonstrarReturn();
    demonstrarPorValor();
    demonstrarPorReferencia();
    demonstrarInline();
    demonstrarSobrecarga();
    demonstrarCalculadora();

    std::cout << "\n================================" << std::endl;
    std::cout << " FIM DA AULA 06" << std::endl;
    std::cout << "================================\n" << std::endl;
}
