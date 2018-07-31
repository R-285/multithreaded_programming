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
//��������� ������ ������� (���������� ������ 100 �� �� ������). Speed �������� �� ����,
//������ ��� �������� �������� �� ����� ����� (UpdatePosit �� ���������� �� ����� �����)
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
	if( hThread != INVALID_HANDLE_VALUE ) return; //��� �������
	ResetEvent( hStopEvent ); //����� ������� ������ ���������� ���� ���������
	hThread = CreateThread( NULL, 0, ThreadFunc, this, 0, NULL ); //����������� � ������
}

void Bus::stop()
{
	if( hThread == INVALID_HANDLE_VALUE ) return; //�� �������
	SetEvent( hStopEvent ); //������� ���� ���������
	//����, ����� ����� ������� ��� ���� � �����������
	if( WaitForSingleObject( hThread, 5000 ) != WAIT_OBJECT_0 )
	{
		//�������� ���� ������, �� �����������, "��������" ������, ����������, ����� �� �������
		TerminateThread( hThread, 1 );
	}
	CloseHandle( hThread );
	hThread = INVALID_HANDLE_VALUE;
}

void Bus::BusSleep(){
	SetEvent( hSleepEvent ); //���� ��� sleep (��������� �������� �� ���������).
}

DWORD WINAPI Bus::ThreadFunc( LPVOID ptr )
{
	Bus* _this = (Bus*)ptr;
	if( !_this ) return 1; //������ ��� ���� ������, �� ����� ��������

	for(;;)
	{

		if (WaitForSingleObject( _this->hSleepEvent, 0 ) ==  WAIT_OBJECT_0 ){
			Sleep(2000);
			_this->setSpeed((rand()%10) + 15);
			ResetEvent( _this->hSleepEvent );
		}

		//������� ������ ������
		_this->UpdatePosit();
		//������, ����� �� ���� ����� ������
		if( WaitForSingleObject( _this->hStopEvent, 100 ) == WAIT_OBJECT_0 )
			break;
	}
	return 0;
}
