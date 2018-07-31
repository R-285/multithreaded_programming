//---------------------------------------------------------------------------
#include "Windows.h"
#ifndef BusH
#define BusH
//---------------------------------------------------------------------------
//��������������� �����, ����� �������� �������� ������.
//�������� ������ ��������� �� ����� ������
class RMutexLocker
{
	HANDLE hMutex;
public:
	RMutexLocker( HANDLE mutex )
	{
		hMutex = mutex;
		WaitForSingleObject( hMutex, INFINITE );
	}
	~RMutexLocker()
	{
		ReleaseMutex( hMutex );
	}
};



class Bus {
	int Speed;
	int Position;
	HANDLE hThread;
	HANDLE hMutexPos;
	HANDLE hMutexSpeed;
	HANDLE hStopEvent;
	HANDLE hSleepEvent;
	static DWORD WINAPI ThreadFunc( LPVOID ptr ) ;
public:
	Bus();
	~Bus();
	void UpdatePosit();
	void BusSleep();
	void setSpeed(int);
	int getPosit();
	int getSpeed();
	void start();
	void stop();
};
#endif
