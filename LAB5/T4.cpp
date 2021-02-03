//
//  T4.cpp
//  LAB5
//
//  Created by Laith Oudah on 2020-12-09.
//

#include <iostream>

class A {

public:
    void f() {
        std::cout << "A::f" << std::endl;
    }
    // Virtual ger möjligheten att överskriva (Fallback function)
    virtual void g() {
        std::cout << "A::g" << std::endl;
    }
};

class B : public A {
public:
    void f() {
        std::cout << "B::f" << std::endl;
    }
    void g() {
        std::cout << "B::g" << std::endl;
    }
};
int main(int argc, char** argv) {

    A a;
    B b;

    // Skapar en pointer och pekar till adressen av a respketive B.
    A* aPtr = &a;
    A* bPtr = &b;

    // Pointern pekar mot adress och ge mig det värdet
    aPtr->f(); // A::f
    aPtr->g(); // A::g

    bPtr->f(); //B::f is not virtual, A::f will execute instead
    bPtr->g(); //B::g // ty virtual så replacear den.

    return 0;
}
