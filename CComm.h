//---------------------------------------------------------------------------

#ifndef CCommH
#define CCommH
//---------------------------------------------------------------------------
#include <Windows.h>

class CComm{

	private:
		HANDLE hComm;
		bool portOpen;

	public:
		CComm(char *tPort);
		~CComm();

		DCB config;
		unsigned char ReceiveByte();
		bool sendByte (unsigned char data);

		bool GetPortConfig();
		bool SetPortConfig();

		bool GetPortOpen();



};


#endif
