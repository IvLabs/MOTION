//code to test readCSV.cpp
#include "readCSV.cpp"
int main()
{
readCSV i;
vect2d  v;

v=i.storeCSV2array("try.csv",3,3);
for (int i=0;i<3;i++)
{
for(int j=0;j<3;j++)
{
std::cout<<v[i][j];	
}	
std::cout <<"\n";
}

}
