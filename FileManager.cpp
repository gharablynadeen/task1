
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "FileManager.h"
using namespace std;

void FileManager::export_func(std::string filename, vector<vector<double>> &data, vector<std::string> columns, vector<std::string> comments)
{
    // 1- check if the file path exists
    ofstream myfile;
    myfile.open(filename);

    for (int i = 0; i < comments.size(); i++)
    {
        if (comments[i] == "#")
            myfile << endl
                   << "#";
        else
            myfile << comments[i] << endl;
    }

    for (int i = 0; i < columns.size(); i++)
    {
        myfile << columns[i] << ",";
    }
    myfile << endl;

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            myfile << data[i][j] << ",";
        }
        myfile << endl
               << endl;
    }

    myfile.close();
}

// 1- Modify parameters to take the full file path
// 2- Check if the file exists in the given path or not

// bool import_func(filename, outputs)
bool FileManager::import_func(std::string filename, vector<vector<double>> &data, vector<std::string> &column, vector<std::string> &comments)
{

    // std::string headers ;
    // vector<vector<double>> data;
    int col = 0;
    ifstream input(filename);
    int i = 0; // rows for data vector
    if (!input.is_open())
    {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return false;
        exit(EXIT_FAILURE);
    }

    if (input.peek() == ifstream::traits_type::eof())
    {
        cout << "File is empty.";
        return false;
    }

    std::string line;

    // getline(input,line);
    while (getline(input, line))
    {
        if (line[0] == '#')
        {
            comments.push_back(line);
        }
        else if (!isdigit(line[0]))
        {
            std::string parsed = "";
            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] != ',')
                {
                    parsed += line[i];
                }
                else
                {
                    column.push_back(parsed);
                    parsed = "";
                }
            }
        }
        else
        {

            std::string parsed = "";
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] != ',')
                {
                    parsed += line[j];
                }
                else
                {

                    col < column.size() ? col = col : col = 0;
                    data[i][col] = stod(parsed);
                    parsed = "";
                    i++;
                    col++;
                }
            }
        }
        return true;
    }
}
