//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "scControls"
#pragma link "scGPControls"
#pragma link "scGPExtControls"
#pragma link "scModernControls"
#pragma link "scGPMeters"
#pragma resource "*.dfm"
TfrmMain *frmMain;

bool controle = False;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
        objPort = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

 void TfrmMain::ListComPorts()
 {
	TRegistry *reg = new TRegistry();

	TStringList *list = new TStringList();

	reg->RootKey = HKEY_LOCAL_MACHINE;

	reg->OpenKey("HARDWARE\\DEVICEMAP\\SERIALCOMM",false);

	reg->GetValueNames(list);


	for(int i=0; i < list->Count; i++)
	{

	}

    delete(reg, list);
 }
 //---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
   ListComPorts();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnListClick(TObject *Sender)
{
  ListComPorts();
}
//---------------------------------------------------------------------------


void TfrmMain::InsertStatusLog(UnicodeString msg)
{

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::thread1Run(TIdThreadComponent *Sender)
{

 if(objPort != NULL)
 {
	   byte = objPort->ReceiveByte();

		switch(byte)
		{
			case 0x00: break;

			case 0x42:   //B
			shpL1->Brush->Color = clWhite;
			InsertStatusLog("L1 turned off");
			break;

			case 0x41: //A
			shpL1->Brush->Color = clHighlight;
			InsertStatusLog("L1 turned on");
			break;

			default:
			break;
		}

		/*
		 L1 = 0xA0 ou 0xA1
		 L2 = 0xB0 ou 0xB1
		 L3 = 0xC0 ou 0xC1
        */
		if(txRequest)
		{

		}

        Sleep(200);

 }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::swcL1ChangeState(TObject *Sender)
{
  if(objPort != NULL && objPort->GetPortOpen())
  {
	  
  }
}
//---------------------------------------------------------------------------

void TfrmMain::ClosePort()
{

}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::btnOpenPortClick(TObject *Sender)
{
	shpL1->Brush->Color = clGreen;

	controle = True;

    objPort = new CComm("COM7");      //teste/

	if(objPort->GetPortOpen())
	{
		if(objPort->GetPortConfig())
		{
			objPort->config.BaudRate =  19200;
			objPort->config.fParity = NOPARITY;
			objPort->config.ByteSize = 8;
			objPort->config.StopBits = ONESTOPBIT;

			if(objPort->SetPortConfig())
			{
				objPort->sendByte(0x01);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::scGPButton1Click(TObject *Sender)
{
	shpL1->Brush->Color = clRed;
    mmo1->Clear();
	controle = False;
    	if(objPort != NULL)
	{
		objPort->sendByte(0x00);
		delete(objPort);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	mmo1->Clear();
	shpL1->Brush->Color = clRed;
	controle = False;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSendClick(TObject *Sender)
{
	if(controle){
		int valueWave = dial->IntValue();

		objPort->sendByte(valueWave);

		float frequency = (48000000/(dial->IntValue()+1))/2;
		//double teste = 10/3;
		mmo1->Clear();
		mmo1->Text = frequency;
	}
}

