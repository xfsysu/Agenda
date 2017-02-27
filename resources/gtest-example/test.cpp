//test.cpp
#include <gtest/gtest.h>
#include <stdexcept>
#include "division.h"

TEST(divisionTest, divisorNotZero) {
	EXPECT_EQ(2, myns::divide(8, 4));
}

TEST(divisionTest, divisorZero) {
	EXPECT_THROW(myns::divide(1, 0), std::domain_error);
}
//g++ division.cpp test.cpp -o test -I./gtest-1.6.0/include -L./gtest-1.6.0/lib/.libs -Wl,-rpath=./gtest-1.6.0/lib/.libs -lgtest -lgtest_main -lpthread
