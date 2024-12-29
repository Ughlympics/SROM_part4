#pragma once

#include <string>
#include <bitset>
#include <iostream>
#include <stdexcept>


class Poly {
private:
	static const int _POWER = 443;
	static const int _DOBLE_POWER = 2 * _POWER;
	static std::bitset<_POWER> mult_matrix[_POWER];
	std::bitset<_POWER> coefficients;
	static bool multiplication_matrix ;
public:
	//Constructors
	Poly();
	Poly(unsigned _default_num);
	Poly(const Poly&);
	Poly(const std::string& binaryString);
	Poly(const std::bitset<_POWER>& bitset_coeffs);
	~Poly();

	//output
	std::string toBitString() const;

	//overloaded operators
	Poly& operator=(const Poly&);
	Poly operator+(const Poly&) const;
	Poly operator*(const Poly&) const;

	//operations
	static void cycle_shift_to_low(std::bitset<_POWER>& b, int i);
    static void cycle_shift_to_high(std::bitset<_POWER>& b, int i);
	static bool get_sum_of_bits(const std::bitset<_POWER>&);
	Poly square() const;
	static int trace(const Poly&);

	//helpers
	static void generate_mult_matrix(static std::bitset<_POWER> mult_matrix[_POWER]);
	static void print_matrix(static std::bitset<_POWER> mult_matrix[_POWER]);
	static std::bitset<_POWER>* get_mult_matrix() {
		return mult_matrix;
	}
};

std::bitset<443> reverse_bitset(const std::bitset<443>& bits);

