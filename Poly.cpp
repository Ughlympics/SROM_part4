#include "Poly.h"
#include <array>
#include <iostream>


std::bitset<Poly::_POWER> Poly::mult_matrix[Poly::_POWER];
bool Poly::multiplication_matrix = false;

void Poly::generate_mult_matrix(static std::bitset<_POWER> mult_matrix[_POWER]) {
    int P = 887;
    int powers_of_2[_POWER];
    powers_of_2[0] = 1;
    for (int i = 1; i <_POWER; ++i) {
        powers_of_2[i] = (powers_of_2[i - 1] << 1) % P;
    }

    for (int i = 0; i < _POWER; ++i) {
        for (int j = 0; j < _POWER; ++j) {
            int v1 = (powers_of_2[i] + powers_of_2[j]) % P;
            int v2 = (powers_of_2[i] - powers_of_2[j] + P) % P; 
            int v3 = (-powers_of_2[i] + powers_of_2[j] + P) % P;
            int v4 = (-powers_of_2[i] - powers_of_2[j] + P) % P;

            if (v1 == 1 || v2 == 1 || v3 == 1 || v4 == 1) {
                mult_matrix[i][j] = 1;
            }
            else {
                mult_matrix[i][j] = 0;
            }
        }
    }
    multiplication_matrix = true;
}

void Poly::print_mult_matrix(static std::bitset<_POWER> mult_matrix[_POWER]) {
    for (int i = 0; i < _POWER; ++i) {
        for (int j = 0; j < _POWER; ++j) {
            std::cout << mult_matrix[i][j];
        }
        std::cout << "\n";
    }
}

Poly::Poly() {
    coefficients.reset();
    if (!multiplication_matrix) {
        generate_mult_matrix(mult_matrix);
        multiplication_matrix = true;
    }
}

Poly::Poly(unsigned _default_num) : coefficients{ _default_num } {
    if (!multiplication_matrix) {
        generate_mult_matrix(mult_matrix);
        multiplication_matrix = true;
    }
}

Poly::Poly(const Poly& othrer) {
    this->coefficients = othrer.coefficients;
}

Poly::Poly(const std::string& binaryString) {

    if (!multiplication_matrix) {
        generate_mult_matrix(mult_matrix);
        multiplication_matrix = true;
    }
    int ln = binaryString.size();

    if (ln > _POWER) {
        coefficients = 0b0;
        throw std::invalid_argument("Binary string exceeds maximum degree");
    }

    int j = 0;
    for (auto i = binaryString.rbegin(); i != binaryString.rend(); ++i, ++j) {
        if (*i == '1') {
            coefficients[j] = 1;
        }
        else if (*i != '0') {
            coefficients = 0b0;
            throw std::invalid_argument("Binary string contains invalid characters");
        }
    }
}

Poly::Poly(const std::bitset<_POWER>& bitset_coeffs) {
    coefficients = bitset_coeffs;
}

Poly::~Poly() {}

std::string Poly::toBitString() const {
    std::string bitString;
    for (int i = _POWER - 1; i >= 0; --i) {
        bitString += coefficients[i] ? '1' : '0';
    }
    return bitString;
}

//overloaded operators
Poly& Poly::operator=(const Poly& pol) {
    this->coefficients = pol.coefficients;
    return *this;
}

Poly Poly::operator+(const Poly& pol) const {
    Poly res;
    res.coefficients = this->coefficients ^ pol.coefficients;
    return res;
}

//operations
void Poly::lcycle_shift(std::bitset<_POWER>& b, int i) {
    b = (b >> i) ^ (b << _POWER - i);
}

void Poly::rcycle_shift(std::bitset<_POWER>& b, int i) {
    b = (b << i) ^ (b >> _POWER - i);
}


Poly Poly::square() const {
    Poly res = *this;
    lcycle_shift(res.coefficients, 1);
    return res;
}
