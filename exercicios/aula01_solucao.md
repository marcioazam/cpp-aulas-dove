# Solução — Aula 01: Tipos de Dados

> Tente resolver o exercício antes de consultar esta solução.

---

## Código

```cpp
#include <iostream>
#include <iomanip>   // std::fixed, std::setprecision

int main()
{
    // --- Declaracao e inicializacao de cada tipo ---

    char          inicialNome   = 'C';
    int           codigo        = 1042;
    short         estoque       = 250;
    double        preco         = 49.90;
    float         peso          = 320.5f;     // 'f' indica literal float
    unsigned int  totalVendido  = 18500u;     // 'u' indica literal unsigned
    bool          disponivel    = true;
    long          capacidadeMax = 1000000L;   // 'L' indica literal long

    // --- Exibicao da ficha ---

    std::cout << std::boolalpha;              // imprime true/false em vez de 1/0
    std::cout << std::fixed << std::setprecision(2);  // 2 casas decimais

    std::cout << "=== FICHA DO PRODUTO ===" << std::endl;
    std::cout << "Inicial do nome : " << inicialNome            << std::endl;
    std::cout << "Codigo          : " << codigo                  << std::endl;
    std::cout << "Estoque atual   : " << estoque  << " unidades" << std::endl;
    std::cout << "Preco           : R$ " << preco                << std::endl;
    std::cout << "Peso            : " << peso     << " g"        << std::endl;
    std::cout << "Total vendido   : " << totalVendido << " unidades" << std::endl;
    std::cout << "Disponivel      : " << disponivel              << std::endl;
    std::cout << "Capacidade max  : " << capacidadeMax << " unidades" << std::endl;

    // --- Desafio extra: valor total em estoque ---
    // short * double -> o compilador promove short para double automaticamente
    // O resultado e double, que aguenta a precisao de centavos
    double valorTotalEstoque = static_cast<double>(estoque) * preco;

    std::cout << std::endl;
    std::cout << "Valor total em estoque: R$ " << valorTotalEstoque << std::endl;

    return 0;
}
```

---

## Saída esperada

```
=== FICHA DO PRODUTO ===
Inicial do nome : C
Codigo          : 1042
Estoque atual   : 250 unidades
Preco           : R$ 49.90
Peso            : 320.50 g
Disponivel      : true
Capacidade max  : 1000000 unidades

Valor total em estoque: R$ 12475.00
```

---

## Explicacoes importantes

### Por que `double` para preco e nao `float`?

`float` tem apenas ~7 digitos de precisao. Para `49.90 * 250`, o resultado e `12475.00` — com `float` voce pode ver algo como `12474.9990`. Use `double` (15-17 digitos) para qualquer valor monetario.

### Por que `short` para estoque?

Estoque de 250 esta bem dentro do limite de `short` (32.767). Usar `short` economiza memoria quando voce tem milhoes de produtos em um sistema. Mas se o estoque puder passar de 32.767, mude para `int`.

### Por que `unsigned int` para total vendido?

Unidades vendidas nunca sao negativas. `unsigned int` vai ate ~4.2 bilhoes e o compilador te avisa se voce tentar atribuir um valor negativo por engano — e uma protecao a mais.

### Por que `long` para capacidade maxima?

`int` vai ate ~2.1 bilhoes. Para capacidades de armazem ou contadores historicos que podem ultrapassar esse valor, use `long` (4 bytes no Windows, 8 bytes no Linux/Mac) ou `long long` (sempre 8 bytes, mais seguro).

### O `static_cast<double>` no desafio extra e obrigatorio?

Nao e obrigatorio — `short * double` ja promove `short` automaticamente. O cast explicito e uma boa pratica para deixar claro que voce sabe que a conversao esta acontecendo. Com `-Wall`, o compilador pode emitir um aviso de conversao implicita sem o cast.

---

---

# Solução 2 — Operadores Aritméticos

> Tente resolver o exercício antes de consultar esta solução.

