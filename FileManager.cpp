#include<iostream>
#include<vector>
#include<string>


class FileManager
{
    void export_to_filestring(string filename,vector<vector<double>& data, ve)
    {
        ofstream myfile
        myfile.open (filename);

      

        myfile <<"# Keysight VSA IQ Data Export"<<endl;
        myfile <<"# SampleRate = 1000000.0"<<endl;

        myfile <<"# Format: Time(s),I,Q"<<endl;
        myfile <<"Time(s),I,Q"<<endl<<endl;
        myfile <<"0,1,0"<<endl<<endl;    
        
        for( int i=0;i<data.size(),i++)
        {
            for(int j=0;i<data[0].size(),j++)
            {
                 myfile <<data[i][j]<<",";
                 
            
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