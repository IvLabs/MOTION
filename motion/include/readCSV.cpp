//input the number of rows and columns of the csv sheet
//written by:sakshi
//13/9/16
#include "readCSV.h"

std::vector<std::string> readCSV::storeCSV2array(const char* const filename,int row,int col)
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
  //std::cout <<"entered loop";
  data.push_back(line);
}
infile.close();

// for (int i = 0; i < data.size(); ++i)
//{
// std::cout << data[i] <<std::endl;
//} 
//converting vector<std::string> to vector<int>
return data;  
}

