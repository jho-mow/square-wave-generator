//---------------------------------------------------------------------------

#pragma hdrstop

#include "CComm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


CComm::CComm(char *tPort)
{
	portOpen = false;

	hComm = CreateFileA(tPort,
						GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);

	if(hComm == INVALID_HANDLE_VALUE)
		portOpen = false;
	else
		portOpen = true;
}

CComm::~CComm()
{
	CloseHandle(hComm);
	portOpen = false;
}


unsigned char CComm::ReceiveByte()
{
	char byteReceived = 0x00;
	DWORD nBytesRead = 0;

    ReadFile(hComm, &byteReceived, 1, &nBytesRead, NULL);

	return byteReceived;
}


bool CComm::sendByte (unsigned char data)
{
	DWORD nBytesWritten = 0;

	return WriteFile(hComm,
					&data,
					1,
					&nBytesWritten,
					NULL);

}

bool CComm::GetPortConfig()
{
	return GetCommState(hComm, &config);
}
bool CComm::SetPortConfig()
{


	if(!SetCommState(hComm, &config))
		return false;

	return true;
}

bool CComm::GetPortOpen()
{
	return portOpen;
}


