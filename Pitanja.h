#ifndef QUIZZ_PITANJA_H
#define QUIZZ_PITANJA_H
#include "QuizItem.h"
#include<iostream>
#include <vector>

class Pitanja : public QuizItem {
public:
    std::string pitanje;
    std::vector<std::string> opcije;
    int tacanOdgovor;
    Pitanja(std::string tekst,std::vector<std::string> opc, int tacno);
    void display()const override;
    bool isTacno(int odabir)const;
};

#endif //QUIZZ_PITANJA_H
