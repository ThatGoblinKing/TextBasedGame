#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Rooms.cpp"
using namespace std;

static vector<string> doTheThing(){
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

static Room parseLine(string line){
    string segment[7];
    string delimeter = "|"
    for (int i = 0; i < 7; i++){
        segment[i] = line.substr(0, line.find(delimeter));
    }
    line.erase(0, line.find(delimeter) + delimeter.lengh());
}

static int printLines(vector<string> rawMap){
    for (string line : rawMap) {
        cout << line;
    }
    return 0;
}