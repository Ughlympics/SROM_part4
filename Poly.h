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
	static void lcycle_shift(std::bitset<_POWER>& b, int i);
    static void rcycle_shift(std::bitset<_POWER>& b, int i);
	Poly square() const;

	//helpers
	void generate_mult_matrix(static std::bitset<_POWER> mult_matrix[_POWER]);
	void print_mult_matrix(static std::bitset<_POWER> mult_matrix[_POWER]);
};

