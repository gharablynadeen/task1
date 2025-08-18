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

bool FileManager::import_func(std::string filename, vector<vector<double>> &data, vector<std::string> &column, vector<std::string> &comments)
{

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
    bool after_comments = false;
    while (getline(input, line) || !(input.eof()))
    {
        if (line.empty())
            continue; // skip empty lines
        if (line[0] == '#')
        {
            comments.push_back(line);
            continue;
        }

        else if (!after_comments)
        {
            std::string parsed = "";
            int i =0 ;
            for (i ; i < line.size(); i++)
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
            if (i == line.size() )
                {
                    column.push_back(parsed);
                }
            after_comments = true; // we have read the comments and columns
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

    for (int i = 0; i < comments.size(); i++) //hayakhod comments men 0 l i-1

    {
        int position = comments[i].find('=');
        if (position == std::string::npos) // if '=' is not found in the comment
            continue;                      // skip this comment

        int leftpointer = position - 1; 
        int rightpointer = position + 1;
        bool second_space_left = false; // flags when the whole word is parsed 
        bool second_space_right = false;

        bool reached_word_left = false; //flags when first character of the word is reached
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
                // key = comments[i][leftpointer] + key; // check extra space
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
           
           
        }



       while (rightpointer > position && !second_space_right)
        {


            if (comments[i][rightpointer] == ' ' && !reached_word_right)
            {
                rightpointer++;
            }

           else if ((comments[i][rightpointer] == ' '  || comments[i][rightpointer] == '\n' || comments[i][rightpointer] == '\r' ||comments[i][rightpointer] == '\000') && reached_word_right)
            {
                second_space_right = true;
                std::reverse(value.begin(), value.end());
                 extracted[key] = value;
            }

            else if (comments[i][rightpointer] != ' '&& !reached_word_right)
            {
                value = comments[i][rightpointer] + value;
                reached_word_right = true;
                rightpointer++;
            }

            else if (reached_word_right && comments[i][rightpointer] != ' ')
            {
                value = comments[i][rightpointer] + value;
                rightpointer++;
            }

        if (value.empty() || key.empty())
            continue;
    }


}
return true;
}

