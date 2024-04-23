#include <gtest/gtest.h>
#include <cpu.hpp>

TEST(HelloTest, BasicAssertion){
    EXPECT_STRNE("Hello","World");
    EXPECT_EQ(7*6,42);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}