#include <gtest/gtest.h>
#include "../include/gcd.h"

TEST(gcdTest, PositiveNumbers) {
    EXPECT_EQ(gcd(5, 10), 5); //НОД(5,10) = 5
    EXPECT_EQ(gcd(10, 20), 10); //НОД(10, 20) = 10
}

TEST(gcdTest, NegativeNumbers) {
    EXPECT_EQ(gcd(-5, -3), 0); //НОД не определен для отрицательных чисел
    EXPECT_EQ(gcd(-10, 5), 0); //НОД не определен для отрицательного числа
}

TEST(gcdTest, EdgeCases) {
    EXPECT_EQ(gcd(0, 0), 0); //НОД не определен для нуля
    EXPECT_EQ(gcd(0, 1), 0); //НОД(0,0) не определен для нуля
    EXPECT_EQ(gcd(100, 1), 1); //НОД любого числа и единицы всегда 1
    EXPECT_EQ(gcd(1, 100), 1); //НОД любого числа и единицы всегда 1
}

TEST(gcdTest, LargeNumbers) {
    EXPECT_EQ(gcd(1000000, 2000000), 1000000); // НОД (100000, 2000000) = 1000000
    EXPECT_EQ(gcd(32768, 16666), 2); // НОД(32768, 16666) = 2
    EXPECT_EQ(gcd(1024000, 16), 16); // НОД(1024000, 16) = 16
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}