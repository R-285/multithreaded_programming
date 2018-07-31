//---------------------------------------------------------------------------

#pragma hdrstop

#include "Bus.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
Bus::Bus(){

	Speed = (rand()%10) + 15; //15 <= speed <= 25;
	Position = (rand()%12)*1000;

	hThread = INVALID_HANDLE_VALUE;
	hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hSleepEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	hMutexPos = CreateMutex( NULL, FALSE, NULL );
	hMutexSpeed = CreateMutex( NULL, FALSE, NULL );
}

Bus::~Bus(){
	stop();
	CloseHandle(hStopEvent);
	CloseHandle(hSleepEvent);
	CloseHandle(hMutexPos);
	CloseHandle(hMutexSpeed);
}
//«ащищенно мен€ем позицию (вызываетс€ каждые 100 мс из потока). Speed защищать не надо,
//потому что скорость мен€етс€ во врем€ паузы (UpdatePosit не вызываетс€ во врем€ паузы)
void Bus::UpdatePosit(){
	RMutexLocker guard( hMutexPos );
	Position += Speed;
	if(Position > 12000)
	 Position = 0;
}

void Bus::setSpeed(int A){
	RMutexLocker guard( hMutexSpeed );
	Speed = A;
}

int Bus::getPosit(){
	RMutexLocker guard( hMutexPos );
	return Position;
}

int Bus::getSpeed(){
	RMutexLocker guard( hMutexSpeed );
	return Speed;
}

void Bus::start(){
	if( hThread != INVALID_HANDLE_VALUE ) return; //уже запущен
	ResetEvent( hStopEvent ); //перед началом работы сбрасываем флаг остановки
	hThread = CreateThread( NULL, 0, ThreadFunc, this, 0, NULL ); //запускаемс€ в работу
}

void Bus::stop()
{
	if( hThread == INVALID_HANDLE_VALUE ) return; //не запущен
	SetEvent( hStopEvent ); //взводим флаг остановки
	//ждем, когда поток заметит наш флаг и остановитс€
	if( WaitForSingleObject( hThread, 5000 ) != WAIT_OBJECT_0 )
	{
		//прождали п€ть секунд, не остановилс€, "приболел" видимо, пристрелим, чтобы не мучалс€
		TerminateThread( hThread, 1 );
	}
	CloseHandle( hThread );
	hThread = INVALID_HANDLE_VALUE;
}

void Bus::BusSleep(){
	SetEvent( hSleepEvent ); //‘лаг дл€ sleep (остановка автобуса на остановке).
}

DWORD WINAPI Bus::ThreadFunc( LPVOID ptr )
{
	Bus* _this = (Bus*)ptr;
	if( !_this ) return 1; //забыли нам дать объект, не будем работать

	for(;;)
	{

		if (WaitForSingleObject( _this->hSleepEvent, 0 ) ==  WAIT_OBJECT_0 ){
			Sleep(2000);
			_this->setSpeed((rand()%10) + 15);
			ResetEvent( _this->hSleepEvent );
		}

		//сделаем важную работу
		_this->UpdatePosit();
		//поспим, гл€д€ на флаг конца работы
		if( WaitForSingleObject( _this->hStopEvent, 100 ) == WAIT_OBJECT_0 )
			break;
	}
	return 0;
}
