#include <iostream>
#include "aula00_intro.h"
#include "aula01_tipos.h"
#include "aula02_ponteiros.h"
#include "aula03_tipos_modernos.h"
#include "aula04_controle.h"
#include "aula05_containers.h"

int main()
{
    int aula;

    std::cout << "================================" << std::endl;
    std::cout << "   SELECIONE A AULA            " << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << " 0 - Introducao (comece aqui!) " << std::endl;
    std::cout << " 1 - Tipos de dados            " << std::endl;
    std::cout << " 2 - Array, Ponteiros, Pilha, Fila e Matriz " << std::endl;
    std::cout << " 3 - Tipos modernos C++11/17   " << std::endl;
    std::cout << " 4 - Estruturas de controle    " << std::endl;
    std::cout << " 5 - Conteineres e Tipos Compostos " << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Aula: ";
    std::cin >> aula;
    std::cout << std::endl;

    switch (aula)
    {
        case 0:
            rodarAula00();
            break;

        case 1:
            rodarAula01();
            break;

        case 2:
            rodarAula02();
            break;

        case 3:
            rodarAula03();
            break;

        case 4:
            rodarAula04();
            break;

        case 5:
            rodarAula05();
            break;

        default:
            std::cout << "Aula " << aula << " nao encontrada." << std::endl;
            break;
    }

    return 0;
}
