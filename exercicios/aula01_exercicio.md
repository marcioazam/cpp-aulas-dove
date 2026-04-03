# Exercício — Aula 01: Tipos de Dados

## Contexto

Você vai criar a **ficha de cadastro de um produto em um estoque** usando apenas os tipos de dados vistos na Aula 01.

O objetivo é praticar a declaração, inicialização e impressão de cada tipo de variável no console.

---

## Tarefa

Crie um programa que represente um produto com as seguintes informações:

| Campo                                      | Tipo esperado                       | Exemplo de valor |
| ------------------------------------------ | ----------------------------------- | ---------------- |
| Nome do produto (inicial)                  | Um único caractere                  | `'C'`            |
| Codigo do produto                          | Numero inteiro                      | `1042`           |
| Quantidade em estoque                      | Numero inteiro pequeno (max 32.767) | `250`            |
| Preco em reais (centavos precisos)         | Ponto flutuante de precisao dupla   | `49.90`          |
| Peso em gramas (aproximado)                | Ponto flutuante de precisao simples | `320.5`          |
| Numero de unidades vendidas historicamente | Inteiro sem sinal (nunca negativo)  | `18500`          |
| Esta disponivel para venda                 | Verdadeiro ou falso                 | `true`           |
| Quantidade maxima permitida no deposito    | Inteiro longo                       | `1000000`        |

---

## O que o programa deve exibir

Ao executar, o console deve mostrar algo parecido com:

```
=== FICHA DO PRODUTO ===
Inicial do nome : C
Codigo          : 1042
Estoque atual   : 250 unidades
Preco           : R$ 49.90
Peso            : 320.5 g
Total vendido   : 18500 unidades
Disponivel      : true
Capacidade max  : 1000000 unidades
```

---

## Dicas

- Para imprimir `true`/`false` em vez de `1`/`0`, use `std::boolalpha` antes do `cout`.
- Para controlar casas decimais no preco, use `std::fixed` e `std::setprecision(2)` — inclua o header `<iomanip>`.
- `short` suporta valores de -32.768 a 32.767. Para quantidade em estoque pequena, ele e suficiente.
- `unsigned int` so aceita valores positivos — o compilador vai avisar se voce tentar atribuir um valor negativo.
- `long` (ou `long long`) e usado quando o valor pode ser muito grande, como contadores historicos ou capacidades de armazem.
- `float` perde precisao em valores decimais. Use `double` para precos onde centavos importam.
- Para imprimir um `char` como letra, use `cout` normalmente. Para ver seu valor numerico, use `static_cast<int>(variavel)`.

---

## Desafio extra (opcional)

Adicione um calculo ao final:

- **Valor total em estoque** = quantidade × preco
- Declare o resultado no tipo correto (pense: qual tipo aguenta quantidade × preco sem perder precisao?)
- Exiba com duas casas decimais.

---

## Como testar

Compile com:

```bash
cmake --build build
./build/cppsmoke
```

Ou crie um arquivo separado `main_exercicio.cpp` e compile diretamente:

```bash
g++ -std=c++20 -o exercicio src/main_exercicio.cpp
./exercicio
```

---

---

# Exercício 2 — Operadores Aritméticos

## Contexto

Você é o caixa de uma lanchonete e precisa calcular a conta de uma mesa.

## Tarefa

Declare as variáveis abaixo e calcule os resultados pedidos **usando apenas operadores aritméticos** (`+`, `-`, `*`, `/`, `%`):

| Variável          | Tipo     | Valor |
| ----------------- | -------- | ----- |
| `quantidadeItens` | `int`    | `7`   |
| `precoPorItem`    | `double` | `12.5`|
| `pessoasNaMesa`   | `int`    | `3`   |

Calcule e exiba:

1. **Total da conta** = quantidade × preço por item
2. **Valor por pessoa** (divisão inteira de `int` por `int` — observe o resultado)
3. **Sobra** = total de centavos que não divide igualmente (use `%` sobre o total em centavos)
4. **Valor real por pessoa** = usando pelo menos um `double` na divisão para obter resultado correto

## Saída esperada

```
=== CONTA DA LANCHONETE ===
Itens: 7 x R$ 12.50 = R$ 87.50
Divisao inteira (errada): R$ 29 por pessoa
Sobra em centavos: 50
Divisao correta:   R$ 29.17 por pessoa
```

## Dicas

