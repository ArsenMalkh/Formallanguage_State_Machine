#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include "Early.h"

using namespace std;

void Earley::Scan(vector<unordered_set<Situation, Situation::Hash>>& configs,
    char next_symbol, int config_index) {
    unordered_set<Situation, Situation::Hash> tmp_config_set;
    for (const auto& cur_situation : configs[config_index]) {
        if (cur_situation.cur_point >= cur_situation.right.size()) {
            continue;
        }
        if (cur_situation.right[cur_situation.cur_point] == next_symbol) {
            tmp_config_set.insert(Situation(cur_situation.left, cur_situation.right, cur_situation.start,
                cur_situation.cur_point + 1));
        }
    }
    configs.emplace_back(tmp_config_set);
}

void Earley::Predict(unordered_map<char, unordered_set<Grammar, Grammar::Hash>>& grammar_set,
    vector<unordered_set<Situation, Situation::Hash>>& configs, int config_index) {
    unordered_set<Situation, Situation::Hash> tmp_config_set;
    for (const auto& cur_situation : configs[config_index]) {
        if (cur_situation.cur_point >= cur_situation.right.size()) {
            continue;
        }
        char point_front_symbol = cur_situation.right[cur_situation.cur_point];
        if (grammar_set.find(point_front_symbol) != grammar_set.end()) {
            const auto& current_grammars = grammar_set[point_front_symbol];
            for (const auto& cur_grammar : current_grammars) {
                tmp_config_set.insert(Situation(cur_grammar, config_index, 0));
            }
        }
    }
    configs[config_index].merge(tmp_config_set);
}

void Earley::Complete(vector<unordered_set<Situation, Situation::Hash>>& configs, int config_index) {
    unordered_set<Situation, Situation::Hash> tmp_config_set;
    for (const auto& cur_situation : configs[config_index]) {
        if (cur_situation.cur_point < cur_situation.right.size()) {
            continue;
        }
        const auto& cur_config_set = configs[cur_situation.start];
        for (const auto& config : cur_config_set) {
            if (config.cur_point >= config.right.size()) {
                continue;
            }
            if (config.right[config.cur_point] == cur_situation.left) {
                tmp_config_set.insert(Situation(config.left, config.right,
                    config.start, config.cur_point + 1));
            }
        }
    }
    configs[config_index].merge(tmp_config_set);
}

void Earley::SetRule(unordered_map<char, unordered_set<Grammar, Grammar::Hash>>& grammar_set,
    const vector<Grammar>& grammars) {
    unordered_set<Grammar, Grammar::Hash> tmp_grammar_set;
    for (const auto& cur_grammar : grammars) {
        if (grammar_set.find(cur_grammar.left) != grammar_set.end()) {
            grammar_set[cur_grammar.left].insert(cur_grammar);
            continue;
        }
        tmp_grammar_set.clear();
        tmp_grammar_set.insert(cur_grammar);
        grammar_set.insert({ cur_grammar.left, tmp_grammar_set });
    }
    tmp_grammar_set.clear();
    tmp_grammar_set.insert(Grammar('.', string(1, 'S')));
    grammar_set.insert({ '.', tmp_grammar_set });
}

size_t Grammar::Hash::operator()(const Grammar& grammar_) const {
    return hash<size_t>()(hash<string>()(grammar_.right)
        + hash<char>()(grammar_.left));
}
bool Grammar::operator==(const Grammar& other) const {
    return left == other.left && right == other.right;
}
Grammar::Grammar(char left, const string& right)
    : left(left), right(right) {}

size_t Situation::Hash::operator()(const Situation& situation_) const {
    return hash<size_t>()(hash<string>()(situation_.right) + hash<char>()(situation_.left)
        + hash<int>()(situation_.cur_point + situation_.start));
}

Situation::Situation(char left, const string& right, int start, int index = 0)
    : Grammar(left, right), start(start), cur_point(index) {}

Situation::Situation(const Grammar& grammar, int start, int index) :
    Grammar(grammar), start(start), cur_point(index) {}

bool Situation::operator==(const Situation& other) const {
    return left == other.left && right == other.right
        && start == other.start && cur_point == other.cur_point;
}




EarleyAnalyse::EarleyAnalyse(const vector<Grammar>& grammars, char first_symbol) : first_symbol(first_symbol) {
    Earley::SetRule(grammar_set, grammars);
    unordered_set<Situation, Situation::Hash> tmp_config_set;
    tmp_config_set.insert(Situation('.', string(1, first_symbol), 0, 0));
    configs.emplace_back(tmp_config_set);
}
bool EarleyAnalyse::CompriseSymbol(const string& symbol) {
    configs.resize(1);
    return Build(first_symbol, symbol);
}

void EarleyAnalyse::CompletePredict(int config_index) {
    int previous_size = configs[config_index].size();
    int new_size = configs[config_index].size();
    do {
        Earley::Predict(grammar_set, configs, config_index);
        Earley::Complete(configs, config_index);
        previous_size = new_size;
        new_size = configs[config_index].size();
    } while (new_size != previous_size);
}

bool EarleyAnalyse::Build(char first_symbol, const string& symbol) {
    CompletePredict(0);
    for (int j = 1; j <= symbol.size(); ++j) {
        Earley::Scan(configs, symbol[j - 1], j - 1);
        CompletePredict(j);
    }
    Situation found_situation('.', string(1, first_symbol), 0, 1);
    return configs[symbol.size()].find(found_situation) != configs[symbol.size()].end();
}
