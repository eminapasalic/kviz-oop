#ifndef QUIZZ_IGRAC_H
#define QUIZZ_IGRAC_H

#include <iostream>

class Igrac{
public:
    std::string ime;
    std::string prezime;
    int brBodova;
    Igrac();
    Igrac(const std::string& imeIgraca, std::string& prezimeIgraca,int skorIgraca);
};

#endif //QUIZZ_IGRAC_H
