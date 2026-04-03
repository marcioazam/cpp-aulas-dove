#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "aula07_oop.h"

// ============================================================
// AULA 07 — ORIENTACAO A OBJETOS (OOP)
// Topicos: 27-33
// Pre-requisitos: Aulas 00–06
// ============================================================

// ============================================================
// CLASSES DE DEMONSTRACAO — definidas no escopo do arquivo
// ============================================================

// ============================================================
// TOPICO 27 — class vs struct
// ============================================================

// struct (Aula 05): membros PUBLICOS por padrao.
// Usa-se para agrupar dados simples (sem logica interna).
struct PontoXY {
    double x = 0.0;
    double y = 0.0;
};

// class: membros PRIVADOS por padrao.
// Usa-se quando o objeto tem LOGICA que protege o estado interno.
class ContadorSimples {
    int valor;           // private por padrao — so a propria classe acessa
public:
    ContadorSimples() : valor(0) {}   // constructor (Topico 29)
    void incrementar()       { ++valor; }
    void decrementar()       { if (valor > 0) --valor; }
    int  obter()       const { return valor; }  // const: nao modifica o objeto
    void zerar()             { valor = 0; }
};

// ============================================================
// TOPICO 28 — public / private / protected
// TOPICO 29 — Constructor e destructor
// TOPICO 30 — Heranca
// ============================================================

class ContaBancaria {
private:
    double      saldo;      // so a propria classe acessa
    std::string titular;

protected:
    double taxaJuros = 0.02;  // classes derivadas PODEM acessar

public:
    // Constructor: inicializa o objeto.
    // Member initializer list (:) e mais eficiente que atribuicao no corpo.
    ContaBancaria(std::string t, double s)
        : saldo(s), titular(t)
    {
        std::cout << "  [ContaBancaria criada para " << titular << "]" << std::endl;
    }

    // Destructor: chamado automaticamente ao sair do escopo.
    ~ContaBancaria()
    {
        std::cout << "  [ContaBancaria destruida para " << titular << "]" << std::endl;
    }

    void depositar(double valor)
    {
        saldo += valor;
    }

    bool sacar(double valor)
    {
        if (valor > saldo) return false;  // early return — sem saldo
        saldo -= valor;
        return true;
    }

    double      obterSaldo()   const { return saldo;   }
    std::string obterTitular() const { return titular; }
};

// Heranca: ContaPoupanca REUTILIZA ContaBancaria e adiciona renderJuros().
class ContaPoupanca : public ContaBancaria {
public:
    ContaPoupanca(std::string t, double s)
        : ContaBancaria(t, s)  // chama o constructor da base
    {}

    void renderJuros()
    {
        double rendimento = obterSaldo() * taxaJuros;  // taxaJuros = protected
        depositar(rendimento);
        std::cout << "  Juros rendidos: " << std::fixed << std::setprecision(2)
                  << rendimento << std::endl;
    }
};

// ============================================================
// TOPICO 31 — virtual e override (polimorfismo)
// ============================================================

// Forma e uma classe BASE ABSTRATA — define uma interface comum.
// Qualquer classe que herdar de Forma DEVE implementar calcularArea().
class Forma {
public:
    // = 0 torna o metodo PURO VIRTUAL — Forma nao pode ser instanciada diretamente.
    virtual double      calcularArea()   const = 0;
    virtual std::string descricao()      const = 0;

    // Destructor VIRTUAL e OBRIGATORIO em hierarquias com polimorfismo.
    // Sem ele, delete em um ponteiro Forma* nao chamaria o destructor correto.
    virtual ~Forma() {}
};

// Circulo herda de Forma e SOBRESCREVE os metodos virtuais com override.
// override avisa o compilador: "este metodo deve existir na base" — evita erros de typo.
class Circulo : public Forma {
    double raio;
public:
    explicit Circulo(double r) : raio(r) {}

    double calcularArea() const override
    {
        return 3.14159265 * raio * raio;
    }

    std::string descricao() const override { return "Circulo"; }
};

class Retangulo : public Forma {
    double largura, altura;
public:
    Retangulo(double l, double a) : largura(l), altura(a) {}

    double calcularArea() const override
    {
        return largura * altura;
    }

    std::string descricao() const override { return "Retangulo"; }
};

class Triangulo : public Forma {
    double base, altura;
public:
    Triangulo(double b, double a) : base(b), altura(a) {}

