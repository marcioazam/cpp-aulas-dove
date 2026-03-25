#include <iostream>
#include "aula01_tipos.h"
#include "aula02_tipos_modernos.h"
#include "aula03_controle.h"

int main()
{
    int aula;

    std::cout << "================================" << std::endl;
    std::cout << "   SELECIONE A AULA            " << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << " 1 - Tipos de dados            " << std::endl;
    // std::cout << " 2 - Tipos modernos C++11/17 (Block)   " << std::endl;
    // std::cout << " 3 - Estruturas de controle  (Block)  " << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Aula: ";
    std::cin >> aula;
    std::cout << std::endl;

    switch (aula)
    {
        case 1:
            rodarAula01();
            break;

        case 2:
            break;

        case 3:
            break;

        default:
            std::cout << "Aula " << aula << " nao encontrada." << std::endl;
            break;
    }

    return 0;
}
