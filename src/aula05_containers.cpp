#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "aula05_containers.h"

// ============================================================
// AULA 05 — CONTEINERES E TIPOS COMPOSTOS
// Topicos: 16. std::array  17. std::vector  18. struct  19. enum class
// Pre-requisitos: Aulas 00–04 (tipos, ponteiros, modernos, controle)
// ============================================================

// ============================================================
// TOPICO 16 — std::array<T, N>
// ============================================================
static void demonstrarArray()
{
    std::cout << "\n==============================" << std::endl;
    std::cout << " TOPICO 16 — std::array<T, N>" << std::endl;
    std::cout << "==============================" << std::endl;

    // Analogia: caixa de ovos — tamanho fixo impresso na tampa.
    // std::array e como um C-array com superpoderes:
    //   - sabe o proprio tamanho com .size() (sem o sizeof trick)
    //   - pode ser copiado diretamente
    //   - aceita range-based for nativo

    std::array<int, 5> pontos = {10, 20, 30, 40, 50};

    // --- Informacoes e acesso ---
    std::cout << "Tamanho : " << pontos.size()  << std::endl;
    std::cout << "Primeiro: " << pontos.front() << std::endl;
    std::cout << "Ultimo  : " << pontos.back()  << std::endl;

    // Acesso por [] — sem verificacao de bounds (rapido, sem excecao):
    std::cout << "pontos[2]   : " << pontos[2]    << std::endl;

    // Acesso por .at() — COM verificacao de bounds (lanca excecao se fora do range):
    std::cout << "pontos.at(2): " << pontos.at(2) << std::endl;

    // --- Range-based for (Aula 04) ---
    std::cout << "Todos: ";
    for (int p : pontos) {
        std::cout << p << " ";
    }
    std::cout << std::endl;

    // --- For com indice usando .size() ---
    std::cout << "Com indice:" << std::endl;
    for (size_t i = 0; i < pontos.size(); ++i) {
        std::cout << "  pontos[" << i << "] = " << pontos[i] << std::endl;
    }

    // --- Comparacao com C-array ---
    std::cout << "\n--- C-array vs std::array ---" << std::endl;

    int cArray[5]              = {10, 20, 30, 40, 50};
    constexpr size_t NUM_CARR  = sizeof(cArray) / sizeof(cArray[0]);  // truque necessario

    std::cout << "C-array tamanho (sizeof trick) : " << NUM_CARR     << std::endl;
    std::cout << "std::array tamanho (.size())   : " << pontos.size() << std::endl;
    std::cout << "-> Prefira std::array: .size() sempre correto," << std::endl;
    std::cout << "   inclusive ao passar para funcoes (Aula 06)." << std::endl;
}

// ============================================================
// TOPICO 17 — std::vector<T>
// ============================================================
static void demonstrarVector()
{
    std::cout << "\n=============================" << std::endl;
    std::cout << " TOPICO 17 — std::vector<T>" << std::endl;
    std::cout << "=============================" << std::endl;

    // Analogia: lista de compras — voce nao sabe quantos itens havera;
    // vai adicionando conforme necessario. O vector cresce automaticamente.

    // --- Vetor vazio + push_back ---
    std::vector<int> notas;
    std::cout << "Criado vazio. Tamanho: " << notas.size() << std::endl;
    std::cout << "Vazio? " << (notas.empty() ? "sim" : "nao") << std::endl;

    notas.push_back(92);
    notas.push_back(45);
    notas.push_back(78);
    notas.push_back(60);
    notas.push_back(88);

    std::cout << "\nApos 5 push_back:" << std::endl;
    std::cout << "  Tamanho : " << notas.size()  << std::endl;
    std::cout << "  Vazio?   " << (notas.empty() ? "sim" : "nao") << std::endl;
    std::cout << "  Primeiro: " << notas.front() << std::endl;
    std::cout << "  Ultimo  : " << notas.back()  << std::endl;

    // Acesso — igual ao std::array:
    std::cout << "notas[2]   : " << notas[2]    << "  (sem verificacao)" << std::endl;
    std::cout << "notas.at(2): " << notas.at(2) << "  (com verificacao)" << std::endl;

    // --- Range-based for ---
    std::cout << "Notas: ";
    for (int n : notas) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // --- For com indice ---
    std::cout << "Com indice:" << std::endl;
    for (size_t i = 0; i < notas.size(); ++i) {
        std::cout << "  notas[" << i << "] = " << notas[i] << std::endl;
    }

    // --- Inicializacao direta (como std::array) ---
    std::vector<std::string> cidades = {"Sao Paulo", "Rio", "Brasilia"};
    std::cout << "\nCidades: ";
    for (const auto& c : cidades) {
        std::cout << c << " | ";
    }
    std::cout << std::endl;

    // --- clear: esvazia sem destruir o objeto ---
    notas.clear();
    std::cout << "Apos clear — tamanho: " << notas.size() << std::endl;

    // --- Quando usar std::array vs std::vector? ---
    std::cout << "\n--- std::array vs std::vector ---" << std::endl;
    std::cout << "std::array : tamanho FIXO, conhecido em tempo de compilacao." << std::endl;
    std::cout << "             Ex: 7 dias da semana, 3 vertices de triangulo." << std::endl;
    std::cout << "std::vector: tamanho VARIAVEL ou desconhecido antecipadamente." << std::endl;
    std::cout << "             Ex: lista de usuarios, historico de eventos." << std::endl;
}

