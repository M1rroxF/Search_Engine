#include "../include/ConverterJSON.h"

/**
 * вспомогательня функция для получения содержимого документов
 * @param fileName - название файла для чтения
 * @return содержимое файла с названием (fileName)
 */
string readFile(const string& fileName) {
    ifstream file(fileName);
    stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

ConverterJson::ConverterJson() {
    config_json = json::parse(readFile("config.json"));
    requests_json = json::parse(readFile("requests.json"));
}

string ConverterJson::GetName() {
    return config_json["config"]["name"];
}

int ConverterJson::GetVersion() {
    return config_json["config"]["version"];
}

vector<string> ConverterJson::GetTextDocuments()
{
    vector<string> files_content;
    for (auto &i : config_json["files"]) {
        files_content.push_back(readFile(i));
    }
    return files_content;

}

int ConverterJson::GetResponsesLimit() const
{
    return config_json["config"]["max_responses"];
}

vector<string> ConverterJson::GetRequests()
{
    return requests_json["requests"];
}

/**
 * вспомогательная функция получения чисел (001, 002, 003...)
 * @param num - число дла изменения кол-ва цифр
 * @param count - общее кол-во цифр для числа
 * @return возвращает число с определённым кол-ом цифр
 */
string getStrNum(const int& num, int count = 3) {
    string str_num = to_string(num);
    string ret_num;
    for (int i = 0; i < count-str_num.length(); i++) {
        ret_num += "0";
    }
    return ret_num + str_num;
}

void ConverterJson::putAnswers(vector<vector<pair<int, float>>> answers) {
    json answers_json;
    for (int i = 0; i < answers.size(); i++) {
        if (answers[i].empty()) {
            answers_json["answers"]["request" + getStrNum(i+1)]["result"] = false;
        }
        else {
            answers_json["answers"]["request" + getStrNum(i+1)]["result"] = true;
            vector<json> relevance;
            for (auto &j : answers[i]) relevance.push_back({{"docid", j.first}, {"rank", j.second}});
            answers_json["answers"]["request" + getStrNum(i+1)]["relevance"] = relevance;
        }
    }
    ofstream answers_file("answers.json");
    answers_file << setw(4) << setprecision(10) << answers_json;
    answers_file.close();
}