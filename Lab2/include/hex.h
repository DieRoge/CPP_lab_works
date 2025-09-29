#pragma once
#define HEX_H

#include <iostream>
#include <vector>
#include <string>

class Hex {

private:

    unsigned char* digits;
    size_t size;
    int charToInt(unsigned char c) const;
    unsigned char intToChar(int n) const;
    Hex createFromDigits(unsigned char* digits_array, size_t digits_size) const;

public:

    Hex();
    Hex(const char* hexStr);
    Hex(const Hex& other);
    ~Hex();

    size_t getSize() const;
    std::string toString() const;
    void print() const;

    int compare(const Hex& other) const;
    bool equals(const Hex& other) const;
    bool isGreater(const Hex& other) const;
    bool isLess(const Hex& other) const;

    Hex add(const Hex& other) const;
    Hex subtract(const Hex& other) const;

};
