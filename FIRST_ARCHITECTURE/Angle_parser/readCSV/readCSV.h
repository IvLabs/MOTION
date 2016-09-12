//date:11/9/16
//author:sakshi
//header file for readCSV.cpp
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>

typedef std::vector<std::vector<int> >  vect2d;
class readCSV
{
public:
vect2d  storeCSV2array(const char*const filename,int row,int col);	
};
