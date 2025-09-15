#include <iostream>
#include "include/gcd.h"

int main() {
    int a, b, res;
    std::cout << "Введите 2 числа через пробел. Если НОД не определен - программа выведет 0" << std::endl;
    std::cin >> a >> b;
    res = gcd(a, b);
    std::cout << res << std::endl;
    return 0;
    } 