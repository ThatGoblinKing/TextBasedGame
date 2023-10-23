#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

static vector<string> getRawMap(){
    fstream newFile;
    int count = 0;
    vector<string> rawMap;

    newFile.open("Map.txt", ios::in);
    if (newFile.is_open()){
        string tp;
        while(getline(newFile, tp)){
            rawMap.push_back(tp);
        }
    }

    return rawMap;
}