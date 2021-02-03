//
//  main.cpp
//  LAB5Try2
//
//  Created by Laith Oudah on 2020-12-09.
//

#include "headerT2.h" // header in local directory

using namespace std;

Complex::Complex() { // En klass som heter Complex och har en construct som heter real och imag, default värde. Måste finnas.
    real = 0;
    imag = 0;
}

Complex::Complex(double re, double im) { // Klassen som tar emot två värden och använder de variabler som finns i .h filen.
    real = re;
    imag = im;
}

/* Complex::~Complex() { // Används ej, när programmet stängs, försvinner allt.
//cout << "dtor ~Complex invoked" << endl;
}*/

double Complex::getReal() { // Samma klass, ger oss realla värdet.
    return real;
}
double Complex::getImaginary() { // Samma klass, ger oss img värdet
    return imag;
}
void Complex::setReal(double re) { // Tar emot en double, och sätter de värdet som stoppas in i RE.
    real = re;
}
void Complex::setImaginary(double im) { // -.- i IM
    real = im;
}
Complex Complex::operator+(Complex& theComplex) { //
//    Complex complex; // Objekt som heter complex för klassen complex
//
//    // Delar complexobjetet i två delar
//    complex.real = real + theComplex.getReal();
//    complex.imag = imag + theComplex.getImaginary();
//    return complex;
    return (Complex((real + theComplex.real), (imag + theComplex.imag)));
}

// Delar complexobjetet i två delar
Complex Complex::operator-(Complex& theComplex) {
//    Complex complex;
//    complex.real = real - theComplex.getReal();
//    complex.imag = imag - theComplex.getImaginary();
    return (Complex((real - theComplex.real), (imag - theComplex.imag)));

  //  return complex;
}

// Delar complexobjetet i två delar
Complex Complex::operator*(Complex& theComplex) {
    // Använder denna formel (a+bi)(c+di) = ac + adi + bci + bdi2
    Complex complex;
    complex.real = real * theComplex.getReal() - (imag * theComplex.getImaginary());
    complex.imag = real * theComplex.getImaginary() + imag * theComplex.getReal();
    return complex;
}

// Delar complexobjetet i två delar
Complex Complex::operator/(Complex& theComplex) {
    Complex complex;

    // Samma resultat med this och enkel pekare
    complex.real = (this->real * theComplex.getImaginary()) / (theComplex.getReal() * theComplex.getReal() + theComplex.getImaginary() * theComplex.getImaginary());
    complex.imag = (this->imag * theComplex.getReal() - this->real * theComplex.getImaginary()) / (theComplex.getReal() * theComplex.getReal() + theComplex.getImaginary() * theComplex.getImaginary());
    return complex;
}

int main() {
    Complex complex1(1, 1); //Okbejt 1 (1+1i)
    Complex complex2(2, 2); //Objekt 2 (2+2i)

    // Nya variabler för de olika operatorerna
    Complex calcAdd = complex1 + complex2;
    Complex calcSub = complex1.operator-(complex2);
    Complex calcMult = complex1.operator*(complex2);
    Complex calcDiv = complex1.operator/(complex2);

    // Addition
    cout << "Addition:" << endl;
    cout << calcAdd.getReal() << " " << calcAdd.getImaginary() << "i" << endl;

    // Subtraction
    cout << "Subtraction:" << endl;
    cout << calcSub.getReal() << " " << calcSub.getImaginary() << "i" << endl;

    // Multiplication
    cout << "Multiplication:" << endl;
    cout << calcMult.getReal() << " " << calcMult.getImaginary() << "i" << endl;

    // Division
    cout << "Division:" << endl;
    cout << calcDiv.getReal() << " " << calcDiv.getImaginary() << "i" << endl;

    return 0;
}