- `int / int` sempre trunca. Para obter decimais, converta um dos lados: `static_cast<double>(total) / pessoas`
- Para calcular a sobra: converta o total para centavos (`int totalCentavos = total * 100`) e use `%`
- `std::setprecision(2)` com `std::fixed` formata os valores monetários

---

---

# Exercício 3 — Conversão de Tipos (Casting)

## Contexto

Um sistema de notas converte pontuações inteiras (0–100) em conceitos e percentuais.

## Tarefa

Dadas as variáveis abaixo, realize as conversões pedidas com `static_cast`:

| Variável     | Tipo  | Valor |
| ------------ | ----- | ----- |
| `notaAluno`  | `int` | `87`  |
| `notaMaxima` | `int` | `100` |

Calcule e exiba:

1. **Percentual** = `notaAluno / notaMaxima` (sem cast) → observe que dá `0`
2. **Percentual correto** = usando `static_cast<double>` em um dos valores
3. **Nota truncada** = `static_cast<int>(92.8)` (simula arredondamento para baixo)
4. **Código ASCII** da letra `'N'` usando `static_cast<int>`
5. **Letra** correspondente ao código ASCII `65` usando `static_cast<char>`

## Saída esperada

```
=== SISTEMA DE NOTAS ===
Percentual sem cast:    0%      <- divisao inteira, resultado errado!
Percentual com cast:    87%
Nota truncada de 92.8:  92
ASCII de 'N':           78
Char do codigo 65:      A
```

## Dicas

- `int / int` com valores menores resulta em `0` — o clássico bug de novato
- `static_cast<double>(notaAluno) / notaMaxima` resolve o problema
- Para exibir o `%` literal no cout sem formatação especial, basta colocar `"%%"` ou `" %"`

---

---

# Exercício 4 — Overflow e Underflow

## Contexto

Um jogo acumula pontos e você precisa entender o que acontece quando os limites dos tipos são ultrapassados.

## Tarefa

1. Declare `int pontos = INT_MAX` e mostre seu valor
2. Some `1` a `pontos` e mostre o resultado — o que aconteceu?
3. Declare `unsigned int vidas = 0u` e subtraia `1` — o que aconteceu?
4. Corrija o problema do item 2 usando `long long` em vez de `int`

> **Dica de compilação:** use `volatile int pontos = INT_MAX;` para evitar que o compilador calcule em tempo de compilação e emita warning.

## Saída esperada

```
=== OVERFLOW NO JOGO ===
pontos (INT_MAX):        2147483647
pontos + 1 (overflow):  -2147483648  <- voltou para INT_MIN!
vidas 0u - 1 (underflow): 4294967295 <- voltou para UINT_MAX!
Correcao com long long:  2147483648  <- sem overflow
```

## Dicas

- `#include <climits>` disponibiliza `INT_MAX`, `INT_MIN`, `UINT_MAX`
- `volatile` impede que o compilador detecte e avise sobre overflow em tempo de compilação
- Para a correção: `long long correto = (long long)INT_MAX + 1;`

---

---

# Exercício 5 — const

## Contexto

Uma loja aplica descontos e impostos fixos. Esses valores não devem mudar durante a execução.

## Tarefa

Declare as constantes abaixo e use-as para calcular os valores pedidos:

| Constante         | Tipo     | Valor  | Significado              |
| ----------------- | -------- | ------ | ------------------------ |
| `TAXA_IMPOSTO`    | `double` | `0.12` | 12% de imposto           |
| `DESCONTO_SOCIO`  | `double` | `0.10` | 10% de desconto p/ sócio |
| `FRETE_FIXO`      | `double` | `15.0` | frete fixo em reais      |
| `MAX_PARCELAS`    | `int`    | `12`   | máximo de parcelas       |

Dado um produto de R$ 200,00:

1. Preço com imposto = preço × (1 + TAXA_IMPOSTO)
2. Preço com desconto de sócio = preço × (1 - DESCONTO_SOCIO)
3. Preço final = com imposto + frete fixo
4. Valor de cada parcela = preço final ÷ MAX_PARCELAS

## Saída esperada

```
=== CALCULADORA DA LOJA ===
Preco original:      R$ 200.00
Com imposto (12%):   R$ 224.00
Com desconto socio:  R$ 180.00
Com frete:           R$ 239.00
Parcela (12x):       R$ 19.92
```

## Dicas

- Use `UPPER_SNAKE_CASE` para todas as constantes — é a convenção padrão
- Tente atribuir um novo valor a uma `const` para ver o erro de compilação
- `const` garante que ninguém muda esses valores por acidente no código
