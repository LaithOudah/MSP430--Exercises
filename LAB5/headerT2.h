//
//  complex.h
//  Courses
//
//  Created by Laith Oudah on 2020-12-09.
//

#ifndef Header_h
#define Header_h

#include <iostream>

class Complex {
public: // Kan nås via .cpp
    Complex(); //Default constructor
    Complex(double re, double im); //Prototype. You should define this constructor.
    ~Complex(); //Deconstructor, används för att rensa minne, behövs inte pga den används ej då vi lagrar ingenting i minnet. new etc. (Memoryleak)

    double getReal(void); //get the real part of the complex number
    double getImaginary(void); //get the Imaginary part of the 2 complex number
    void setReal(double re);//set the real part of the complex number
    void setImaginary(double im); //set the Imaginary part of the complex number

    //overwrite the operators for complex numbers
    Complex operator+(Complex& theComplex);
    Complex operator-(Complex& theComplex);
    Complex operator*(Complex& theComplex);
    Complex operator/(Complex& theComplex);

private: // Endast i .h filen
    double real;
    double imag;
};

#endif /* Header_h */
