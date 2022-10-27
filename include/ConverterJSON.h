#pragma once

#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

class ConverterJson {
private:
    json config_json;
    json requests_json;

public:
    ConverterJson();

    /**
     * метод проверяет наличие нужных json файлов
     */
    static bool check_json_files();

    /**
     * Метод получения наименования приложения
     * @return Возвращает название проекта
     */
    string GetName() const;

    /**
     * Метод получения версии приложения
     * @return возвращает версию приложения
     */
    int GetVersion() const;

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    vector<string> GetTextDocuments() const;

    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return Возвращает кол-во максимальных ответов на один запрос
    */
    int GetResponsesLimit() const;

    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    vector<string> GetRequests() const;

    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(const vector<vector<pair<int, float>>>& answers) const;
};
