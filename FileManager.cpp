#include<iostream>
#include<vector>
#include<string>


class FileManager
{
    void export_to_filestring(string filename,vector<vector<double>& data, vector<string>columns, vector<string> comments)
    {
        ofstream myfile
        myfile.open (filename);

      
        for( int i=0;i<comments.size(),i++)
        {
            if(comments[i]=="#")
                myfile<<endl<<"#";
            else
                myfile<<comments[i]<<endl;
        }
            
        
        for( int i=0;i<columns.size(),i++)
        {
            myfile<<columns[i]<<",";
        }
        
        for( int i=0;i<data.size(),i++)
        {
            for(int j=0;i<data[0].size(),j++)
            {
                 myfile <<data[i][j]<<",";
                 
            6
            }
            myfile<<endl<<endl;
        }


  myfile.close()
    }
    vector<vector<double> import_from_file(string filename,istream& str)
    {
              vector<string>   result;
                string line;
                getline(str,line);


    }
};