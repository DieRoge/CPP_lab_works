#include "../include/gcd.h"

int gcd(int a, int b) {
    if((a < 1) || (b < 1)){
        return 0;
    }
    while((a != 0) && (b != 0)) {
        if (a > b) {
            a = a % b;
        } 
        else {
            b = b % a;
        }
        }
    return a + b;
}
