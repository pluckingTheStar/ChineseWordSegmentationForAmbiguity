#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>
#include "preSplit.hpp"
using namespace std;

// load hashtable
multiHashList<string>& loadDict(){
    // read words and explanations
    multiHashList<string> *table = new multiHashList<string>(10, 1e5);
    fstream fp;
    fp.open("E:\\workspace\\C++\\c++source\\wordSegmentation\\dict.txt", ios::in);
    while (!fp.eof()){
        string line = "", word = "", explanation = "";
        getline(fp, line);
        if (line == "") continue;
        word = line.substr(0, line.find("=>"));
        explanation = line.substr(line.find("=>") + 2, line.length());
        // load into hash
        table->add(pair<string, string>(word, explanation));
    }
    fp.close();
    return (*table);
}

// load test sentences
vector<string>& testFile(){
    fstream fp;
    fp.open("E:\\workspace\\C++\\c++source\\wordSegmentation\\demo.txt", ios::in);
    vector<string> *testdata = new vector<string>;
    while (!fp.eof()){
        string line = "";
        getline(fp, line);
        if (line == "") continue;
        testdata->push_back(line);
    }
    fp.close();
    return (*testdata);
}


int main(){
    multiHashList<string> table = loadDict();
    vector<string> tesdata = testFile();
    // performence estimation
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1); // count time
    vector<vector<vector<string>>> res;
    for (int i = 0; i < tesdata.size(); i ++){
        string sen = tesdata[i];
        vector<string> splited = maxiumSplit(table, sen);
        vector<vector<string>> pathes = fullPath(splited, sen);
        res.push_back(pathes);
    }
    QueryPerformanceCounter(&t2); // end count
    double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart; 
    for (int i = 0; i < res.size(); i ++){
        for (int j = 0; j < res[i].size(); j ++){
            for (int k = 0; k < res[i][j].size(); k ++) cout << res[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
    }
    cout << time * 1e6 << "us" << endl; // 输出时间（单位：us）
    table.info();
    return 0;
}