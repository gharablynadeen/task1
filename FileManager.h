#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <variant>
#include <algorithm>

using namespace std;

class FileManager
{
public:
    void exportFunction(std::string fileName, vector<vector<double>> &data, vector<std::string> columns, vector<std::string> comments);

    bool importFunction(std::string fileName, vector<vector<double>> &data, vector<std::string> &column, vector<std::string> &comments);

    bool commentExtraction(vector<std::string> &comments, unordered_map<std::string, std::variant<int, double, std::string>> &extracted);
};

#endif
