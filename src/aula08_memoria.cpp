#include <iostream>
#include <string>
#include <iomanip>
#include "aula08_memoria.h"

// ============================================================
// AULA 08 — MEMORIA E PONTEIROS AVANCADOS
// Topicos: 34-38
// Pre-requisitos: Aulas 00–07
// ============================================================

// ============================================================
// CLASSES E FUNCOES DE DEMONSTRACAO
// ============================================================

// --- Topico 36: static local ---
// Funcao com variavel local estatica — persiste entre chamadas.
static void contarChamadas()
{
    static int chamadas = 0;   // inicializado UMA UNICA VEZ na primeira chamada
    ++chamadas;
    std::cout << "  Chamada " << chamadas << std::endl;
}

// --- Topico 36: membro estatico de classe ---
class Instancia {
    static int contador;   // uma copia COMPARTILHADA por todos os objetos
public:
    Instancia()  { ++contador; }
    ~Instancia() { --contador; }
    static int obterContador() { return contador; }   // metodo estatico
};
int Instancia::contador = 0;   // definicao fora da classe (obrigatorio)

// --- Topico 38: this ---
class Retangulo {
    int largura;
    int altura;
public:
    Retangulo(int largura, int altura)
    {
        // this->membro resolve ambiguidade quando param e membro tem o mesmo nome.
        // Alternativa moderna: usar nomes diferentes ou member initializer list (Aula 07).
        this->largura = largura;
        this->altura  = altura;
    }

    // return *this permite ENCADEAMENTO de chamadas (method chaining / fluent interface).
    Retangulo& dobrar()
    {
        this->largura *= 2;
        this->altura  *= 2;
        return *this;
    }

    Retangulo& escalar(int fator)
    {
        this->largura *= fator;
        this->altura  *= fator;
        return *this;
    }

    void mostrar() const
    {
        std::cout << "  " << largura << " x " << altura << std::endl;
    }
};

// --- Fechamento: Configuracao fluente (usa todos os 5 conceitos) ---
class Configuracao {
    static int totalInstancias;   // static membro
    std::string chave;
    int         valor;

public:
    static int total() { return totalInstancias; }

    explicit Configuracao(const std::string& c, int v)
        : chave(c), valor(v)
    {
        ++totalInstancias;
        std::cout << "  [Configuracao criada: " << chave << "]" << std::endl;
    }

    ~Configuracao()
    {
        --totalInstancias;
        std::cout << "  [Configuracao destruida: " << chave << "]" << std::endl;
    }

    const std::string& obterChave() const { return chave; }   // const method
    int                obterValor() const { return valor; }   // const method

    Configuracao& setValor(int v) { this->valor = v; return *this; }
    Configuracao& dobrar()        { this->valor *= 2; return *this; }
};
int Configuracao::totalInstancias = 0;

// ============================================================
// TOPICO 34 — new e delete
// ============================================================
static void demonstrarNewDelete()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 34 — new e delete" << std::endl;
    std::cout << "============================" << std::endl;

    // A memoria de um programa tem duas regioes principais:
    //
    //   STACK (pilha): variaveis locais e automaticas.
    //     Alocadas/liberadas automaticamente ao entrar/sair do escopo.
    //     Rapida. Tamanho limitado (~1–8 MB).
    //
    //   HEAP: memoria dinamica.
    //     Alocada com new, liberada com delete.
    //     Voce e o responsavel pela liberacao — se esquecer = MEMORY LEAK.
    //     Tamanho limitado pela RAM disponivel.

    // --- new/delete para um unico objeto ---
    int* p = new int(42);   // aloca int no heap, inicializa com 42
    std::cout << "Heap  — valor: " << *p << "  endereco: " << p << std::endl;

    delete p;       // LIBERA a memoria — OBRIGATORIO para cada new
    p = nullptr;    // boa pratica: anula o ponteiro para evitar dangling pointer
    // *p;          // <- se nao tivesse nullptr, seria Undefined Behavior!

    // --- new[]/delete[] para arrays ---
    const int TAM = 5;
    int* arr = new int[TAM];   // aloca array de 5 ints no heap
    for (int i = 0; i < TAM; ++i) arr[i] = i * 10;

    std::cout << "Array dinamico: ";
    for (int i = 0; i < TAM; ++i) std::cout << arr[i] << " ";
    std::cout << std::endl;

    delete[] arr;   // delete[] para arrays — NUNCA delete simples!
    arr = nullptr;

    // --- new/delete para objetos ---
    std::string* texto = new std::string("mundo");
    std::cout << "String no heap: " << *texto << std::endl;
    delete texto;
    texto = nullptr;

    std::cout << "\nRegras de ouro:" << std::endl;
    std::cout << "  new    -> delete     (objeto unico)" << std::endl;
    std::cout << "  new[]  -> delete[]   (array)" << std::endl;
    std::cout << "  Sempre new/delete em par — nunca vaze memoria!" << std::endl;
    std::cout << "  Dica: prefira std::vector e std::unique_ptr (Aula futura)" << std::endl;
}

