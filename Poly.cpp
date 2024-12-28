#include "Poly.h"
#include <array>
#include <iostream>



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
