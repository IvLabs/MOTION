#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
using namespace std;
int main()
{
	std::vector<char> store_array;
	store_array.push_back(0x5f);
	store_array.push_back(0x3f);
	for(int i=0;i<2;i++)
	{
		std::cout<< store_array[i];
	}
	cout<<"hello"<<endl;
	int  a[100];
	for (int j=0;j<2;j++)
	{
		a[j]=(int)store_array[j];
	}
	for (int j=0;j<2;j++)
	{
		std::cout<<a[j];
	}
	
	
}
