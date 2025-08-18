#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "FileManager.h"
using namespace std;

int main()
{
    vector<vector<double>> data{

        {1.00, 0.809016994, 0.587785252},

        {2.0006, 0.309016994, 0.951056516},
        
        {1.00, 0.809016994, 0.587785252},
    
    {1.00, 0.809016994, 0.587785252}};

    vector<string> columns = {"it", "is", "done"};
    vector<string> comments = {"# I hope all is well", "# I also hope all is well"};

    FileManager filem;

    filem.export_func("C:/Users/Nadeen/Documents/GitHub/task1/trial.csv", data, columns, comments);

    vector<vector<double>> data2;
    vector<string> columns2;
    vector<string> comments2;
    bool import_func = filem.import_func("vsa_sample_iq_data.csv", data2, columns2, comments2);
    
   
    
    for (const auto &comment : comments2) {
        cout << comment << endl;
    }
 for (const auto &col : columns2) {
        cout << col << " ";
    }
    cout << endl;
    for (auto &row : data2) {
        for (auto &value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    cout << import_func;

    unordered_map<string, std::variant<int, double, std::string>> extracted;
    bool extraction = filem.comment_extraction(comments2, extracted);


     cout <<endl<< "--------------------------------------------------------------------------" << endl<<extraction << endl;
    for (auto& [key, value] : extracted) {
    std::cout << key << ": ";
    std::visit([](auto&& arg) { std::cout << arg; }, value);
    std::cout << "\n";
}



}