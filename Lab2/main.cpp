#include "include/hex.h"
#include "iostream"

int main() {
    Hex a("1A3F");
    Hex b(a);
    std::cout << b.toString() << std::endl;
    std::cout << a.compare(b) << std::endl;
    
    return 0;
}