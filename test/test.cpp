#include "pch.h"

// Test bàsic para verificar que Google Test funciona
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

// Tests addicionals de sanitat
TEST(BasicTests, SimpleArithmetic) {
  EXPECT_EQ(2 + 2, 4);
  EXPECT_NE(2 + 2, 5);
}

TEST(BasicTests, BooleanLogic) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(!true);
}

TEST(BasicTests, StringComparison) {
  std::string s1 = "Hello";
  std::string s2 = "Hello";
  EXPECT_EQ(s1, s2);
}

// Test per verificar que els includes funcionen
TEST(FrameworkTests, GoogleTestIncluded) {
  int x = 42;
  EXPECT_EQ(x, 42);
  EXPECT_GT(x, 0);
  EXPECT_LT(x, 100);
}