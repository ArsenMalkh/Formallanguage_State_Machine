#include "Regular.h"


Regexp::Regexp(const std::string &str, const std::string &rpn) : str(str), reg_rpn(rpn) {
	incorrect = false;
	symbols.insert('.');
	symbols.insert('*');
    	symbols.insert('+');
    	Create();
    	if (regular_exp.size() != 1) {
        incorrect = true;
    	}
}
bool Regexp::GetInCorrection() const {
	return incorrect;
}

int Regexp::GetMaxSubstrLength() const {
    int max_length = -1;
    for (auto substr: substr_sets.top()) {
        int first = substr.first;
        int second = substr.second;
        if (second - first > max_length) {
            max_length = second - first;
        }
    }
	return max_length;
}

void Regexp::Create() {

    for (char elem: reg_rpn) {
        if (isalnum(elem)) {
            regular_exp.push(std::string(1, elem));
			std::set<std::pair<uint32_t, uint32_t >> h;
			substr_sets.push(h);
            for (size_t i = 0; i < str.size(); ++i) {
                if (str[i] == elem) {
                    substr_sets.top().emplace(i, i + 1);
                }
                if (elem == '1') {
                    substr_sets.top().emplace(i, i);
                }
            }
        } else {
            if (symbols.find(elem) == symbols.end() || ((elem == '+' || elem == '.') && regular_exp.size() < 2) || (elem == '*' && regular_exp.empty())) {
                incorrect = true;
                return;
            }


            if (elem == '+') {
                std::string merging_string = regular_exp.top();
                regular_exp.pop();
                regular_exp.top() += '+' + merging_string;
                regular_exp.top().insert(0, "(");
                regular_exp.top().push_back(')');
                std::set<std::pair<uint32_t, uint32_t >> merging_set = std::move(substr_sets.top());
                substr_sets.pop();
                substr_sets.top().insert(merging_set.begin(), merging_set.end());

            } 
			else if (elem == '.') {
                std::string merging_string = regular_exp.top();
                regular_exp.pop();
                regular_exp.top() += merging_string;
                std::set<std::pair<uint32_t, uint32_t >> snd_merging_set = std::move(substr_sets.top());
                substr_sets.pop();
                std::set<std::pair<uint32_t, uint32_t >> fst_merging_set = std::move(substr_sets.top());
                substr_sets.pop();
                substr_sets.push(std::set<std::pair<uint32_t, uint32_t >>());
                for (auto first_pair: fst_merging_set) {
                    for (auto second_pair: snd_merging_set) {
                        if (first_pair.second == second_pair.first) {
                            substr_sets.top().emplace(first_pair.first, second_pair.second);
                        }
                    }
                }


            } 
			else if(elem == '*'){
                regular_exp.top().insert(0, "(");
                regular_exp.top() += ")*";
                for (size_t i = 0; i <= str.size(); ++i) {
                    substr_sets.top().emplace(i, i); /* empty substrings are fine too */
                }

                bool is_end;
                do {
                    is_end = true;
                    std::set<std::pair<uint32_t, uint32_t >> new_substrings;
                    for (auto first_pair: substr_sets.top()) {
                        for (auto second_pair: substr_sets.top()) {
                            if ((first_pair.second - first_pair.first == 0)
                                || (second_pair.second - second_pair.first == 0)) {
                                continue;
                            }
                            if (first_pair.second == second_pair.first) {
                                std::pair<uint32_t, uint32_t> cur;
								cur.first = first_pair.first;
								cur.second = second_pair.second;
                                if (substr_sets.top().find(cur) == substr_sets.top().end()) {
                                    new_substrings.emplace(first_pair.first, second_pair.second);
                                    is_end = false;
                                }
                            }
                        }
                    }
                    substr_sets.top().insert(new_substrings.begin(), new_substrings.end());
                } while (!is_end);
            }

        }

    }
}
