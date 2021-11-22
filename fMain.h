//---------------------------------------------------------------------------

#ifndef fMainH
#define fMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include <Vcl.ExtCtrls.hpp>
#include "scControls.hpp"
#include "scGPControls.hpp"
#include "scGPExtControls.hpp"
#include "scModernControls.hpp"

#include <registry.hpp>
#include "CComm.h"
#include <IdBaseComponent.hpp>
#include <IdThreadComponent.hpp>
#include "scGPMeters.hpp"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TscGPLabel *lbl1;
	TscGPButton *btnOpenPort;
	TShape *shpL1;
	TscGPPanel *pnlHeader;
	TscGPGlyphButton *btnExit;
	TscGPLabel *lblLogStatus;
	TscGPButton *scGPButton1;
	TscGPLabel *lbl;
	TscGPLabel *lbl11;
	TscGPLabel *lbl12;
	TscGPDial *dial;
	TscGPLabel *lbl13;
	TMemo *mmo1;
	TscGPButton *scgpbtn1;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnListClick(TObject *Sender);
	void __fastcall thread1Run(TIdThreadComponent *Sender);
	void __fastcall swcL1ChangeState(TObject *Sender);
	void __fastcall btnOpenPortClick(TObject *Sender);
	void __fastcall scGPButton1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnSendClick(TObject *Sender);
private:	// User declarations

	CComm *objPort;

	AnsiString port;
	AnsiString rxByte;
	AnsiString txByte;

	unsigned char byte;
    unsigned char txRequest;

    UnicodeString currentDateTime;

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);

	void ListComPorts();
	bool ConfigPort();
	void ClosePort();
	void InsertStatusLog(UnicodeString msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
