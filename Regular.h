#pragma once
#include <iostream>
#include <unordered_set>
#include <set>
#include <stack>
#include <string>
#include <cstdint>

class Regexp {
private:
    void Create();    
    std::stack<std::string> regular_exp;
    std::stack<std::set<std::pair<uint32_t, uint32_t >>> substr_sets;
    const std::string str;
    const std::string reg_rpn;
    std::unordered_set<char> symbols;
    bool incorrect;

public:
    Regexp(const std::string &str, const std::string& rpn);
    int GetMaxSubstrLength() const;
    bool GetInCorrection() const;

};
