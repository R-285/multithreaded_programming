//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitBus.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Randomize();
	hStartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);   //Событие для обработки Start-Stop
	autobus = new TList;

	temp = new Bus;
	autobus->Add(temp);

	for (int i = 1; i < Edit1->Text.ToInt(); ++i){
		autobus->Add(new Bus);
	}
	*Stopping = new BusStop[5];                          //Инициализируем объекты автобусных остановок
	Stopping[0] = new BusStop(1000);
	Stopping[1] = new BusStop(4000);
	Stopping[2] = new BusStop(6000);
	Stopping[3] = new BusStop(10000);
	Stopping[4] = new BusStop(12000);
}

void __fastcall TForm1::StartButtonClick(TObject *Sender)
{
	for (int i = 0; i < Edit1->Text.ToInt(); ++i){
		((Bus*)autobus->Items[i])->start();
	}
	SetEvent(hStartEvent);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopButtonClick(TObject *Sender)
{
	for (int i = 0; i < autobus->Count; ++i){
		((Bus*)autobus->Items[i])->stop();
	}
	ResetEvent(hStartEvent);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (WaitForSingleObject(hStartEvent, 0) != WAIT_OBJECT_0) {  //Чтобы не выводить информацию по тому, что ещё не запущено (не инициализировано)
		return;
	}
	
	Memo1->Clear(); 		
	Memo2->Clear(); 
	
	int min_, min_index;
	//Обработка и вывод информации по всем автобусам. temp -информация с какой остановки автобус выехал
	for (int j = 0, temp = 5; j < autobus->Count; j++, temp = 5) {
		if (((Bus*)autobus->Items[j])->getPosit() >= 1000) {
			temp = 1;
		}
		if (((Bus*)autobus->Items[j])->getPosit() >= 4000) {
			temp = 2;
		}
		 if (((Bus*)autobus->Items[j])->getPosit() >= 6000) {
			temp = 3;
		}
		 if (((Bus*)autobus->Items[j])->getPosit() >= 10000) {
			temp = 4;
		}
		Memo1->Lines->Add(IntToStr(j) + "). Speed = " + IntToStr(((Bus*)autobus->Items[j])->getSpeed()) + \
			"; Position = "+IntToStr(((Bus*)autobus->Items[j])->getPosit()) + "; came form the " + \
			IntToStr(temp) + "-th busstop");
	}

	//Обработка информации по всем остановкам и вывод её
	for (int i = 0; i < 5; i++) {
		int min = 13000;
		//Определяем для данной остановки индекс ближайшего автобуса, и расстояние
			//Это если автобус находится раньше остановки
		for (int j = 0; j < autobus->Count; j++) {
			min_ = ((BusStop*)Stopping[i])->getPosition() - ((Bus*)autobus->Items[j])->getPosit();

			if  ((min > min_)&&(min_>0)) {
				min = min_ ;
				min_index = j;
			}
		}
			//А это если автобуса ещё нет раньше остановки, тогда смотрим раньше начала кольца.
		if ( min > 12000) {
			for (int j = 0; j < autobus->Count; j++) {
				min_ = (12000 - ((Bus*)autobus->Items[j])->getPosit()) + (((BusStop*)Stopping[i])->getPosition());
				if  ((min > min_)&&(min_>0)) {
					min = min_ ;
					min_index = j;
				}
			}
		}
		Memo2->Lines->Add("Weit to: " + FloatToStr( min /(((Bus*)autobus->Items[min_index])->getSpeed())) + \
			"c. Will come bus №" + IntToStr(min_index));
		Memo2->Lines->Add(" ");
		//Для обработки того, что автобус находится ближе к остановке, чем один шаг до неё (Speed).
        //(Т.е. следующим шагом он проедет дальше данной остановки)
		if (min <= (((Bus*)autobus->Items[min_index])->getSpeed())) {
			((Bus*)autobus->Items[min_index])->BusSleep();

		}
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::ButtonPlusClick(TObject *Sender)
{
	int number = StrToInt(Edit1->Text);
	if (number < 10) {
		number++;
		temp = new Bus;
		autobus->Add(temp);
		Edit1->Text = IntToStr(number);
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonMinusClick(TObject *Sender)
{
	int number = StrToInt(Edit1->Text);
	if (number > 1) {
		number--;
		autobus->Delete(number);
		Edit1->Text = IntToStr(number);
	}
}
//---------------------------------------------------------------------------


