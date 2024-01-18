#include <iostream>
#include "Quiz.h"
#include "Igrac.h"

enum menuOdabir {
    START = 1,
    TABELA,
    POHRANJIVANJE,
    TABELASVIH,
    EXIT
};


int main() {
    Quiz quiz;
    menuOdabir izbor;

    quiz.loadTable("Tabela.txt");

    do {
        std::cout << "---------------MENI---------------" << std::endl;
        std::cout << "1. Zapocni igru" << std::endl;
        std::cout << "2. Tabela" << std::endl;
        std::cout << "3. Pohrani skor" << std::endl;
        std::cout << "4. Tabela igraca prije vas" << std::endl;
        std::cout << "5. Izlaz" << std::endl;



        std::cout << "Odaberite opciju: ";
        std::cin >> static_cast<int&>(reinterpret_cast<int &>(izbor));

        switch (izbor) {
            case START:
                quiz.start();
                break;
            case TABELA:
                quiz.tabela();
                break;
            case POHRANJIVANJE:
            {
                std::string imeIgraca;
                std::string prezimeIgraca;
                std::cout << "Unesite vase ime: ";
                std::cin >> imeIgraca;
                std::cout << "Unesite vase prezime: ";
                std::cin >> prezimeIgraca;
                quiz.pohraniSkor(imeIgraca,prezimeIgraca);
            }
                break;
            case TABELASVIH:
                quiz.storedTabela("Tabela.txt");
                break;
            case EXIT:
                quiz.saveTable("Tabela.txt");
                std::cout << "Hvala na igranju, NAOOOO!" << std::endl;
                break;
            default:
                std::cout << "Pogresan unos, unesite ponovo!" << std::endl;
        }

    }while(izbor != EXIT);

    return 0;
}