// ============================================================
// TOPICO 35 — const
// ============================================================
static void demonstrarConst()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 35 — const" << std::endl;
    std::cout << "============================" << std::endl;

    // const = "este valor nao pode ser modificado apos inicializacao".
    // O compilador garante — qualquer tentativa de mudanca = ERRO em compilacao.

    // --- const em variaveis ---
    const double PI = 3.14159265;
    // PI = 3.14;  // ERRO: assignment of read-only variable
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "PI = " << PI << std::endl;

    const int MAX_JOGADORES = 4;
    std::cout << "MAX_JOGADORES = " << MAX_JOGADORES << std::endl;

    // --- const& — referencia const (Aula 06 — recapitulo) ---
    // Eficiente (sem copia) e segura (nao modifica).
    std::string nome = "Alice";
    const std::string& refNome = nome;   // alias readonly
    // refNome = "Bob";   // ERRO
    std::cout << "nome via const&: " << refNome << std::endl;

    // --- const com ponteiros: 3 combinacoes ---
    std::cout << "\n--- const com ponteiros ---" << std::endl;
    int valor = 10;
    int outro = 20;

    // 1. const int* p  — ponteiro para const
    //    Pode mudar ONDE aponta (p = &outro).
    //    Nao pode mudar O QUE aponta (*p = 99). <- PROTEGE O VALOR
    const int* p1 = &valor;
    // *p1 = 99;   // ERRO
    p1 = &outro;   // OK
    std::cout << "const int* p1   (ptr para const): *p1 = " << *p1 << std::endl;

    // 2. int* const p  — ponteiro const
    //    Nao pode mudar ONDE aponta (p = &outro). <- PROTEGE O PONTEIRO
    //    Pode mudar O QUE aponta (*p = 99).
    int* const p2 = &valor;
    *p2 = 99;      // OK
    // p2 = &outro; // ERRO
    std::cout << "int* const p2   (ptr const):      valor = " << valor << std::endl;
    valor = 10;    // restaura

    // 3. const int* const p  — ponteiro const para const
    //    Nada pode mudar — protege tanto o ponteiro quanto o valor.
    const int* const p3 = &valor;
    // *p3 = 1;     // ERRO
    // p3 = &outro; // ERRO
    std::cout << "const int* const p3 (ambos const): *p3 = " << *p3 << std::endl;

    // --- Macete de leitura ---
    std::cout << "\nMacete: leia a declaracao da direita para a esquerda:" << std::endl;
    std::cout << "  const int* p1  -> 'p1 e ponteiro para int const'" << std::endl;
    std::cout << "  int* const p2  -> 'p2 e ponteiro const para int'" << std::endl;
    std::cout << "  const int* const p3 -> 'p3 e ponteiro const para int const'" << std::endl;
}

