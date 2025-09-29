#include "../include/hex.h"
#include <iostream>
#include <string>
#include <cstring>
//#########################
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//#########################
size_t Hex::getSize() const {
    return size;
}

bool validChar(char c) {
    return (c >= '0' && c <= '9') ||
    (c >= 'A' && c <= 'F') ||
    (c >= 'a' && c <= 'f');
}

int Hex::charToInt(unsigned char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
}

unsigned char Hex::intToChar(int n) const {
    if (n < 0 || n > 15) throw std::invalid_argument("Invalid value");
    if (n < 10) return '0' + n;
    return 'A' + (n - 10);
}

Hex Hex::createFromDigits(unsigned char* digits_array, size_t digits_size) const {
        Hex result;
        
        result.digits = new unsigned char[digits_size];
        result.size = digits_size;
        
        for (size_t i = 0; i < digits_size; i++) {
            result.digits[i] = digits_array[i];
        }
        
        return result;
    }
//#########################
// КОНСТРУКТОРЫ И ДЕСТРУКТОР
//#########################
Hex::Hex() : digits(nullptr), size(0) {}

Hex::Hex(const char* hexStr) {
    if (hexStr == nullptr || hexStr[0] == '\0') {
        throw std::invalid_argument("Empty string");
    }
    for (int i = 0; hexStr[i] != '\0'; i++) {
        if (!validChar(hexStr[i])) {
            throw std::invalid_argument("Invalid characters");
        }
    }

    size = strlen(hexStr);
    digits = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        digits[i] = hexStr[size - 1 - i];
    }
}

Hex::Hex(const Hex& other) {
    size = other.size;
    digits = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        digits[i] = other.digits[i];
    }
}

Hex::~Hex() {
    delete[] digits;
    digits = nullptr;
    size = 0;
}

//#########################
//       ФУНКЦИОНАЛ
//#########################

//Print - вывод
std::string Hex::toString() const {
    if (size == 0 || digits == nullptr) {
        return "0";
    }
    
    std::string result;
    
    for (int i = size - 1; i >= 0; i--) {
        result += digits[i];
    }
    
    return result;
}

void Hex::print() const {
    std::cout << this->toString() << std::endl;
}

// Сравнения

int Hex::compare(const Hex& other) const {
    if (size != other.size) {
        return (size > other.size) ? 1 : -1;
    }
    for (int i = size - 1; i >= 0; i--) {
        int digit1 = charToInt(digits[i]);
        int digit2 = charToInt(other.digits[i]);
        if (digit1 != digit2) {
            return (digit1 > digit2) ? 1 : -1;
        }
    }
    return 0;
}

bool Hex::equals(const Hex& other) const {
    return compare(other) == 0;
}

bool Hex::isGreater(const Hex& other) const {
    return compare(other) > 0;
}

bool Hex::isLess(const Hex& other) const {
    return compare(other) < 0;
}

// Сумма и разность

Hex Hex::add(const Hex& other) const {

    size_t max_size = (size > other.size) ? size : other.size;
    max_size += 1;
    
    unsigned char* result_digits = new unsigned char[max_size];
    size_t result_size = 0;
    
    int i = 0;
    int carry = 0;
    
    while (i < size || i < other.size || carry > 0) {
        int digit1 = (i < size) ? charToInt(digits[i]) : 0;
        int digit2 = (i < other.size) ? charToInt(other.digits[i]) : 0;
        int sum = digit1 + digit2 + carry;
        
        carry = sum / 16;
        int resDigit = sum % 16;
        
        result_digits[result_size] = intToChar(resDigit);
        result_size++;
        i++;
    }
    Hex result = createFromDigits(result_digits, result_size);
    delete[] result_digits;
    
    return result;
}

Hex Hex::subtract(const Hex& other) const {
    if (this->compare(other) < 0) {
        throw std::underflow_error("Negative result");
    }
    unsigned char* result_digits = new unsigned char[size];
    size_t result_size = 0;
    
    int carry = 0;
    int i = 0;

    while (i < size) {
        int digit1 = charToInt(digits[i]);
        int digit2 = (i < other.size) ? charToInt(other.digits[i]) : 0;

        digit1 -= carry;
        carry = 0;

        if (digit1 < digit2) {
            digit1 += 16;
            carry = 1;
        }
        
        int diff = digit1 - digit2;
        result_digits[result_size] = intToChar(diff);
        result_size++;
        i++;
    }

    while (result_size > 1 && result_digits[result_size - 1] == '0') {
        result_size--;
    }
    
    Hex result = createFromDigits(result_digits, result_size);
    delete[] result_digits;
    
    return result;
}
