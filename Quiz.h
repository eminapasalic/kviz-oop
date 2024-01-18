#ifndef QUIZZ_QUIZ_H
#define QUIZZ_QUIZ_H

#include <iostream>
#include <vector>
#include "Pitanja.h"
#include "Igrac.h"
#include <memory>

class Quiz {
private:
    std::vector<std::shared_ptr<QuizItem>> items;
    std::vector<Pitanja> pitanja;
    std::vector<Igrac> igraci;
    int skor;


public:
    Quiz();
    void loadPitanja(const std::string& filename);
    void start();
    void odabirOblasti();
    void pohraniSkor(const  std::string& imeIgraca,std::string& prezimeIgraca);
    void tabela() const;
    void storedTabela(const std::string& filename)const;
    void saveTable(const std::string& filename) const;
    void loadTable(const std::string& filename);



};

#endif //QUIZZ_QUIZ_H