// ============================================================
// TOPICO 36 — static
// ============================================================
static void demonstrarStatic()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 36 — static" << std::endl;
    std::cout << "============================" << std::endl;

    // static tem 3 usos em C++:
    //   1. Variavel local estatica — persiste entre chamadas da funcao
    //   2. Membro estatico de classe — compartilhado por todos os objetos
    //   3. Linkage interno (Aulas anteriores: static void demonstrarX())

    // --- 1. Variavel local estatica ---
    // Inicializada UMA UNICA VEZ (na primeira execucao da funcao).
    // Nas chamadas seguintes, a variavel ja existe e mantem o valor anterior.
    std::cout << "--- Variavel local estatica ---" << std::endl;
    std::cout << "  static int chamadas = 0;  // inicializado so uma vez" << std::endl;
    contarChamadas();
    contarChamadas();
    contarChamadas();

    // --- 2. Membro estatico de classe ---
    // Declarado na classe com 'static'. Definido uma vez fora da classe.
    // Uma UNICA copia — compartilhada por todos os objetos.
    // Acessado via NomeClasse::membro (nao via objeto).
    std::cout << "\n--- Membro estatico de classe ---" << std::endl;
    std::cout << "Antes:  Instancia::obterContador() = " << Instancia::obterContador() << std::endl;
    {
        Instancia a;
        Instancia b;
        std::cout << "Dois criados:   " << Instancia::obterContador() << std::endl;
        {
            Instancia c;
            std::cout << "Terceiro criado: " << Instancia::obterContador() << std::endl;
        }   // c destruido aqui
        std::cout << "Terceiro destruido: " << Instancia::obterContador() << std::endl;
    }   // a e b destruidos aqui
    std::cout << "Todos destruidos: " << Instancia::obterContador() << std::endl;

    std::cout << "\nUsos tipicos de static membro: contadores, singletons, constantes." << std::endl;
}

// ============================================================
// TOPICO 37 — sizeof
// ============================================================
static void demonstrarSizeof()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 37 — sizeof" << std::endl;
    std::cout << "============================" << std::endl;

    // sizeof: operador que retorna o tamanho em BYTES de um tipo ou expressao.
    // Avaliado em TEMPO DE COMPILACAO — zero custo em execucao.
    // Retorna size_t (inteiro sem sinal).

    std::cout << "Tipos primitivos (plataforma 64-bit tipica):" << std::endl;
    std::cout << "  sizeof(char)      = " << sizeof(char)      << " byte"  << std::endl;
    std::cout << "  sizeof(short)     = " << sizeof(short)     << " bytes" << std::endl;
    std::cout << "  sizeof(int)       = " << sizeof(int)       << " bytes" << std::endl;
    std::cout << "  sizeof(long)      = " << sizeof(long)      << " bytes" << std::endl;
    std::cout << "  sizeof(long long) = " << sizeof(long long) << " bytes" << std::endl;
    std::cout << "  sizeof(float)     = " << sizeof(float)     << " bytes" << std::endl;
    std::cout << "  sizeof(double)    = " << sizeof(double)    << " bytes" << std::endl;
    std::cout << "  sizeof(bool)      = " << sizeof(bool)      << " byte"  << std::endl;
    std::cout << "  sizeof(void*)     = " << sizeof(void*)     << " bytes (ponteiro 64-bit)" << std::endl;

    // sizeof com arrays C-style (truque ja visto nas Aulas 02 e 04)
    int arr[10] = {};
    std::cout << "\nArray C-style int[10]:" << std::endl;
    std::cout << "  sizeof(arr)                    = " << sizeof(arr)                   << " bytes" << std::endl;
    std::cout << "  sizeof(arr[0])                 = " << sizeof(arr[0])                << " bytes" << std::endl;
    std::cout << "  sizeof(arr) / sizeof(arr[0])   = " << sizeof(arr)/sizeof(arr[0])    << " elementos" << std::endl;

    // Armadilha: sizeof em PONTEIRO nao da o tamanho do array apontado
    int* p = arr;
    std::cout << "\n--- Armadilha: ponteiro vs array ---" << std::endl;
    std::cout << "  sizeof(arr)  = " << sizeof(arr) << " bytes  <- correto (array local)" << std::endl;
    std::cout << "  sizeof(p)    = " << sizeof(p)   << " bytes  <- TAMANHO DO PONTEIRO, nao do array!" << std::endl;
    std::cout << "  Por isso: prefira std::array.size() ou std::vector.size() (Aula 05)." << std::endl;

    // sizeof de struct (pode ter padding para alinhamento)
    struct Ponto { int x; int y; };
    std::cout << "\nstruct Ponto {int x; int y;}:" << std::endl;
    std::cout << "  sizeof(Ponto) = " << sizeof(Ponto) << " bytes (2 ints = 8, sem padding aqui)" << std::endl;
}

