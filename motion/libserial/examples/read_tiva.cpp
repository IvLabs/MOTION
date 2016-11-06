//Compiling the code : g++ -o read_tiva read_tiva.cpp -L/usr/local/lib -lserial
// using the serial port.h alone
// to read the serial port giving the number of bytes as input

#include <SerialPort.h>
#include <iostream>
/*
void SerialPort::Read 	( 	DataBuffer &  	dataBuffer,
		const unsigned int  	numOfBytes = 0,
		const unsigned int  	msTimeout = 0 
	) 		
throw 	(	NotOpen,
		ReadTimeout,
		std::runtime_error
	)	*/
	
//	void 	Read (DataBuffer &dataBuffer, const unsigned int numOfBytes=0, const unsigned int msTimeout=0) throw ( NotOpen, ReadTimeout, std::runtime_error )
 /*void SerialPort::Open 	( 	const BaudRate  	baudRate = BAUD_DEFAULT,
		const CharacterSize  	charSize = CHAR_SIZE_DEFAULT,
	const Parity  	parityType = PARITY_DEFAULT,
		const StopBits  	stopBits = STOP_BITS_DEFAULT,
		const FlowControl  	flowControl = FLOW_CONTROL_DEFAULT 
	) */	


int main()
{
	int count=3;
	int i;
	unsigned char a;
	SerialPort s("/dev/ttyACM0");
	SerialPort::BaudRate b;
    b=s.BAUD_9600;
	s.Open(b);
 /*   a= s.ReadByte(10000);
    std::cout<< std::hex<<(int)a<<std::endl; */
   SerialPort::DataBuffer d;
   d.clear();
   std::cout<<"Reading data"<<std::endl;
    s.Read(d,count,0);
     std::cout<<"completed reading data"<<std::endl;
    for ( i=0;i<count;i++)
    {
		std::cout<<std::hex<<(int)d[i]<<std::endl;
	}
	for ( i=0;i<count;i++)
    {
		a=d[i];
		std::cout<<a<<std::endl;

	}

}