// ============================================================
// TOPICO 18 — struct
// ============================================================

// struct definida no escopo do arquivo (visivel para os topicos abaixo).
// Nenhuma funcao dentro — isso vira na Aula 06 (metodos).
struct Jogador {
    std::string nome;
    int         vida   = 100;  // valor padrao C++11: se nao informado, usa 100
    int         pontos = 0;    // valor padrao
};

static void demonstrarStruct()
{
    std::cout << "\n=============================" << std::endl;
    std::cout << " TOPICO 18 — struct" << std::endl;
    std::cout << "=============================" << std::endl;

    // Analogia: ficha de cadastro — em vez de 3 variaveis soltas,
    // 1 entidade coesa com nome, vida e pontos relacionados.
    //
    // Estrutura do Jogador:
    //   struct Jogador {
    //       std::string nome;
    //       int         vida   = 100;
    //       int         pontos = 0;
    //   };

    // --- Declaracao e acesso com ponto ---
    Jogador j1;            // vida=100, pontos=0 (valores padrao)
    j1.nome   = "Alice";
    j1.pontos = 1500;
    // j1.vida nao foi alterada — continua 100

    std::cout << "Jogador 1 (campos atribuidos separadamente):" << std::endl;
    std::cout << "  Nome  : " << j1.nome   << std::endl;
    std::cout << "  Vida  : " << j1.vida   << std::endl;
    std::cout << "  Pontos: " << j1.pontos << std::endl;

    // --- Aggregate initialization (inicializacao na ordem dos campos) ---
    Jogador j2 = {"Bob", 75, 2000};  // nome="Bob", vida=75, pontos=2000
    std::cout << "\nJogador 2 (aggregate init):" << std::endl;
    std::cout << "  Nome  : " << j2.nome   << std::endl;
    std::cout << "  Vida  : " << j2.vida   << std::endl;
    std::cout << "  Pontos: " << j2.pontos << std::endl;

    // --- Modificacao de campo ---
    j1.vida -= 30;   // Alice tomou 30 de dano
    std::cout << "\nAlice tomou 30 de dano. Vida agora: " << j1.vida << std::endl;

    // --- Array de structs (combina Aula 02 + struct) ---
    std::cout << "\n--- Array de Jogadores ---" << std::endl;
    Jogador ranking[3] = {
        {"Alice", 85, 1500},
        {"Bob",   75, 2000},
        {"Carol", 60,  900}
    };
    constexpr size_t NUM_RANKING = sizeof(ranking) / sizeof(ranking[0]);

    for (size_t i = 0; i < NUM_RANKING; ++i) {
        std::cout << "  [" << i << "] "
                  << ranking[i].nome
                  << " | vida="   << ranking[i].vida
                  << " | pontos=" << ranking[i].pontos << std::endl;
    }

    // --- Vector de structs (combina Topico 17 + struct) ---
    std::cout << "\n--- Vector de Jogadores ---" << std::endl;
    std::vector<Jogador> time;
    time.push_back({"Diego", 90,  800});
    time.push_back({"Eva",   55, 3200});

    std::cout << "Time (" << time.size() << " jogadores):" << std::endl;
    for (const auto& jogador : time) {
        std::cout << "  " << jogador.nome
                  << " | vida="   << jogador.vida
                  << " | pontos=" << jogador.pontos << std::endl;
    }
}

// ============================================================
// TOPICO 19 — enum class
// ============================================================

enum class EstadoJogo { Menu, Jogando, Pausado, GameOver };
enum class Dificuldade { Facil, Normal, Dificil };

