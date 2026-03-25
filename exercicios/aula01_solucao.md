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
