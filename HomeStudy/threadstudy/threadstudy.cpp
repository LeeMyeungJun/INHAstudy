// threadstudy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <process.h>

int Value = 0;
int ValuePlusOne = 0;

int cnt = 0;

bool isChecked = false;
CRITICAL_SECTION cs;

//ũ��Ƽ�ü���, �̺�Ʈ  ����ؼ� �����带 �����ϰ� ����ϵ��� . å�� �̺�Ʈ�� ��������� .
//CreateThread ���� beginThread�� ���������.
//CreateThread ���� ���۸� ����ϴ� rand����� . �޸� �Ҵ�Ǵ� ������ ���ݾ� . malloc ���� �Ҵ��� �Ѵٵ��� ���������ʴٴ°ž�. 
//biginThread�� ������ .

DWORD WINAPI ThFunc1(LPVOID lpParam)
{
	while (1)
	{
		//isChecked = false;
		EnterCriticalSection(&cs);
		Value = rand() % 1000;
		ValuePlusOne = Value + 1;
		//isChecked = true;
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI ThFunc2(LPVOID lpParam)
{

	while (1)
	{
		//if(isChecked)
		EnterCriticalSection(&cs);
		{
			if (Value > ValuePlusOne)
				printf("%d \n", cnt++);
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}


unsigned __stdcall thFunc7(LPVOID lpParam)
{
	while (1)
	{
		//isChecked = false;
	//	EnterCriticalSection(&cs);
		Value = rand() % 1000;
		ValuePlusOne = Value + 1;
		//isChecked = true;
	//	LeaveCriticalSection(&cs);
	}
	return 0;
}

unsigned __stdcall thFunc8(LPVOID lpParam)
{
	while (1)
	{
		//if(isChecked)
	//	EnterCriticalSection(&cs);
		{
			if (Value > ValuePlusOne)
				printf("%d \n", cnt++);
		}
	//	LeaveCriticalSection(&cs);
	}
	return 0;
}

int main()
{
	InitializeCriticalSection(&cs);

	DWORD dwThID1, dwThID2;
	HANDLE hThread[2];

	unsigned long ulStackSize = 0;
	dwThID1 = 0; dwThID2 = 0;
	hThread[0] = NULL; hThread[1] = NULL;

	/*hThread[0] = CreateThread(NULL,ulStackSize , ThFunc1 , NULL,CREATE_SUSPENDED,&dwThID1);
	hThread[1] = CreateThread(NULL, ulStackSize, ThFunc2, NULL, CREATE_SUSPENDED, &dwThID2);*/

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))thFunc7, NULL, 0, (unsigned *)&dwThID1);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))thFunc8, NULL, 0, (unsigned *)&dwThID2);

	if (hThread[0] == 0 || hThread[1] == 0)
		exit(1);


	ResumeThread(hThread[0]);
	ResumeThread(hThread[1]);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	DeleteCriticalSection(&cs);

    return 0;
}

