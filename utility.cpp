#include "utility.h"
#include <iostream>
#include <algorithm>
#include <random>

std::string generateRandomString(int length, int seed){
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> distribution(0, 25);

    std::string randomString;

    for(int i = 0; i < length; i++){
        char randomChar = 'a' + distribution(rng);
        randomString += randomChar;
    }
    return randomString;
}

std::string generateRandomNumber(int length, int seed){
    std::mt19937 rng(seed);

    int minValue = std::pow(10, length - 1);
    int maxValue = std::pow(10, length) - 1;

    std::uniform_int_distribution<int> distribution(minValue, maxValue);

    int randomNumber = distribution(rng);
    return std::to_string(randomNumber);
}

std::string generateRandomCombo(int length, int seed){
    std::mt19937 rng(seed);

    const std::string characters = "0123456789012345678901234567890123456789abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<int> distribution(0, characters.size() - 1);

    std::string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += characters[distribution(rng)];
        }

    return randomString;
}

std::string encrypt(int inputNumber){

    std::string encryptedString;

    std::string randomCombo = generateRandomCombo(7, inputNumber); // seed is based on the input number so it's unique for dif numbers
    std::string randomLetters = generateRandomString(7, inputNumber);
    std::string randomNumbers = generateRandomNumber(8, inputNumber);

    // Middle section encryption
    inputNumber = (inputNumber+37)*131;

    std::string middleSection = std::to_string(inputNumber);
    std::reverse(middleSection.begin(), middleSection.end()); // reverse numbers

    middleSection.insert(2, randomNumbers.substr(0,2)); // add first 2 random numbers in position 2 of middleSection
    middleSection.insert(3, randomLetters.substr(0,2)); // add first 2 random letters in position 3 of middleSection

    encryptedString += randomCombo.substr(0,4);

    encryptedString += randomNumbers.substr(2,2);
    encryptedString += randomLetters.substr(2,3);
    encryptedString += randomNumbers.substr(4,1);

    encryptedString += middleSection;

    encryptedString += randomNumbers.substr(5,1);
    encryptedString += randomLetters.substr(5,2);
    encryptedString += randomNumbers.substr(6,2);

    encryptedString += randomCombo.substr(4,3);

    return encryptedString;
}

bool isWholeInteger(const std::string& str) {
    // Check if the string is empty
    if (str.empty()) {
        return false;
    }

    // Iterate through each character in the string
    for (int i = 0; i < str.length(); i++) {
        // Check if each character is a digit
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    // If all characters are digits, it's a whole integer
    return true;
}

int decrypt(std::string inputString){
    std::string str = inputString;

    if(str.size() < 26){
        std::cout << "Decryption: Invalid encryptedID - reason 0. Returning 0. " << std::endl;
        return 0;
    }


    str.erase(str.begin(), str.begin() + 10);
    str.erase(str.end() - 8, str.end());
    str.erase(str.begin() + 2, str.begin() + 6);
    std::reverse(str.begin(), str.end());

    float value;
    if(isWholeInteger(str)){
        value = std::stof(str); // if a whole integer, continue
    } else{
        std::cout << "Decryption: Invalid encryptedID - reason 1. Returning 0. " << std::endl;
        return 0;
    }

    value = (value/131) - 37;
    int valueInt = value;

    if(value == valueInt){ // if value is a whole number
        return value; // encryption ID is valid and original value has been found.
    } else{
        std::cout << "Decryption: Invalid encryptedID - reason 2. Returning 0. " << std::endl;
        return 0;
    }

    return 0;
}