    double calcularArea() const override
    {
        return (base * altura) / 2.0;
    }

    std::string descricao() const override { return "Triangulo"; }
};

// ============================================================
// TOPICO 32 — friend
// ============================================================

class Cofre {
    int combinacao;   // private — ningem fora da classe acessa normalmente
public:
    explicit Cofre(int c) : combinacao(c) {}

    // Declara auditarCofre como amiga: ela ganha acesso a membros privados.
    friend void auditarCofre(const Cofre& c);
};

// Funcao amiga: acessa Cofre::combinacao mesmo sendo private.
void auditarCofre(const Cofre& c)
{
    std::cout << "  Auditoria (acesso via friend): combinacao = "
              << c.combinacao << std::endl;
}

// ============================================================
// TOPICO 33 — explicit
// ============================================================

class Temperatura {
    double celsius;
public:
    // explicit: bloqueia conversao implicita do tipo double para Temperatura.
    // Sem explicit: Temperatura t = 36.5; funcionaria silenciosamente.
    // Com explicit: so Temperatura t(36.5); ou Temperatura t{36.5}; sao validos.
    explicit Temperatura(double c) : celsius(c) {}

    double obter() const { return celsius; }
};

// ============================================================
// FUNCOES DE TOPICO
// ============================================================

static void demonstrarClass()
{
    std::cout << "\n===============================" << std::endl;
    std::cout << " TOPICO 27 — class vs struct" << std::endl;
    std::cout << "===============================" << std::endl;

    // struct — membros publicos: ideal para dados simples sem logica
    PontoXY p;
    p.x = 3.0;
    p.y = 4.0;
    std::cout << "PontoXY (struct): x=" << p.x << " y=" << p.y << std::endl;

    // class — membros privados: ideal quando o objeto tem estado e logica
    ContadorSimples cont;
    cont.incrementar();
    cont.incrementar();
    cont.incrementar();
    std::cout << "ContadorSimples (class): " << cont.obter() << std::endl;
    cont.decrementar();
    std::cout << "Apos decrementar: "        << cont.obter() << std::endl;

    // cont.valor = 99;   // <- ERRO de compilacao: 'valor' e private
    // So se acessa por metodos publicos (interface controlada).

    std::cout << "\n--- class vs struct ---" << std::endl;
    std::cout << "struct: padrao PUBLIC  — ideal para dados simples (PontoXY, Jogador...)" << std::endl;
    std::cout << "class : padrao PRIVATE — ideal quando ha logica protegendo o estado"     << std::endl;
    std::cout << "Em C++, struct e class sao quase identicos — so diferem no padrao de acesso." << std::endl;
}

static void demonstrarAcesso()
{
    std::cout << "\n=======================================" << std::endl;
    std::cout << " TOPICO 28 — public/private/protected" << std::endl;
    std::cout << "=======================================" << std::endl;

    // private  : so a propria classe acessa
    // public   : qualquer codigo acessa
    // protected: a classe e suas derivadas acessam (Topico 30)

    std::cout << "Criando conta..." << std::endl;
    ContaBancaria conta("Alice", 1000.0);

    // conta.saldo = 9999;    // ERRO: saldo e private
    // conta.titular = "Hack"; // ERRO: titular e private

    // Acesso via metodos publicos (interface controlada):
    std::cout << "Titular: " << conta.obterTitular()                          << std::endl;
    std::cout << "Saldo  : " << std::fixed << std::setprecision(2)
                             << conta.obterSaldo()                            << std::endl;

    conta.depositar(500.0);
    std::cout << "Apos depositar 500.0: " << conta.obterSaldo()               << std::endl;

    bool sacou = conta.sacar(200.0);
    std::cout << "Saque 200.0: " << (sacou ? "ok" : "sem saldo")              << std::endl;
    std::cout << "Saldo final: " << conta.obterSaldo()                        << std::endl;

    bool semSaldo = conta.sacar(9999.0);
    std::cout << "Saque 9999.0: " << (semSaldo ? "ok" : "recusado (sem saldo)") << std::endl;

    std::cout << "\nEncapsulamento: o estado interno (saldo) so muda por metodos controlados." << std::endl;
    std::cout << "Impossivel por acidente colocar saldo negativo ou zero sem validacao." << std::endl;

    // destructor chamado automaticamente quando conta sai do escopo
}

