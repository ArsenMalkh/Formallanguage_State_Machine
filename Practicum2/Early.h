#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <functional>
#include <iostream>


using namespace std;

class Grammar {
public:
    struct Hash {
        size_t operator()(const Grammar& grammar_) const;
    };
    char left;
    string right;
    Grammar(char left, const string& right);
    bool operator==(const Grammar& other) const;
};

class Situation : public Grammar {
public:
    struct Hash {
        size_t operator()(const Situation& situation_) const;
    };
    int start;
    int cur_point;
    Situation(char left, const string& right, int start, int index);
    Situation(const Grammar& grammar, int start, int index);
    bool operator==(const Situation& other) const;
};


class EarleyAnalyse {
public:
    EarleyAnalyse(const vector<Grammar>& grammars, char first_symbol);
    bool CompriseSymbol(const string& symbol);
private:
    bool Build(char first_symbol, const string& symbol);
    void CompletePredict(int config_index);
    char first_symbol;
    unordered_map<char, unordered_set<Grammar, Grammar::Hash>> grammar_set;
    vector<unordered_set<Situation, Situation::Hash>> configs;
};

class Earley {
public:
    static void Predict(unordered_map<char, unordered_set<Grammar, Grammar::Hash>>& grammar_set,
        vector<unordered_set<Situation, Situation::Hash>>& configs, int config_index);
    static void Scan(vector<unordered_set<Situation, Situation::Hash>>& configs, char next_symbol, int config_index);
    static void Complete(vector<unordered_set<Situation, Situation::Hash>>& configs, int config_index);
    static void SetRule(unordered_map<char, unordered_set<Grammar, Grammar::Hash>>& grammar_set,
        const vector<Grammar>& grammars);
};
