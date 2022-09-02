#include "../include/SearchServer.h"
#include <iostream>

vector<vector<RelativeIndex>> SearchServer::search(const vector<string> &queries_input) {
    vector<vector<RelativeIndex>> result(queries_input.size());

    for (int i = 0; i < queries_input.size(); i++) {
        map<string, int> search_words;
        map<int, int> doc_rev;

        {
            string current_word;
            for (auto &letter: queries_input[i]) {
                if (letter != ' ' && letter != '.' &&
                        letter != ',' && letter != '!') {
                    current_word += letter;
                }
                else {
                    auto iterator = search_words.find(current_word);
                    if (iterator == search_words.end()) {
                        search_words.insert(pair<string, int>(current_word, 1));
                    } else {
                        iterator->second += 1;
                    }
                    current_word = "";
                }
            }
            auto iterator = search_words.find(current_word);
            if (iterator == search_words.end()) {
                search_words.insert(pair<string, int>(current_word, 1));
            } else {
                iterator->second += 1;
            }
        }

        int max_rev = 0;
        for (auto& word : search_words) {
            for (auto& entry : _index.GetWordCount(word.first)) {
                auto iterator = doc_rev.find((int)entry.doc_id);
                if (iterator == doc_rev.end()) {
                    doc_rev.insert(pair<int, int>(entry.doc_id, entry.count * word.second));
                    if (entry.count * word.second > max_rev) max_rev = entry.count * word.second;
                }
                else {
                    iterator->second += (int)entry.count * word.second;
                    if (iterator->second > max_rev) max_rev = iterator->second;
                }
            }
        }

        for (auto& iterator : doc_rev) {
            result[i].push_back(RelativeIndex({(size_t)iterator.first, (float)iterator.second / (float)max_rev}));
        }

        for (int j = 1; j < result[i].size(); j++) {
            if (result[i][j].rank > result[i][j-1].rank) {
                for (int k = j; k > 0 && result[i][k].rank > result[i][k-1].rank; k--) {
                    RelativeIndex tmp = result[i][k];
                    result[i][k] = result[i][k-1];
                    result[i][k-1] = tmp;
                }
            }
        }
    }

    return result;
}