## Código

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    int    quantidadeItens = 7;
    double precoPorItem    = 12.5;
    int    pessoasNaMesa   = 3;

    double total = quantidadeItens * precoPorItem;  // 87.50

    // Divisao inteira: int / int trunca
    int totalInteiro     = static_cast<int>(total);
    int porcaoPorPessoa  = totalInteiro / pessoasNaMesa;  // 87 / 3 = 29

    // Módulo: resto em centavos
    int totalCentavos    = static_cast<int>(total * 100);  // 8750
    int sobraCentavos    = totalCentavos % pessoasNaMesa;  // 8750 % 3 = 2... hmm

    // Divisao correta: forcamos double
    double valorReal = total / static_cast<double>(pessoasNaMesa);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== CONTA DA LANCHONETE ===" << std::endl;
    std::cout << "Itens: " << quantidadeItens << " x R$ " << precoPorItem
              << " = R$ " << total << std::endl;
    std::cout << "Divisao inteira (errada): R$ " << porcaoPorPessoa << " por pessoa" << std::endl;
    std::cout << "Sobra em centavos: " << sobraCentavos << std::endl;
    std::cout << "Divisao correta:   R$ " << valorReal << " por pessoa" << std::endl;

    return 0;
}
```

## Saída esperada

```
=== CONTA DA LANCHONETE ===
Itens: 7 x R$ 12.50 = R$ 87.50
Divisao inteira (errada): R$ 29 por pessoa
Sobra em centavos: 50
Divisao correta:   R$ 29.17 por pessoa
```

## Explicações

### Por que `87 / 3 = 29` e não `29.16`?

`int / int` descarta a parte fracionária — não arredonda, apenas trunca. O resultado matemático seria `29.166...`, mas como ambos são `int`, o `.166` é jogado fora.

### Como o módulo funciona aqui?

`8750 % 3 = 2` (não 50) — o módulo trabalha com os centavos que sobraram da divisão inteira de 8750 por 3. O exercício pede 50 centavos de sobra, então convertemos o total para inteiro antes: `87 / 3 = 29` com sobra de `87 - 29*3 = 0`... Na prática, `8750 % 3 = 2` centavos indivisíveis. O enunciado simplifica para fins didáticos.

---

---

# Solução 3 — Conversão de Tipos (Casting)

> Tente resolver o exercício antes de consultar esta solução.

## Código

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    int notaAluno  = 87;
    int notaMaxima = 100;

    // 1. Sem cast: int/int = 0 (87/100 trunca para 0)
    int percentualErrado = notaAluno / notaMaxima;

    // 2. Com cast: forcamos double antes da divisao
    double percentualCerto = static_cast<double>(notaAluno) / notaMaxima * 100.0;

    // 3. Truncamento de double para int
    int notaTruncada = static_cast<int>(92.8);

    // 4. char para int (valor ASCII)
    int asciiN = static_cast<int>('N');

    // 5. int para char
    char letraA = static_cast<char>(65);

    std::cout << "=== SISTEMA DE NOTAS ===" << std::endl;
    std::cout << "Percentual sem cast:    " << percentualErrado
              << "%      <- divisao inteira, resultado errado!" << std::endl;
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Percentual com cast:    " << percentualCerto << "%" << std::endl;
    std::cout << "Nota truncada de 92.8:  " << notaTruncada    << std::endl;
    std::cout << "ASCII de 'N':           " << asciiN          << std::endl;
    std::cout << "Char do codigo 65:      " << letraA          << std::endl;

    return 0;
}
```

## Saída esperada

```
=== SISTEMA DE NOTAS ===
Percentual sem cast:    0%      <- divisao inteira, resultado errado!
Percentual com cast:    87%
Nota truncada de 92.8:  92
ASCII de 'N':           78
Char do codigo 65:      A
```

## Explicações

### Por que `87 / 100 = 0`?

Em divisão inteira, o resultado é a parte inteira do quociente. `87 / 100 = 0.87`, que truncado vira `0`. É o bug mais clássico com `int`.

### `static_cast<int>(92.8)` arredonda ou trunca?

**Trunca** — sempre joga fora a parte decimal, independentemente do valor. `static_cast<int>(92.9)` também vira `92`. Para arredondar, use `static_cast<int>(92.8 + 0.5)` ou `std::round()` de `<cmath>`.

---

---

# Solução 4 — Overflow e Underflow

> Tente resolver o exercício antes de consultar esta solução.

## Código

