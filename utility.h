#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <algorithm>
#include <random>

std::string generateRandomString(int length, int seed);
std::string generateRandomNumber(int length, int seed);
std::string generateRandomCombo(int length, int seed);
bool isWholeInteger(const std::string& str);

std::string encrypt(int inputNumber);
int decrypt(std::string inputString);

#endif // UTILITY_H
