#include "Early.h"
#include <gtest/gtest.h>

const std::string epsilon = "";

TEST(general_test, first) {
    std::vector<Grammar> grammars;
    grammars.emplace_back(Grammar('S', "cTc"));
    grammars.emplace_back(Grammar('S', "a"));
    grammars.emplace_back(Grammar('T', "Uc"));
    grammars.emplace_back(Grammar('T', epsilon));
    grammars.emplace_back(Grammar('U', "bSa"));
    grammars.emplace_back(Grammar('U', "b"));

    EarleyAnalyse parser(grammars, 'S');
    std::string word = "cbcbcbaaccaccacc";
    EXPECT_EQ(parser.CompriseSymbol(word), true);	
}

TEST(general_test, second) {
    std::vector<Grammar> grammars;
    grammars.emplace_back(Grammar('S', "cT"));
    grammars.emplace_back(Grammar('S', "bS"));
    grammars.emplace_back(Grammar('T', "Uc"));
    grammars.emplace_back(Grammar('T', "cTa"));
    grammars.emplace_back(Grammar('U', "cV"));
    grammars.emplace_back(Grammar('U', "bUb"));
    grammars.emplace_back(Grammar('V', "bVc"));
    grammars.emplace_back(Grammar('V', "a"));

    EarleyAnalyse parser(grammars, 'S');
    std::string word = "bcccbbbbaccccca";
    EXPECT_EQ(parser.CompriseSymbol(word), true);
}

TEST(general_test, third) {
    std::vector<Grammar> grammars;
    grammars.emplace_back(Grammar('S', "cT"));
    grammars.emplace_back(Grammar('S', "bS"));
    grammars.emplace_back(Grammar('T', "Uc"));
    grammars.emplace_back(Grammar('T', "cTa"));
    grammars.emplace_back(Grammar('U', "cV"));
    grammars.emplace_back(Grammar('U', "bUb"));
    grammars.emplace_back(Grammar('V', "bVc"));
    grammars.emplace_back(Grammar('V', "a"));

    EarleyAnalyse parser(grammars, 'S');
    std::string word = "bbbbbccccbaccaaa";
    EXPECT_EQ(parser.CompriseSymbol(word), false);
}

TEST(general_test, fourth) {
    std::vector<Grammar> grammars;
    grammars.emplace_back(Grammar('S', "U+S"));
    grammars.emplace_back(Grammar('S', "a"));
    grammars.emplace_back(Grammar('U', "U"));
    grammars.emplace_back(Grammar('U', "V"));
    grammars.emplace_back(Grammar('U', "U*V"));
    grammars.emplace_back(Grammar('V', "(U+W)"));
    grammars.emplace_back(Grammar('V', "a"));
    grammars.emplace_back(Grammar('V', "b"));
    grammars.emplace_back(Grammar('W', "c"));
    grammars.emplace_back(Grammar('W', "V"));
    grammars.emplace_back(Grammar('W', "a"));
    EarleyAnalyse parser(grammars, 'S');
    std::string word = "b*a*b*(b*b+c)+a";
    EXPECT_EQ(parser.CompriseSymbol(word), true);
}

TEST(general_test, fifth) {
    std::vector<Grammar> grammars;
    grammars.emplace_back(Grammar('S', "U+S"));
    grammars.emplace_back(Grammar('S', "a"));
    grammars.emplace_back(Grammar('U', "U"));
    grammars.emplace_back(Grammar('U', "V"));
    grammars.emplace_back(Grammar('U', "U*V"));
    grammars.emplace_back(Grammar('V', "(U+W)"));
    grammars.emplace_back(Grammar('V', "a"));
    grammars.emplace_back(Grammar('V', "b"));
    grammars.emplace_back(Grammar('W', "c"));
    grammars.emplace_back(Grammar('W', "1"));
    grammars.emplace_back(Grammar('W', "a"));
    EarleyAnalyse parser(grammars, 'S');
    std::string word = "a+b*b*(a+c)+a+1";
    EXPECT_EQ(parser.CompriseSymbol(word), false);
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
