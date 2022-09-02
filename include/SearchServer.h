#ifndef SEARCHENGINE_SEARCHSERVER_H
#define SEARCHENGINE_SEARCHSERVER_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "InvertedIndex.h"

using namespace std;

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
private:
    InvertedIndex _index;

public:
    /**
     * @param idx - в конструктор класса передаётся ссылка на класс InvertedIndex,
     * чтобы SearchServer мог узнать частоту слов встречаемых в запросе
     */
    explicit SearchServer(InvertedIndex& idx) : _index(idx){ };

    /**
     * Метод обработки поисковых запросов
     * @param queries_input - поисковые запросы взятые из файла requests.json
     * @return возвращает отсортированный список релевантных ответов для заданных запросов
     */
    vector<vector<RelativeIndex>> search(const vector<string>& queries_input);
};

#endif //SEARCHENGINE_SEARCHSERVER_H
