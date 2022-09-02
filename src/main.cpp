#include "../include/ConverterJSON.h"
#include "../include/SearchServer.h"

#include <iostream>

#define LAST_VER 1

using namespace std;

int main() {
    ConverterJson converterJson;
    cout << "|=======Start=======|" << endl;
    cout << "Name: " << converterJson.GetName() << endl;
    cout << "Last Version: " << LAST_VER << endl;
    cout << "Current Version: " << converterJson.GetVersion() << endl;
    if (converterJson.GetVersion() == LAST_VER) {
        cout << "compatibility: Y" << endl;
    }
    else {
        cout << "compatibility: N" << endl;
        cout << "|========End========|" << endl;
        exit(0);
    }
    cout << "|======Search=======|" << endl;
    InvertedIndex index;
    index.UpdateDocumentBase(converterJson.GetTextDocuments());
    SearchServer searchServer(index);

    vector<vector<RelativeIndex>> output = searchServer.search(converterJson.GetRequests());
    vector<vector<pair<int, float>>> rev(output.size());

    for (int i = 0; i < output.size(); i++) {
        int size_rev = (output[i].size() > converterJson.GetResponsesLimit() ?
                converterJson.GetResponsesLimit() : (int)output[i].size());
        rev[i].resize(size_rev);
        for (int j = 0; j < size_rev; j++) {
            rev[i][j] = pair<int, float>(output[i][j].doc_id, output[i][j].rank);
        }
    }

    converterJson.putAnswers(rev);
    cout << "|========End========|" << endl;
}