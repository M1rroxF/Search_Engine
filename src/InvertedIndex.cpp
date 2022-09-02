#include "../include/InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(const vector<string>& input_docs) {
    docs = input_docs;
    vector<future<map<string, map<size_t, size_t>>>> threads;
    mutex m_result;

    for (int i = 0; i < docs.size(); i++) {
        threads.emplace_back(async(launch::async, [this, i, &m_result](){
            map<string, map<size_t, size_t>> result;
            string current_word;
            for (auto &letter: docs[i]) {
                if (letter != ' ' && letter != '.' &&
                        letter != ',' && letter != '!') {
                    current_word += tolower(letter);
                }
                else {
                    auto iterator = result.find(current_word);
                    if (iterator == result.end()) {
                        result.insert(pair<string, map<size_t, size_t>>(current_word, {{i, 1}}));
                    }
                    else if (iterator->second.find((size_t)i) == iterator->second.end()) {
                        iterator->second.insert(pair<size_t, size_t>((size_t)i, 1));
                    }
                    else {
                        iterator->second.find(i)->second += 1;
                    }
                    current_word = "";
                }
            }
            auto iterator = result.find(current_word);
            if (iterator == result.end()) {
                result.insert(pair<string, map<size_t, size_t>>(current_word, {{i, 1}}));
            }
            else if (iterator->second.find((size_t)i) == iterator->second.end()) {
                iterator->second.insert(pair<size_t, size_t>((size_t)i, 1));
            }
            else {
               iterator->second.find(i)->second += 1;
            }

            return result;
        }
        ));
    }

    for (auto & thread : threads) {
        auto s = thread.get();
        for (auto& output : s) {
            vector<Entry> result;
            for (auto& entry : output.second) {
                result.push_back({entry.first, entry.second});
            }
            auto iterator = freq_dictionary.find(output.first);
            if (iterator == freq_dictionary.end()){
                freq_dictionary.insert(pair<string, vector<Entry>>(output.first, result));
            }
            else {
                for (auto& i : result)
                    iterator->second.push_back(i);
            }
        }
    }
}

vector<Entry> InvertedIndex::GetWordCount(const string &word) {
    if (freq_dictionary.find(word) == freq_dictionary.end()) {
        return {};
    }
    return freq_dictionary[word];
}