static void demonstrarEnumClass()
{
    std::cout << "\n=============================" << std::endl;
    std::cout << " TOPICO 19 — enum class" << std::endl;
    std::cout << "=============================" << std::endl;

    // Analogia: semaforo — so 3 estados possiveis.
    // Problema que resolve: "magic numbers" — if (estado == 2) nao diz nada.
    // Com enum class: if (estado == EstadoJogo::Jogando) — legivel!

    EstadoJogo  estado      = EstadoJogo::Jogando;
    Dificuldade dificuldade = Dificuldade::Normal;

    // --- switch com enum class (revisao Aula 04) ---
    std::cout << "Estado atual: ";
    switch (estado) {
        case EstadoJogo::Menu:     std::cout << "Menu principal" << std::endl; break;
        case EstadoJogo::Jogando:  std::cout << "Em jogo"        << std::endl; break;
        case EstadoJogo::Pausado:  std::cout << "Pausado"        << std::endl; break;
        case EstadoJogo::GameOver: std::cout << "Game Over"      << std::endl; break;
    }

    std::cout << "Dificuldade : ";
    switch (dificuldade) {
        case Dificuldade::Facil:   std::cout << "Facil (inimigos lentos)"    << std::endl; break;
        case Dificuldade::Normal:  std::cout << "Normal (balanceado)"         << std::endl; break;
        case Dificuldade::Dificil: std::cout << "Dificil (sem misericordia)"  << std::endl; break;
    }

    // --- enum class vs enum antigo ---
    std::cout << "\n--- enum class vs enum antigo ---" << std::endl;
    std::cout << "enum antigo : Menu, Jogando, Pausado... vazam para o escopo global." << std::endl;
    std::cout << "              Podem conflitar com outros nomes no codigo." << std::endl;
    std::cout << "enum class  : nomes isolados — EstadoJogo::Menu, Dificuldade::Facil." << std::endl;
    std::cout << "              Sem conflito. Mais legivel. Tipo seguro." << std::endl;
    std::cout << "              Regra pratica: sempre use enum class em C++ moderno." << std::endl;

    // --- Mudanca de estado ---
    estado = EstadoJogo::GameOver;
    std::cout << "\nPartida encerrada. Estado mudou para: ";
    switch (estado) {
        case EstadoJogo::Menu:     std::cout << "Menu"     << std::endl; break;
        case EstadoJogo::Jogando:  std::cout << "Jogando"  << std::endl; break;
        case EstadoJogo::Pausado:  std::cout << "Pausado"  << std::endl; break;
        case EstadoJogo::GameOver: std::cout << "GameOver" << std::endl; break;
    }
}

// ============================================================
// FECHAMENTO — Mini sistema de jogo
// Usa std::array + std::vector + struct + enum class juntos.
// ============================================================

struct Personagem {
    std::string nome;
    int         nivel  = 1;
    int         pontos = 0;
};

enum class Classe { Guerreiro, Mago, Arqueiro };

static void demonstrarJogoCompleto()
{
    std::cout << "\n=====================================" << std::endl;
    std::cout << " FECHAMENTO — Mini sistema de jogo   " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "(std::array + std::vector + struct + enum class)" << std::endl;

    // 1. enum class: define a classe do personagem
    Classe classeEscolhida = Classe::Mago;

    std::string nomeClasse;
    switch (classeEscolhida) {
        case Classe::Guerreiro: nomeClasse = "Guerreiro"; break;
        case Classe::Mago:      nomeClasse = "Mago";      break;
        case Classe::Arqueiro:  nomeClasse = "Arqueiro";  break;
    }
    std::cout << "\nClasse escolhida : " << nomeClasse << std::endl;

    // 2. std::array: habilidades fixas (sempre 3 — tamanho conhecido)
    std::array<std::string, 3> habilidades = {
        "Bola de fogo",
        "Raio de gelo",
        "Teletransporte"
    };
    std::cout << "Habilidades (" << habilidades.size() << "):" << std::endl;
    for (size_t i = 0; i < habilidades.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << habilidades[i] << std::endl;
    }

    // 3. struct: define o heroi
    Personagem heroi = {"Gandalf", 10, 5000};
    std::cout << "\nHeroi    : " << heroi.nome
              << " | Nivel " << heroi.nivel
              << " | Pontos " << heroi.pontos << std::endl;

    // 4. std::vector: ranking dinamico (pode crescer a qualquer momento)
    std::vector<Personagem> ranking;
    ranking.push_back({"Saruman",  15, 8000});
    ranking.push_back({"Gandalf",  10, 5000});
    ranking.push_back({"Radagast",  8, 3200});

    std::cout << "\nRanking (" << ranking.size() << " jogadores):" << std::endl;
    for (size_t i = 0; i < ranking.size(); ++i) {
        std::string marca = (ranking[i].nome == heroi.nome) ? " <- voce" : "";
        std::cout << "  " << (i + 1) << ". "
                  << ranking[i].nome
                  << " (nivel " << ranking[i].nivel << ")"
                  << " — " << ranking[i].pontos << " pontos"
                  << marca << std::endl;
    }

    std::cout << "\nTodos os conceitos da Aula 05 em acao!" << std::endl;
}

// ============================================================
// PONTO DE ENTRADA DA AULA 05
// ============================================================
void rodarAula05()
{
    std::cout << "\n================================" << std::endl;
    std::cout << " AULA 05 - CONTEINERES E TIPOS COMPOSTOS" << std::endl;
    std::cout << "================================\n" << std::endl;

    demonstrarArray();
    demonstrarVector();
    demonstrarStruct();
    demonstrarEnumClass();
    demonstrarJogoCompleto();

    std::cout << "\n================================" << std::endl;
    std::cout << " FIM DA AULA 05" << std::endl;
    std::cout << "================================\n" << std::endl;
}
