//code to test readCSV.cpp
#include "readCSV.cpp"
int main()
{
readCSV i;
std::vector<int>  v;

v=i.storeCSV2array("ang1.csv",3,3);
for (int j=0;j<5;j++)
{
std::cout <<v[j] <<std::endl;
}
}
