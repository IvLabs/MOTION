//input the number of rows and columns of the csv sheet
#include "readCSV.h"

vect2d readCSV::storeCSV2array(const char* const filename,int row,int col)
{
//file opening	
std::ifstream file(filename);
if ( !file.good() )
          {
			std::cout << "error while opening file.";
          }
//storing data to 2d vector data[][]
std::vector<std::vector<int> > data(row, std::vector<int>(col));
	for(int i = 0; i < row; i++)
    {
        std::string line;
        std::getline(file, line);
        if ( !file.good() )
         break;
        std::stringstream iss(line);
        for (int j = 0; i<col; j++)
        {
            std::string val;
            std::getline(iss, val, ',');
        if ( !iss.good() )
	     break;
	        std::stringstream convertor(val);
            convertor >> data[j][i];
    }
    
    }
   
return data;  
}
