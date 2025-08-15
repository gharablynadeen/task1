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
{ // 1- check if the file path exists
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
    if (!input.is_open())
    {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return false;
        exit(EXIT_FAILURE);
    }

    if (input.peek() == ifstream::traits_type::eof()) // next to read (which is first to read) is nothing
    {
        cout << "File is empty.";
        return false;
    }

    std::string line;
    vector<double> row;

    while (getline(input, line) || !(input.eof()))
    {
        if (line.empty())
            continue; // skip empty lines
        if (line[0] == '#')
        {
            comments.push_back(line);
        }
        else if (!isdigit(line[0]))
        {
            std::string parsed = "";
            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] == ','||line[i] == '\n' || line[i] == '\r')
                {
                  column.push_back(parsed);
                    parsed = "";   
                }
                else
                {
                   

                    parsed += line[i];
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
                    
                    
                        row.push_back(stod(parsed));
                        col++;
                        parsed = "";
                    
                    if (col >= column.size())
                    {
                        data.push_back(row);
                        row.clear();
                        //row.push_back(stod(parsed));
                        col = 0;
                        parsed = "";
                    }
                }
            }
        }

    }
    
    input.close();
    return true;
}

bool FileManager::comment_extraction(vector<std::string> &comments, unordered_map<std::string, std::variant<int, double, std::string>> &extracted )
{
    if (comments.empty())
    {
        cout << "No comments found." << endl;
        return false;
    }

    for (int i = 0; i < comments.size(); i++)

    {
        int position = comments[i].find('=');
        if (position == std::string::npos) // if '=' is not found in the comment
            continue;                      // skip this comment

        int leftpointer = position - 1;
        int rightpointer = position + 1;
        bool second_space_left = false;
        bool second_space_right = false;

        bool reached_word_left = false;
        bool reached_word_right = false;
        string key = "";
        string value = "";

        comments[i][leftpointer] == ' ' ? reached_word_left = false : reached_word_left = true;
        comments[i][rightpointer] == ' ' ? reached_word_right = false : reached_word_right = true;

        while (leftpointer > 0 && !second_space_left)
        {


            if (comments[i][leftpointer] == ' ' && !reached_word_left)
            {
                leftpointer--;
            }

            else if (comments[i][leftpointer] == ' ' && reached_word_left)
            {
                second_space_left = true;
                leftpointer--;
            }

            else if (comments[i][leftpointer] != ' '&& !reached_word_left)
            {
                key = comments[i][leftpointer] + key;
                reached_word_left = true;
                leftpointer--;
            }
            else if (reached_word_left && comments[i][leftpointer] != ' ')
            {
                key = comments[i][leftpointer] + key;
                leftpointer--;
            }
           
           
            // This part is commented out because it was not functioning as intended

            // if (comments[i][leftpointer] != ' ' && !second_space_left)
            // {
            //     key = comments[i][leftpointer] + key;
            //     reached_word_left = true;
            //     leftpointer--;
            // }

            // else if (reached_word_left && comments[i][leftpointer] == ' ')
            // {
            //     second_space_left = true;
            //     leftpointer--;
            // }

            // else
            // {
            //     leftpointer--;
            // }
        }

       while (rightpointer > 0 && !second_space_right)
        {


            if (comments[i][rightpointer] == ' ' && !reached_word_right)
            {
                rightpointer++;
            }

            else if (comments[i][rightpointer] == ' ' && reached_word_right)
            {
                second_space_right = true;
                rightpointer++;
            }

            else if (comments[i][rightpointer] != ' '&& !reached_word_right)
            {
                key = comments[i][rightpointer] + key;
                reached_word_right = true;
                rightpointer++;
            }
            else if (reached_word_right && comments[i][rightpointer] != ' ')
            {
                key = comments[i][rightpointer] + key;
                rightpointer++;
            }

        if (value.empty() || key.empty())
            continue;
        std::reverse(value.begin(), value.end());
        extracted[key] = value;
    }
    return true;
}

