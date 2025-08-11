#include <iostream>
#include<vector>
#include<string>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"FileManager.h"
using namespace std;





int main()
{
    vector<vector<double>> data{
       
		
{1.00,	0.809016994,	0.587785252},
		
{2.0006,	0.309016994	,0.951056516}};

    vector<string>columns={"hi","bye","ok"};
    vector<string> comments={"# I hope all is well","# I also hope all is well"};

    FileManager filem;

    

    filem.export_func("trial.csv",data, columns, comments);

 
    vector<vector<double>> data2;
    vector<string>columns2;
    vector<string> comments2;



   bool import_func= filem.import_func("/.trial_write.csv",data2,columns2,comments2);

   cout<<import_func;

}