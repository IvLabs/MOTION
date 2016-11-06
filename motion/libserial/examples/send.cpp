//  Compilation : g++ -o send send.cpp -L/usr/local/lib -lserial
// Running : ./send

#include <SerialPort.h>
#include <iostream>

//void 	WriteByte (const unsigned char dataByte) throw ( NotOpen, std::runtime_error )
 
int main()
{
int  ch[]={0xFF,0xFF,0x0A,0x05,0x03,0x38,0xC6,0x35,0x01,0xff}; //unsigned char
 SerialPort s("/dev/ttyACM0");
	SerialPort::BaudRate b;
    b=s.BAUD_115200;
	s.Open(b);
	unsigned char a;
	for (int i=0; i<10;i++)
	{
      a=(char)ch[i];
      std::cout<<std::hex<<(int)a<<std::endl;
	  s.WriteByte(a);
	}
	return 0;
}
   
