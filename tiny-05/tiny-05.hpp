#pragma once

namespace pjc {

/**
 * Jednoduchá implementace komplexních čísel, viz třeba
 * https://cs.wikipedia.org/wiki/Komplexn%C3%AD_%C4%8D%C3%ADslo
 *
 * Vaším úkolem je pro ni přidat binární operátory +, -, *, fungující
 * pro pár instancí complex, ale i pro kombinaci instance complex a
 * double.
 */
class complex {
public:

    complex(double real, double imaginary);

    // Vrátí reálnou část
    double real() const;
    // Nastaví reálnou část na d
    void real(double d);

    // Vrátí imaginární část
    double imag() const;
    // Nastaví imaginární část na d
    void imag(double d);

    

    complex operator + (const double & rhs);
    complex operator - (const double & rhs);
    complex operator * (const double & rhs);

    complex operator + (const complex & rhs);
    complex operator - (const complex & rhs);
    complex operator * (const complex & rhs);



private:
    double m_real;
    double m_imag;
};

complex operator + (double blob, const complex & rhs);
complex operator - (double blob, const complex & rhs);
complex operator * (double blob, const complex & rhs);

} // end namespace pjc