// ============================================================
// TOPICO 38 — this
// ============================================================
static void demonstrarThis()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 38 — this" << std::endl;
    std::cout << "============================" << std::endl;

    // this: ponteiro implicito disponivel em todo metodo nao-estatico.
    // Aponta para o objeto que chamou o metodo.
    // Tipo: NomeClasse* const this
    //
    // Dois usos principais:
    //   1. Resolver ambiguidade: this->nome = nome  (param e membro com mesmo nome)
    //   2. return *this: habilita encadeamento de chamadas (method chaining)

    Retangulo r(5, 3);
    std::cout << "Inicial:" << std::endl;
    r.mostrar();

    // Method chaining: cada chamada retorna *this (referencia ao proprio objeto)
    r.dobrar().dobrar();
    std::cout << "Apos .dobrar().dobrar():" << std::endl;
    r.mostrar();

    Retangulo r2(2, 3);
    r2.escalar(3).dobrar().escalar(2);
    std::cout << "r2 apos .escalar(3).dobrar().escalar(2):" << std::endl;
    r2.mostrar();

    std::cout << "\nthis->membro : resolve ambiguidade param/membro de mesmo nome." << std::endl;
    std::cout << "return *this : permite r.a().b().c() (fluent interface / builder pattern)." << std::endl;
    std::cout << "static nao tem this — nao ha objeto associado ao metodo estatico." << std::endl;
}

// ============================================================
// FECHAMENTO — Configuracao fluente (todos os 5 conceitos)
// ============================================================
static void demonstrarFechamento()
{
    std::cout << "\n======================================" << std::endl;
    std::cout << " FECHAMENTO — Configuracao fluente" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "(new/delete + const + static + sizeof + this)" << std::endl;

    // static: total de instancias vivas
    std::cout << "\nTotal inicial: " << Configuracao::total() << std::endl;

    // new: alocacao no heap
    Configuracao* cfg1 = new Configuracao("timeout", 30);
    Configuracao* cfg2 = new Configuracao("retries", 3);
    std::cout << "Total apos 2 new: " << Configuracao::total() << std::endl;

    // const: acesso somente leitura ao objeto
    const Configuracao* leitura = cfg1;
    std::cout << "Leitura (const*): "
              << leitura->obterChave() << " = " << leitura->obterValor() << std::endl;

    // this (method chaining): encadeia modificacoes fluentemente
    cfg1->setValor(10).dobrar().dobrar();
    std::cout << "cfg1 apos .setValor(10).dobrar().dobrar(): " << cfg1->obterValor() << std::endl;

    // sizeof: tamanho do objeto vs do ponteiro
    std::cout << "\nsizeof(Configuracao) = " << sizeof(Configuracao) << " bytes" << std::endl;
    std::cout << "sizeof(cfg1)         = " << sizeof(cfg1) << " bytes (ponteiro — nao o objeto!)" << std::endl;

    // delete: libera heap — OBRIGATORIO
    delete cfg1; cfg1 = nullptr;
    delete cfg2; cfg2 = nullptr;
    std::cout << "\nTotal apos 2 delete: " << Configuracao::total() << std::endl;

    // Stack: destruida automaticamente ao sair do escopo
    std::cout << "\nCriando cfg3 no stack..." << std::endl;
    {
        Configuracao cfg3("debug", 1);
        std::cout << "  Total com cfg3: " << Configuracao::total() << std::endl;
    }   // cfg3 destruida aqui (destructor automatico)
    std::cout << "Apos escopo: total = " << Configuracao::total() << std::endl;

    std::cout << "\nTodos os conceitos da Aula 08 em acao!" << std::endl;
}

// ============================================================
// PONTO DE ENTRADA DA AULA 08
// ============================================================
void rodarAula08()
{
    std::cout << "\n================================" << std::endl;
    std::cout << " AULA 08 - MEMORIA E PONTEIROS" << std::endl;
    std::cout << "================================\n" << std::endl;

    demonstrarNewDelete();
    demonstrarConst();
    demonstrarStatic();
    demonstrarSizeof();
    demonstrarThis();
    demonstrarFechamento();

    std::cout << "\n================================" << std::endl;
    std::cout << " FIM DA AULA 08" << std::endl;
    std::cout << "================================\n" << std::endl;
}
