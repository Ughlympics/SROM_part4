#pragma once

#include <string>
#include <bitset>
#include <iostream>


class Poly {
private:
	static const int _POWER = 443;
	static const int _DOBLE_POWER = 2 * _POWER;
	static std::bitset<_POWER> mult_matrix[_POWER];
	std::bitset<_POWER> coefficients;
	static bool multiplication_matrix;
public:
	//Constructors
	Poly();
	Poly(unsigned _default_num);
	Poly(const Poly&);

	//helpers
	void generate_mult_matrix(static std::bitset<_POWER> mult_matrix[_POWER]);
	void print_mult_matrix(static std::bitset<_POWER> mult_matrix[_POWER]);
};

