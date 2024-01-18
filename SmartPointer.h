#ifndef QUIZZ_SMARTPOINTER_H
#define QUIZZ_SMARTPOINTER_H

#include <iostream>
#include <memory>

template<typename P>
class SmartPointer{
private:
    std::shared_ptr<P> ptr_;

public:
    explicit SmartPointer(std::shared_ptr<P> ptr) : ptr_(ptr) {
    }
    SmartPointer<P>& operator ++(){
            ++(*ptr_);
            return *this;
    }
    P* get() const{
        return ptr_.get();
    };
};

#endif //QUIZZ_SMARTPOINTER_H
