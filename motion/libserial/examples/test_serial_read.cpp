#include "serialUSB.cpp"

int main()
{

   
   int s[]={0x7F,0xFF,0x0A,0x05,0x03,0x38,0xC6,0x35,0x01,0x01};
    //int s[]={255,255,10,3,56,126,53,1,1};
	serialUSB ser_obj("/dev/ttyUSB1",57600);
    ser_obj.sendData(s,10); 
	return 0;
}
