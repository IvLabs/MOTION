#include "Herkulex.cpp"
#include <iostream>
using namespace std;
int main()
{
	HerkulexClass h; 
	std::cout<<"hello"<<endl;
	h.setLed(20,1);
	float f=h.getPosition(20);
	std::cout<<f<<std::endl;
	float f1=h.getAngle(20);
	std::cout<<f1<<std::endl;
	return(0);
}
