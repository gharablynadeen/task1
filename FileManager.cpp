#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class FileManager
{
    void export(string filename,vector<vector<double>>& data, vector<string>columns, vector<string> comments)
    {
        ofstream myfile ;
        myfile.open (filename);

      
        for( int i=0;i<comments.size();i++) 
        {
            if(comments[i]=="#")
                myfile<<endl<<"#";
            else
                myfile<<comments[i]<<endl;
        }
            
        
        for( int i=0;i<columns.size();i++)
        {
            myfile<<columns[i]<<",";
        }
        
        for( int i=0;i<data.size();i++)
        {
            for(int j=0;i<data[0].size();j++)
            {
                 myfile <<data[i][j]<<",";
            }
            myfile<<endl<<endl;
        }

  myfile.close();
    }

    vector<vector<double>> import(string filename,istream& str)
    {
              /*vector<string>   result;
                getline(str,line);*/

                vector<string> titles ;
                vector<vector<double>> data;
                ifstream input ("filename");
                string line;
                double x;
                int j = 0 ; //columns
                int i = 0; //rows
                int noOfColumns = 1;

                input>> line ;

                while (line == "#"){
                     getline (input, line);
                     cout<<"#"<<line;
                     input>>line;
                }
                 
                titles[0] = line ;
                 
                //getting values of each column title 
                 while(input>>titles[1]){
                noOfColumns += 1;
                }

                //cout values of each column title 
                for(x=0;x<noOfColumns;x++){
                    cout<<titles[x];
                    if(x<noOfColumns-1)
                    {
                        cout<<",";
                    }
                    else 
                    {
                     cout<<endl<<endl;
                    }
                }

                while(!input.eof())
                {
                  input >> data[i][j] ;
                  if(j==noOfColumns-1){
                  cout<<data[i][j]<<endl<<endl;
                  i++;
                  j=0;
                  }
                  else{
                  cout<<data[i][j]<<",";
                  j++;
                }
            }

             input.close();   

    }
};