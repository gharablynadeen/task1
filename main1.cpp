#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "FileManager.h"
#include<gtest/gtest.h>
using namespace std;

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
int main(){

    vector<vector<double>> data2;
    vector<string> columns2;
    vector<string> comments2;

    FileManager newFile;
    bool importFunction = newFile.importFunction("vsa_sample_iq_data.csv", data2, columns2, comments2);


    for (const auto &comment : comments2)
    {
        cout << comment << endl;
    }
    for (const auto &col : columns2)
    {
        cout << col << " ";
    }
    cout << endl;
    for (auto &row : data2)
    {
        for (auto &value : row)
        {
            cout << value << " ";
        }
        cout << endl;
    }
    cout << importFunction;

    unordered_map<string, std::variant<int, double, std::string>> extracted;
    bool extraction = newFile.commentExtraction(comments2, extracted);

    cout << endl
         << "--------------------------------------------------------------------------" << endl
         << extraction << endl;
    for (auto &[key, value] : extracted)
    {
        std::cout << key << ": ";
        std::visit([](auto &&arg)
                   { std::cout << arg; }, value);
        std::cout << "\n";
    }

}