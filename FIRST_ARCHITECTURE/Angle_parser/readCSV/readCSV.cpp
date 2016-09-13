//input the number of rows and columns of the csv sheet
//13/9/16
//written by-sakshi
#include "readCSV.h"

std::vector<int> readCSV::storeCSV2array(const char* const filename,int row,int col)
{
//file opening	
std::ifstream infile(filename);
 std:: vector<std::string> data;
  std::  string line;
std::cout << "process started" << std::endl;
if ( !infile.good() )
     {
     std::cout << "error while opening file.";
     exit (EXIT_FAILURE);
     }

while (getline(infile, line))
    {   
    data.push_back(line);
    }
infile.close();

  /*  for (int i = 0; i < data.size(); ++i)
    {
       std::cout << data[i] <<std::endl;
     } *///for testing   
//converting vector<std::string> to vector<int>

    
std::vector<int> Data;
for (int i=0; i< data.size(); i++)
   {
    int num = atoi(data.at(i).c_str());
    Data.push_back(num);
   }

return Data;  
}