static void demonstrarConstructor()
{
    std::cout << "\n===================================" << std::endl;
    std::cout << " TOPICO 29 — Constructor/Destructor" << std::endl;
    std::cout << "===================================" << std::endl;

    // Constructor: executado automaticamente ao criar o objeto.
    // Garante que o objeto comeca em estado valido.
    //
    // Member initializer list (recomendado):
    //   ContaBancaria(string t, double s) : saldo(s), titular(t) {}
    //   Mais eficiente que: saldo = s; titular = t; (evita construcao dupla)
    //
    // Destructor: executado automaticamente ao sair do escopo ou ao deletar.
    // Ideal para liberar recursos (arquivo, conexao, memoria alocada).
    //
    // RAII (Resource Acquisition Is Initialization):
    //   adquirir recurso no constructor, liberar no destructor.
    //   O objeto garante que o recurso sempre sera liberado.

    std::cout << "Criando c1 (ContaBancaria no escopo)..." << std::endl;
    {
        ContaBancaria c1("Bob", 500.0);
        c1.depositar(100.0);
        std::cout << "  Saldo: " << c1.obterSaldo() << std::endl;
        std::cout << "  [saindo do bloco — destructor chamado automaticamente]" << std::endl;
    }  // <- ~ContaBancaria() chamado aqui

    std::cout << "\n  Destructor garante limpeza sem precisar de codigo extra." << std::endl;
}

static void demonstrarHeranca()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 30 — Heranca" << std::endl;
    std::cout << "============================" << std::endl;

    // Heranca: ContaPoupanca HERDA tudo de ContaBancaria.
    // Reutiliza depositar(), sacar(), obterSaldo() sem reescrever.
    // Adiciona renderJuros() especifico de poupanca.
    //
    //   class ContaPoupanca : public ContaBancaria { ... };
    //   O construtor chama ContaBancaria(t, s) via initializer list.

    std::cout << "Criando poupanca..." << std::endl;
    ContaPoupanca poupanca("Carol", 1000.0);

    poupanca.depositar(500.0);           // herdado de ContaBancaria
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Saldo inicial: " << poupanca.obterSaldo() << std::endl;

    poupanca.renderJuros();              // especifico de ContaPoupanca
    std::cout << "Saldo com juros: "    << poupanca.obterSaldo() << std::endl;

    poupanca.renderJuros();
    std::cout << "Saldo apos 2x juros: " << poupanca.obterSaldo() << std::endl;

    std::cout << "\nHeranca = reutilizacao de codigo + extensao de comportamento." << std::endl;
    std::cout << "ContaPoupanca tem tudo de ContaBancaria + renderJuros()." << std::endl;

    // destructor de ContaPoupanca e ContaBancaria chamados ao sair do escopo
}

static void demonstrarVirtualOverride()
{
    std::cout << "\n======================================" << std::endl;
    std::cout << " TOPICO 31 — virtual e override" << std::endl;
    std::cout << "======================================" << std::endl;

    // virtual + override = POLIMORFISMO.
    // O programa decide em TEMPO DE EXECUCAO qual versao chamar,
    // baseado no tipo REAL do objeto — nao no tipo do ponteiro.
    //
    // Sem virtual: Forma* f = &circulo; f->calcularArea()  <- chamaria Forma::calcularArea()
    // Com virtual: f->calcularArea()  <- chama Circulo::calcularArea() (correto!)
    //
    // -> (seta): acessa membro de um objeto via PONTEIRO.
    //   f->calcularArea()   equivale a   (*f).calcularArea()

    Circulo   c(5.0);
    Retangulo r(3.0, 4.0);
    Triangulo t(6.0, 8.0);

    // std::vector de ponteiros para a BASE — polimorfismo em acao
    std::vector<Forma*> formas;
    formas.push_back(&c);    // ponteiro para objeto no stack — nao precisa de delete
    formas.push_back(&r);
    formas.push_back(&t);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Calculando areas via ponteiro Forma*:" << std::endl;
    for (Forma* f : formas) {
        std::cout << "  " << f->descricao()
                  << ": area = " << f->calcularArea() << std::endl;
    }
    // c, r, t sao destruidos automaticamente (stack) — sem new/delete aqui

    std::cout << "\nSem virtual: todos chamariam Forma::calcularArea() (errado)." << std::endl;
    std::cout << "Com virtual: cada um chama sua propria versao (polimorfismo)." << std::endl;
    std::cout << "override: compilador verifica que o metodo existe na base (seguranca extra)." << std::endl;
    std::cout << "~Forma() virtual: garante destructor correto ao deletar via Forma*." << std::endl;
}

