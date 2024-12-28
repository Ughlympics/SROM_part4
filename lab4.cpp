#include "Poly.h"
#include <iostream>

int main()
{
    Poly f("10111010101110001100000101011010101001110101110100000010101100101100010001110010011010000010011100010110001000000100011110111001001010010111110101111101011100101001000011010001000101100010110000010100001000000100011010110011000100101000101010010100111010100000000011011111011110001111000111000010000101101000000010110110101101111110100010011111110010011011011011000001110100100111011100100100101011010111111110000101010000011100101110110111101");
    Poly sq = f.square();

    std::cout << "First pol: " << f.toBitString() << std::endl;
   /* std::cout << "Second pol: " << s.toBitString() << std::endl;
    std::cout << "ADDResult: " << add.toBitString() << std::endl;
    std::cout << "MULResult: " << mul.toBitString() << std::endl;
    std::cout << "SQResult: " << sq.toBitString() << std::endl;
    std::cout << "TRResult: " << trace_pol.toBitString() << std::endl;
    std::cout << "Inverse Result: " << inv.toBitString() << std::endl;
    std::cout << "Power Result: " << power.toBitString() << std::endl;*/
}

