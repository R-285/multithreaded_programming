//---------------------------------------------------------------------------

#ifndef UnitBusH
#define UnitBusH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Bus.h"
#include "BusStop.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *ButtonPlus;
	TButton *ButtonMinus;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TMemo *Memo1;
	TButton *StartButton;
	TButton *StopButton;
	TMemo *Memo2;
	TLabel *label7;
	TLabel *Label8;
	void __fastcall StartButtonClick(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ButtonPlusClick(TObject *Sender);
	void __fastcall ButtonMinusClick(TObject *Sender);
private:	// User declarations
	TList * autobus;
	BusStop *Stopping[5];
	HANDLE hStartEvent;
	Bus * temp;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
