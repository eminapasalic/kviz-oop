#include "Pitanja.h"

Pitanja::Pitanja(std::string tekst, std::vector<std::string> opc, int tacno): pitanje(tekst),opcije (opc),tacanOdgovor(tacno) {}
void Pitanja::display() const {
    std::cout << pitanje << std::endl;
    for (size_t i = 0; i < opcije.size(); i++) {
        std::cout << i + 1 << ". " << opcije[i] << std::endl;

    }
}

bool Pitanja::isTacno(int odabir) const {
    return odabir == tacanOdgovor;

}
