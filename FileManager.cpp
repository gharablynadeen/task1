#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "FileManager.h"
using namespace std;

void FileManager::exportFunction(std::string fileName, vector<vector<double>> &data, vector<std::string> columns, vector<std::string> comments)
{
    ofstream myFile;
    myFile.open(fileName);

    for (int i = 0; i < comments.size(); i++)
    {
        if (comments[i] == "#")
            myFile << endl
                   << "#";
        else
            myFile << comments[i] << endl;
    }

    for (int i = 0; i < columns.size(); i++)
    {
        myFile << columns[i] << ",";
    }
    myFile << endl;

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            myFile << data[i][j] << ",";
        }
    }

    myFile.close();
}



bool FileManager::importFunction(std::string fileName, vector<vector<double>> &data, vector<std::string> &column, vector<std::string> &comments)
{
    int col = 0;
    ifstream input(fileName);
    if (!input.is_open())
    {
        cerr << "Could not open the file - '" << fileName << "'" << endl;
        return false;
        exit(EXIT_FAILURE);
    }

    if (input.peek() == ifstream::traits_type::eof())
    {
        cout << "File is empty.";
        return false;
    }
    std::string line;
    vector<double> row;
    bool afterComments = false;
    while (getline(input, line) || !(input.eof()))
    {
        if (line.empty())
            continue;
        if (line[0] == '#')
        {
            comments.push_back(line);
            continue;
        }

        else if (!afterComments)
        {
            std::string parsed = "";
            int i = 0;
            for (i; i < line.size(); i++)
            {
                if (line[i] == ',' || line[i] == '\n' || line[i] == '\r')
                {
                    column.push_back(parsed);
                    parsed = "";
                }
                else
                {
                    parsed += line[i];
                }
            }
            if (i == line.size())
            {
                column.push_back(parsed);
            }
            afterComments = true;
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



bool FileManager::commentExtraction(vector<std::string> &comments, unordered_map<std::string, std::variant<int, double, std::string>> &extracted)
{
    if (comments.empty())
    {
        cout << "No comments found." << endl;
        return false;
    }

    
    int equalsCount = 0;
    bool badLine=false;
    for (int i = 0; i < comments.size(); i++)

    {
        for(int j=0; j<comments[i].size(); j++){
            if(comments[i][j]=='='){
                equalsCount++;
                if(equalsCount>1){
                    cout<<"Multiple '=' found in comment line: "+comments[i]<<endl;
                    equalsCount=0;
                     badLine=true;
                    break;
                }
            }
        }
        if(badline)
            continue;
        
        int position = comments[i].find('=');
        if (position == std::string::npos)
            continue;

        int leftPointer = position - 1;
        int rightPointer = position + 1;
        bool secondSpaceLeft = false;
        bool secondSpaceRight = false;

        bool reachedWordLeft = false;
        bool reachedWordRight = false;
        string key = "";
        string value = "";

        comments[i][leftPointer] == ' ' ? reachedWordLeft = false : reachedWordLeft = true;
        comments[i][rightPointer] == ' ' ? reachedWordRight = false : reachedWordRight = true;

        while (leftPointer > 0 && !secondSpaceLeft)
        {

            if (comments[i][leftPointer] == ' ' && !reachedWordLeft)
            {
                leftPointer--;
            }

            else if (comments[i][leftPointer] == ' ' && reachedWordLeft)
            {
                secondSpaceLeft = true;
            }

            else if (comments[i][leftPointer] != ' ' && !reachedWordLeft)
            {
                key = comments[i][leftPointer] + key;
                reachedWordLeft = true;
                leftPointer--;
            }
            else if (reachedWordLeft && comments[i][leftPointer] != ' ')
            {
                key = comments[i][leftPointer] + key;
                leftPointer--;
            }
        }

        while (rightPointer > position && !secondSpaceRight)
        {

            if (comments[i][rightPointer] == ' ' && !reachedWordRight)
            {
                rightPointer++;
            }

            else if ((comments[i][rightPointer] == ' ' || comments[i][rightPointer] == '\n' || comments[i][rightPointer] == '\r' || comments[i][rightPointer] == '\000') && reachedWordRight)
            {
                secondSpaceRight = true;
                std::reverse(value.begin(), value.end());
                extracted[key] = value;
            }

            else if (comments[i][rightPointer] != ' ' && !reachedWordRight)
            {
                value = comments[i][rightPointer] + value;
                reachedWordRight = true;
                rightPointer++;
            }

            else if (reachedWordRight && comments[i][rightPointer] != ' ')
            {
                value = comments[i][rightPointer] + value;
                rightPointer++;
            }

            if (value.empty() || key.empty())
                continue;
        }
    }
    return true;
}
