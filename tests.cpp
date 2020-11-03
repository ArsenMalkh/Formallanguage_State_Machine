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

TEST(general_tests, third) {
    std::string u= "hoqeirjkabcbbbabaaabbabababcbbababddfdwwerdsfasaaababacasnnb";
    std::string regexp = "ab+*c.ab+*.";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstring(), "bbbabaaabbabababcbbabab");
}

TEST(general_tests, fotrh) {
    std::string u= "nonsence";
    std::string regexp = "ab+*c.ab+*.";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetCommonRegexp(), "((a+b))*c((a+b))*");
}

TEST(general_tests, fifth) {
    std::string u= "otioirweoirewoirewo";
    std::string regexp = "ab+*c.ab+*.";
    Regexp parser(u, regexp);
    std::cout << parser.GetMaxSubstring() << "\n";
    EXPECT_EQ(parser.GetMaxSubstring(), "");
}

TEST(error_tests, first) {
    std::string u= "abaidgaibac";
    std::string regexp = "+ab";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetCommonRegexp(), "");
}

TEST(error_tests, second) {
    std::string u= "aidafoasd";
    std::string regexp = "a.b";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstring(), "Incorrect input: regexp is wrong");
}

TEST(error_tests, third) {
    std::string u= "ab+*c.ab+*.abc";
    std::string regexp = "a.b";
    Regexp parser(u, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), std::numeric_limits<int32_t>::max());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
