#include <gtest/gtest.h>
#include "Hex.h"
#include <stdexcept>

TEST(HexTest, DefaultConstructor) {
    Hex hex;
    EXPECT_EQ(hex.getSize(), 0);
    EXPECT_EQ(hex.toString(), "0");
}

TEST(HexTest, StringConstructor) {
    Hex hex("1A3F");
    EXPECT_EQ(hex.toString(), "1A3F");
    
    Hex hex2("0");
    EXPECT_EQ(hex2.toString(), "0");
}

TEST(HexTest, StringConstructorInvalid) {
    EXPECT_THROW(Hex("1G3F"), std::invalid_argument);
    EXPECT_THROW(Hex(""), std::invalid_argument);
}

TEST(HexTest, CopyConstructor) {
    Hex original("1A3F");
    Hex copy(original);
    EXPECT_EQ(copy.toString(), "1A3F");
    EXPECT_TRUE(original.equals(copy));
}

TEST(HexTest, Equals) {
    Hex hex1("1A3F");
    Hex hex2("1A3F");
    Hex hex3("2B");
    
    EXPECT_TRUE(hex1.equals(hex2));
    EXPECT_FALSE(hex1.equals(hex3));
}

TEST(HexTest, Compare) {
    Hex hex1("1A");
    Hex hex2("2B");
    Hex hex3("1A");
    
    EXPECT_TRUE(hex1.isLess(hex2));
    EXPECT_TRUE(hex2.isGreater(hex1));
    EXPECT_EQ(hex1.compare(hex3), 0);
}

TEST(HexTest, Add) {
    Hex hex1("1A");
    Hex hex2("2B");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.toString(), "45"); 
    
    Hex hex3("F");
    Hex hex4("1");
    Hex result2 = hex3.add(hex4);
    EXPECT_EQ(result2.toString(), "10");
}

TEST(HexTest, AddWithZero) {
    Hex hex1("1A3F");
    Hex hex2("0");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.toString(), "1A3F");
}

TEST(HexTest, Subtract) {
    Hex hex1("45");
    Hex hex2("2B");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.toString(), "1A"); // 45 - 2B = 1A
    
    Hex hex3("10");
    Hex hex4("1");
    Hex result2 = hex3.subtract(hex4);
    EXPECT_EQ(result2.toString(), "F");
}

TEST(HexTest, SubtractEqual) {
    Hex hex1("1A3F");
    Hex hex2("1A3F");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.toString(), "0");
}

TEST(HexTest, SubtractUnderflow) {
    Hex hex1("2B");
    Hex hex2("1A3F");
    EXPECT_THROW(hex1.subtract(hex2), std::underflow_error);
}


TEST(HexTest, LargeNumbers) {
    Hex hex1("FFFFFFFF");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.toString(), "100000000");
}

TEST(HexTest, ToString) {
    Hex hex("1A3F");
    EXPECT_EQ(hex.toString(), "1A3F");
}

TEST(HexTest, Print) {
    Hex hex("1A3F");
    testing::internal::CaptureStdout();
    hex.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1A3F\n");
}

TEST(HexTest, Immutability) {
    Hex original("1A3F");
    Hex other("2B");
    
    Hex sum = original.add(other);
    Hex diff = original.subtract(other);
    
    EXPECT_EQ(original.toString(), "1A3F");
    EXPECT_EQ(other.toString(), "2B");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}