#include "tiny-05.hpp"

namespace pjc {

complex::complex(double real, double imaginary) :
    m_real(real),
    m_imag(imaginary) {}

double complex::real() const {
    return m_real;
}

void complex::real(double d) {
    m_real = d;
}

double complex::imag() const {
    return m_imag;
}

void complex::imag(double d) {
    m_imag = d;
}

complex complex::operator + (const double & rhs){
    return complex(this->real() + rhs, this->imag());
}
complex complex::operator - (const double & rhs){
    return complex(this->real() - rhs, this->imag());
}
complex complex::operator * (const double & rhs){
    return complex(this->real() * rhs, this->imag() * rhs);
}

complex complex::operator+ (const complex & rhs){
    return complex(this->real() + rhs.real(), this->imag() + rhs.imag());
}
complex complex::operator- (const complex & rhs){
    return complex(this->real() - rhs.real(), this->imag() - rhs.imag());
}
complex complex::operator* (const complex & rhs){
    double real_temp = this->real()*rhs.real()-this->imag()*rhs.imag();
    double imag_temp = this->real()*rhs.imag()+this->imag()*rhs.real();
    return complex(real_temp, imag_temp);
}
}
