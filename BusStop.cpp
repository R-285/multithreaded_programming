//---------------------------------------------------------------------------

#pragma hdrstop

#include "BusStop.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

BusStop::BusStop(int pos){
	Position = pos;
}
int BusStop::getPosition() {
	return Position;
}
