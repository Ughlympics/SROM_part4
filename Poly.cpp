#include "Poly.h"
#include <array>
#include <iostream>
#include <fstream>


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
            //std::cout << mult_matrix[i][j] ;
        }
        //std::cout <<  std::endl;
    }

    /*std::ofstream file("mult_matrix.txt");
    if (file.is_open()) {
        for (int i = 0; i < _POWER; ++i) {
            for (int j = 0; j < _POWER; ++j) {
                file << mult_matrix[i][j];
            }
            file << '\n';
        }
        file.close(); 
        std::cout << "Matrix saved to mult_matrix.txt" << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing!" << std::endl;
    }*/
    multiplication_matrix = true;
}

void Poly::print_matrix(static std::bitset<_POWER> mult_matrix[_POWER]) {
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

//Poly Poly::operator*(const Poly& right) const {
//    std::bitset<_POWER> res_coefs;
//    
//    std::bitset<_POWER> left_temp = this->coefficients;
//    std::bitset<_POWER> lreversed = reverse_bitset(left_temp);
//
//    std::bitset<_POWER> right_temp = right.coefficients;
//    std::bitset<_POWER> rreversed = reverse_bitset(right_temp);
//    std::bitset<_POWER> temp_mult;
//
//    for (int i = 0; i < _POWER; i++,
//        cycle_shift_to_high(left_temp, 1),
//        cycle_shift_to_high(right_temp, 1))
//    {
//        for (int j = 0; j < _POWER; j++){
//            temp_mult[j] = get_sum_of_bits(left_temp & mult_matrix[j]);
//        }
//
//        res_coefs[i] = get_sum_of_bits(temp_mult & right_temp);
//    }
//
//    return Poly(res_coefs);
//}

Poly Poly::operator*(const Poly& right) const {
    std::bitset<_POWER> res_coefs;

    std::bitset<_POWER> left_temp = this->coefficients;
    std::bitset<_POWER> lreversed = reverse_bitset(left_temp);

    std::bitset<_POWER> right_temp = right.coefficients;
    std::bitset<_POWER> rreversed = reverse_bitset(right_temp);
    std::bitset<_POWER> temp_mult;

    for (int i = 0; i < _POWER; i++) {
        for (int j = 0; j < _POWER; j++) {
            temp_mult[j] = get_sum_of_bits(lreversed & mult_matrix[j]);
            //std::cout << "First mult res: " << temp_mult << std::endl;
        }

        res_coefs[i] = get_sum_of_bits(temp_mult & rreversed);
        //std::cout << "Second mult res: " << res_coefs[i] << std::endl;
        cycle_shift_to_high(lreversed, 1);
        cycle_shift_to_high(rreversed, 1);
    }
    std::bitset<_POWER> res = reverse_bitset(res_coefs);
    return Poly(res);
}

//Poly Poly::operator*(const Poly& right) const {
//    std::bitset<_POWER> res_coefs;
//    std::bitset<_POWER> u_shifted = this->coefficients;
//    std::bitset<_POWER> v_shifted = right.coefficients;
//
//    std::bitset<_POWER> u = reverse_bitset(u_shifted);
//    std::bitset<_POWER> v = reverse_bitset(v_shifted);
//
//    for (size_t i = 0; i < _POWER; ++i) {
//        std::cout << "u before sh: " << u << std::endl;
//        std::cout << "v before sh: " << v << std::endl;
//        rcycle_shift(u, 1);
//        rcycle_shift(v, 1);
//        std::cout << "u after sh: " << u << std::endl;
//        std::cout << "v after sh: " << v << std::endl;
//
//        std::bitset<_POWER> temp_result;
//        for (size_t j = 0; j < _POWER; ++j) {
//            temp_result[j] = get_sum_of_bits(u_shifted & mult_matrix[j]) ; 
//        }
//        res_coefs[_POWER - i - 1] = get_sum_of_bits(temp_result & v_shifted) ;
//    }
//
//    return Poly(res_coefs);
//}

//operations
void Poly::cycle_shift_to_low(std::bitset<_POWER>& b, int i) {  
    b = (b << i) ^ (b >> _POWER - i);
}

void Poly::cycle_shift_to_high(std::bitset<_POWER>& b, int i) {
    b = (b >> i) ^ (b << _POWER - i);
}


Poly Poly::square() const {
    Poly res = *this;
    cycle_shift_to_high(res.coefficients, 1);
    return res;
}

bool Poly::get_sum_of_bits(const std::bitset<_POWER>& val){
    bool res = 0;
    for (int i = 0; i < _POWER; ++i) {
        res ^= val[i];
    }
    return res;
}

std::bitset<443> reverse_bitset(const std::bitset<443>& bits) {
    std::bitset<443> reversed;
    for (size_t i = 0; i < 443; ++i) {
        reversed[i] = bits[443 - 1 - i];
    }
    return reversed;
}

int Poly::trace(const Poly& poly) {
    return get_sum_of_bits(poly.coefficients);
}
