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
