#include "InvertedIndex.h"

/**
 * вспомогательная функция для нахождения встречаемости слов
 * @param text - текст для поиска слов
 * @param doc_id - номер документа для вывода
 * @return частотный словарь встераемости слов в каждом документе
 */
map<string, map<size_t, size_t>> find_freq(const string& text, const size_t& doc_id) {
    map<string, map<size_t, size_t>> result;
    string current_word;
    for (auto &letter: text) {
        if (letter != ' ' && letter != '.' &&
            letter != ',' && letter != '!') {
            current_word += tolower(letter);
        }
        else {
            auto iterator = result.find(current_word);
            if (iterator == result.end()) {
                result.insert(pair<string, map<size_t, size_t>>(current_word, {{doc_id, 1}}));
            }
            else if (iterator->second.find((size_t)doc_id) == iterator->second.end()) {
                iterator->second.insert(pair<size_t, size_t>((size_t)doc_id, 1));
            }
            else {
                iterator->second.find(doc_id)->second += 1;
            }
            current_word = "";
        }
    }
    auto iterator = result.find(current_word);
    if (iterator == result.end()) {
        result.insert(pair<string, map<size_t, size_t>>(current_word, {{doc_id, 1}}));
    }
    else if (iterator->second.find((size_t)doc_id) == iterator->second.end()) {
        iterator->second.insert(pair<size_t, size_t>((size_t)doc_id, 1));
    }
    else {
        iterator->second.find(doc_id)->second += 1;
    }

    return result;
}

void InvertedIndex::UpdateDocumentBase(const vector<string>& input_docs) {
    docs = input_docs;
    vector<future<map<string, map<size_t, size_t>>>> threads;

    for (int i = 0; i < docs.size(); i++) {
        threads.emplace_back(async(launch::async, find_freq, docs[i], i));
    }

    for (auto & thread : threads) {
        auto s = thread.get();
        for (auto& [word, value] : s) {
            vector<Entry> result;
            for (auto& entry : value) {
                result.push_back({entry.first, entry.second});
            }
            auto iterator = freq_dictionary.find(word);
            if (iterator == freq_dictionary.end()){
                freq_dictionary.insert(pair<string, vector<Entry>>(word, result));
            }
            else {
                for (auto& i : result)
                    iterator->second.push_back(i);
            }
        }
    }
}

vector<Entry> InvertedIndex::GetWordCount(const string &word) const{
    auto iterator = freq_dictionary.find(word);
    if (iterator == freq_dictionary.end()) {
        return {};
    }
    return iterator->second;
}