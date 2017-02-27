#include "gtest/gtest.h"
#include "foo.h"
TEST(foo, max)
{
EXPECT_EQ(2, max(2,-1));
EXPECT_EQ(3, max(2,3));
}
//the main function is not must
int main(int argc, char** argv)
{
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}

//g++ -g foo_test.cpp -o foo_test -I./gtest-1.6.0/include -L./gtest-1.6.0/lib/.libs -Wl,-rpath=./gtest-1.6.0/lib/.libs -lgtest -lgtest_main -lpthread
//g++ division.cpp test.cpp -o test -I./gtest-1.6.0/include -L./gtest-1.6.0/lib/.libs -Wl,-rpath=./gtest-1.6.0/lib/.libs -lgtest -lgtest_main -lpthread
