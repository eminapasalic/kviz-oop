#ifndef QUIZZ_QUIZITEM_H
#define QUIZZ_QUIZITEM_H

#include <iostream>
#include <vector>

class QuizItem{
public:
    virtual void display() const = 0;
    virtual ~QuizItem() = default;

};

#endif //QUIZZ_QUIZITEM_H
