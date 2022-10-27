#include "ConverterJSON.h"

class Items_not_found : public exception {
    const char* what() const noexcept override {
        return "Error: some items were not found in json files";
    }
};

/**
 * вспомогательня функция для получения содержимого документов
 * @param fileName - название файла для чтения
 * @return содержимое файла с названием (fileName)
 */
string readFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: file \"" << fileName << "\" not found!" << endl;
        file.close();
        exit(1);
    }
    stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}

ConverterJson::ConverterJson() {
    try {
        config_json = json::parse(readFile("config.json"));
        if (!config_json["config"].count("name") or !config_json["config"].count("version")
                or !config_json["config"].count("max_responses") or !config_json.count("files")) {
            throw Items_not_found();
        }

        requests_json = json::parse(readFile("requests.json"));
        if (!requests_json.count("requests")) {
            throw Items_not_found();
        }
    }
    catch (json::parse_error& e) {
        cerr << "Error: The syntax of json documents is corrupted!" << endl;
        exit(1);
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        exit(1);
    }
}

bool ConverterJson::check_json_files() {
    bool exit = false;

    ifstream config_file("config.json");
    if (!config_file.is_open()) {
        exit = true;
        ofstream config_create("config.json");

        json config_json;
        config_json["config"]["name"] = "";
        config_json["config"]["version"] = 0;
        config_json["config"]["max_responses"] = 5;
        config_json["files"] = {"your file001", "your file002"};

        config_create << setw(2) << config_json;
        config_create.close();
    }
    config_file.close();

    ifstream requests_file("requests.json");
    if (!requests_file.is_open()) {
        exit = true;
        ofstream requests_create("requests.json");

        json requests_json;
        requests_json["requests"] = {"your request001", "your request002"};
        requests_create << setw(2) << requests_json;

        requests_create.close();
    }
    requests_file.close();

    return exit;
}

string ConverterJson::GetName() const {
    return config_json["config"]["name"];
}

int ConverterJson::GetVersion() const {
    return config_json["config"]["version"];
}

vector<string> ConverterJson::GetTextDocuments() const
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

vector<string> ConverterJson::GetRequests() const
{
    return requests_json["requests"];
}

/**
 * вспомогательная функция получения чисел (001, 002, 003...)
 * @param num - число дла изменения кол-ва цифр
 * @return возвращает число с определённым кол-ом цифр
 */
string getStrNum(int num) {
    string str_num = to_string(num);
    string ret_num;
    for (int i = 0; i < 3-str_num.length(); i++) {
        ret_num += "0";
    }
    return ret_num + str_num;
}

void ConverterJson::putAnswers(const vector<vector<pair<int, float>>>& answers) const{
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
    if (answers_file.is_open()) {
        answers_file << setw(2) << answers_json;
    }
    else {
        cerr << "Error: file \"answers.json\" unavailable" << endl;
        exit(1);
    }
    answers_file.close();
}