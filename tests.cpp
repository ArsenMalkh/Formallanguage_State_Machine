#include "Regular.h"
#include <gtest/gtest.h>

TEST(general_tests, first) {
    std::string u= "abbaa";
    std::string regexp = "acb..bab.c.*.ab.ba.+.+*a.";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 4);
}

TEST(general_tests, second) {
    std::string u= "babc";
    std::string regexp = "ab+c.aba.*.bac.+.*+*";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