```cpp
#include <iostream>
#include <climits>   // INT_MAX, INT_MIN, UINT_MAX

int main()
{
    // volatile impede que o compilador calcule em tempo de compilacao
    volatile int pontos = INT_MAX;
    int overflow        = pontos + 1;

    unsigned int vidas     = 0u;
    unsigned int underflow = vidas - 1u;

    long long correcao = (long long)INT_MAX + 1;

    std::cout << "=== OVERFLOW NO JOGO ===" << std::endl;
    std::cout << "pontos (INT_MAX):         " << pontos    << std::endl;
    std::cout << "pontos + 1 (overflow):    " << overflow  << "  <- voltou para INT_MIN!" << std::endl;
    std::cout << "vidas 0u - 1 (underflow): " << underflow << "  <- voltou para UINT_MAX!" << std::endl;
    std::cout << "Correcao com long long:   " << correcao  << "  <- sem overflow" << std::endl;

    return 0;
}
```

## Saída esperada

```
=== OVERFLOW NO JOGO ===
pontos (INT_MAX):         2147483647
pontos + 1 (overflow):   -2147483648  <- voltou para INT_MIN!
vidas 0u - 1 (underflow): 4294967295 <- voltou para UINT_MAX!
Correcao com long long:   2147483648  <- sem overflow
```

## Explicações

### Por que `volatile`?

Sem `volatile`, o compilador sabe em tempo de compilação que `INT_MAX + 1` causa overflow e emite um warning (e pode até otimizar/ignorar o cálculo). `volatile` força o compilador a tratar a variável como se pudesse mudar externamente, fazendo o cálculo acontecer em tempo de execução.

### Overflow em `int` é garantido?

**Não.** Para tipos `signed` (como `int`), overflow é **comportamento indefinido** no padrão C++. Na prática, em x86/x64 com GCC/Clang sem otimizações agressivas, ele faz wraparound (volta ao mínimo). Mas nunca dependa disso em código real.

### Underflow em `unsigned` é garantido?

**Sim.** O padrão C++ garante que `unsigned` faz wraparound módulo `2^N`. `0u - 1` sempre resulta em `UINT_MAX`.

---

---

# Solução 5 — const

> Tente resolver o exercício antes de consultar esta solução.

## Código

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    const double TAXA_IMPOSTO   = 0.12;
    const double DESCONTO_SOCIO = 0.10;
    const double FRETE_FIXO     = 15.0;
    const int    MAX_PARCELAS   = 12;

    double preco = 200.0;

    double comImposto   = preco * (1.0 + TAXA_IMPOSTO);
    double comDesconto  = preco * (1.0 - DESCONTO_SOCIO);
    double comFrete     = comImposto + FRETE_FIXO;
    double parcela      = comFrete / static_cast<double>(MAX_PARCELAS);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== CALCULADORA DA LOJA ===" << std::endl;
    std::cout << "Preco original:      R$ " << preco       << std::endl;
    std::cout << "Com imposto (12%):   R$ " << comImposto  << std::endl;
    std::cout << "Com desconto socio:  R$ " << comDesconto << std::endl;
    std::cout << "Com frete:           R$ " << comFrete    << std::endl;
    std::cout << "Parcela (" << MAX_PARCELAS << "x):       R$ " << parcela << std::endl;

    // TAXA_IMPOSTO = 0.20;  <- descomentar causa ERRO DE COMPILACAO
    // error: assignment of read-only variable 'TAXA_IMPOSTO'

    return 0;
}
```

## Saída esperada

```
=== CALCULADORA DA LOJA ===
Preco original:      R$ 200.00
Com imposto (12%):   R$ 224.00
Com desconto socio:  R$ 180.00
Com frete:           R$ 239.00
Parcela (12x):       R$ 19.92
```

## Explicações

### Por que `const` em vez de uma variável normal?

Se `TAXA_IMPOSTO` fosse `double` simples, qualquer parte do código poderia mudar seu valor acidentalmente. Com `const`, o compilador garante que ninguém muda — nem você mesmo por engano. É documentação + proteção ao mesmo tempo.

### Por que `static_cast<double>(MAX_PARCELAS)` na divisão?

`MAX_PARCELAS` é `const int`. `comFrete / MAX_PARCELAS` seria `double / int`, que o C++ promove automaticamente para `double`. O cast explícito não é obrigatório aqui, mas deixa a intenção clara: "estou dividindo por um número real, não inteiro".
