#include "SearchServer.h"

/**
 * Вспомагательная функция для разделения текста
 * @param text - текст
 * @return возвращает слова(string) с их количеством(int) в тексте
 */
map<string, int> split(const string& text) {
    map<string, int> result;

    string current_word;
    for (auto &letter: text) {
        if (letter != ' ' && letter != '.' &&
            letter != ',' && letter != '!') {
            current_word += letter;
        }
        else {
            auto iterator = result.find(current_word);
            if (iterator == result.end()) {
                result.insert(pair<string, int>(current_word, 1));
            } else {
                iterator->second += 1;
            }
            current_word = "";
        }
    }
    auto iterator = result.find(current_word);
    if (iterator == result.end()) {
        result.insert(pair<string, int>(current_word, 1));
    } else {
        iterator->second += 1;
    }

    return result;
}

/**
 * сортирует в порядке возрастания класс T
 * @tparam T - класс по которому идёт сравнивание
 * @param t - вектор класса T для сортировки
 */
template <class T>
void sort(vector<T>& t) {
    for (int j = 1; j < t.size(); j++) {
        if (t[j] > t[j-1]) {
            for (int k = j; k > 0 && t[k] > t[k-1]; k--) {
                T tmp = t[k];
                t[k] = t[k-1];
                t[k-1] = tmp;
            }
        }
    }
}

vector<vector<RelativeIndex>> SearchServer::search(const vector<string> &queries_input) {
    vector<vector<RelativeIndex>> result(queries_input.size());

    for (int i = 0; i < queries_input.size(); i++) {
        map<string, int> search_words = split(queries_input[i]);
        map<int, int> doc_rev;

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

        sort<RelativeIndex>(result[i]);
    }

    return result;
}