static void demonstrarFriend()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 32 — friend" << std::endl;
    std::cout << "============================" << std::endl;

    // friend concede acesso especial a membros private/protected.
    // Util para: operadores (<<, >>), funcoes de auditoria, classes fortemente acopladas.
    //
    //   class Cofre {
    //       int combinacao;   // private
    //       friend void auditarCofre(const Cofre& c);  // acesso especial
    //   };
    //
    //   void auditarCofre(const Cofre& c) {
    //       cout << c.combinacao;  // valido — e amiga
    //   }

    Cofre cofre(1234);

    // cofre.combinacao;   // ERRO: private
    auditarCofre(cofre);   // OK: auditarCofre e friend

    std::cout << "\nUse friend com moderacao — quebra o encapsulamento." << std::endl;
    std::cout << "Casos legitimos: operadores sobrecarregados, factories, testes." << std::endl;
}

static void demonstrarExplicit()
{
    std::cout << "\n============================" << std::endl;
    std::cout << " TOPICO 33 — explicit" << std::endl;
    std::cout << "============================" << std::endl;

    // explicit bloqueia conversao IMPLICITA no constructor de um unico parametro.
    //
    // Sem explicit — o compilador permitiria:
    //   Temperatura t = 36.5;   // converte double para Temperatura silenciosamente
    //   exibirTemp(36.5);       // converte o argumento automaticamente
    //   Isso pode gerar bugs sutis e confusos.
    //
    // Com explicit — so estas formas sao validas:
    //   Temperatura t(36.5);    // construcao explicita
    //   Temperatura t{36.5};    // inicializacao com chaves

    Temperatura corporal(36.5);
    Temperatura febre(39.2);

    // Temperatura errada = 100.0;  // ERRO com explicit — bloqueado!

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Temperatura corporal: " << corporal.obter() << " C" << std::endl;
    std::cout << "Temperatura febre   : " << febre.obter()    << " C" << std::endl;

    std::cout << "\nUse explicit em construtores de unico parametro." << std::endl;
    std::cout << "Evita conversoes invisiveis que podem introduzir bugs dificeis." << std::endl;
    std::cout << "Em C++20, explicit tambem se aplica a conversoes de outros tipos." << std::endl;
}

// ============================================================
// FECHAMENTO — Sistema de formas geometricas (OOP completo)
// ============================================================
static void demonstrarFormas()
{
    std::cout << "\n======================================" << std::endl;
    std::cout << " FECHAMENTO — Sistema de geometria" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "(class + public/private + constructor + heranca + virtual + override)" << std::endl;

    Circulo    circulo(5.0);
    Retangulo  retangulo(4.0, 6.0);
    Triangulo  triangulo(3.0, 8.0);
    Circulo    pequeno(2.0);

    // vector de ponteiros para a base — heranca + polimorfismo
    std::vector<Forma*> formas;
    formas.push_back(&circulo);
    formas.push_back(&retangulo);
    formas.push_back(&triangulo);
    formas.push_back(&pequeno);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nAreas por tipo:" << std::endl;

    double totalArea = 0.0;
    for (Forma* f : formas) {
        double area = f->calcularArea();
        totalArea  += area;
        std::cout << "  " << f->descricao()
                  << " — area = " << area << std::endl;
    }

    std::cout << "\nArea total: " << totalArea << std::endl;
    std::cout << "\nO mesmo loop funciona para QUALQUER nova Forma que herdar a base." << std::endl;
    std::cout << "Isso e o poder do polimorfismo: codigo generico que funciona com tipos especificos." << std::endl;
}

// ============================================================
// PONTO DE ENTRADA DA AULA 07
// ============================================================
void rodarAula07()
{
    std::cout << "\n================================" << std::endl;
    std::cout << " AULA 07 - ORIENTACAO A OBJETOS" << std::endl;
    std::cout << "================================\n" << std::endl;

    demonstrarClass();
    demonstrarAcesso();
    demonstrarConstructor();
    demonstrarHeranca();
    demonstrarVirtualOverride();
    demonstrarFriend();
    demonstrarExplicit();
    demonstrarFormas();

    std::cout << "\n================================" << std::endl;
    std::cout << " FIM DA AULA 07" << std::endl;
    std::cout << "================================\n" << std::endl;
}
