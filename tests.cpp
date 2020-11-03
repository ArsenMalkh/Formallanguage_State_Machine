#include "Regular.h"
#include <gtest/gtest.h>

TEST(general_test, first) {
    std::string u = "abbbacbaa";
    std::string regexp = "ab+c+c.ab+.";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 3);
}

TEST(general_test, second) {
    std::string u= "ababacbababbcaaa";
    std::string regexp = "ac+b.*ab+c..";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 8);
}

TEST(general_test, third) {
    std::string u= "abbaa";
    std::string regexp = "acb..bab.c.*.ab.ba.+.+*a.";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 4);
}

TEST(general_tests, fourth) {
    std::string u= "babc";
    std::string regexp = "ab+c.aba.*.bac.+.*+*";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 2);
}
TEST(error_test, first) {
    std::string u= "abbababbabaa";
    std::string regexp = "acb..bab.c.*.ab.ba.+.+*a";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetInCorrection(), true);
}

TEST(error_test, second) {
    std::string u= "bbcababaa";
    std::string regexp = "ab+cc..a.bb";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetInCorrection(), true);
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
