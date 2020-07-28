// linkedlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


enum MENU
{
	MENU_NONE,
	MENU_ADD,
	MENU_DELETE,
	MENU_PRINT,
	MENU_EXIT,
	MENU_END
};

enum DELETE
{
	DELETE_NONE,
	DELETE_FRONT,
	DELETE_CHOICE,
	DELETE_BACK,
	DELETE_MENU_BACK,
	DELETE_END
};



struct classmate
{
	int no;
	string name;
	struct classmate *pnext;
	struct classmate *previous;
};


void Initialize();
int MenuSelect();
void ClassMateAdd();
void PrintMate();
void DeleteMate();
void DeleteMenu();
void DeleteFront();
void DeleteBack();


classmate* head = new classmate;



int main()
{
	/*
	입력 순서와 상관없이 번호 순서대로 정렬된 리스트를 구현하고자 하는 프로그램을 작성하라..


	1. 리스트 초기화
	2. 노드 추가
		-1 제일 앞에 추가
		-2 맨뒤에 추가
		-3 사이에 추가
	3. 노드삭제
		-1 제일앞 노드삭제
		-2 맨뒤 노드삭제
		-3 사이 노드삭제
	4. 검색
		-번호를 입력받아서 해당번호의 이름 출력
	5. 출력
		리스트전부 출력

		메뉴선택 1학생추가 2학생삭제 3 전체출력
	*/

	
	Initialize();

	int iChoice = 0;
	while (1)
	{
		system("cls");
		iChoice = MenuSelect();

		switch (iChoice)
		{
		case MENU_ADD:
			ClassMateAdd();
			break;
		case MENU_DELETE:
			DeleteMenu();
			break;
		case MENU_PRINT:
			PrintMate();
			break;
		case MENU_EXIT:
			exit(0);
			break;
		}
	}
    return 0;
}

void Initialize()
{	
	head->pnext = head;
	head->previous = nullptr;
}

int MenuSelect()
{
	int iChoice = MENU_NONE;

	cout << "메뉴선택"<<endl;
	cout << "1. 학생 추가" << endl;
	cout << "2. 학생 삭제" << endl;
	cout << "3. 전체 출력" << endl;
	cout << "4. 종료 " << endl;
	while (iChoice == MENU_NONE)
	{
		cin >> iChoice;

		if (iChoice <= MENU_NONE || iChoice >= MENU_END)
			iChoice = MENU_NONE;
	}

	return iChoice;
}

void ClassMateAdd()
{
	classmate* mate = new classmate;
	classmate* temp = NULL;

	temp = head;

	int num = 0;

	cout << "번호 : ";
	cin >> num;
	while (temp->pnext != head)
	{
		if (num == temp->pnext->no)
		{
			cout << "중복된값 존재. 다른값을 넣어주세요."<<endl;
			system("pause");
			return;
		}
		/*수정 시작*/
		if (num < temp->pnext->no)
		{
			mate->previous = temp;
			temp->pnext->previous = mate;

			mate->pnext = temp->pnext;
			temp->pnext = mate;

			mate->no = num;
			cout << "이름 : ";
			cin >> mate->name;

			return;
		}
		//여기까지
		temp = temp->pnext;
	}
	mate->pnext = head;
	mate->previous = temp;
	temp->pnext = mate;

	mate->no = num;
	cout << "이름 : ";
	cin >> mate->name;

	return;
}

void PrintMate()
{
	if (head->pnext == head)
	{
		cout << "값이 없습니다."<<endl;
		system("pause");
		return;
	}

	classmate* temp = NULL;
	temp = head;

	while (temp->pnext != head)
	{
		cout << "번호 : " << temp->pnext->no << " 이름 : " << temp->pnext->name<<endl;
		temp = temp->pnext;
		
		system("pause");
	}
}

void DeleteMate()
{
	classmate* temp = NULL;
	classmate* deleteMate = new classmate;
	temp = head;

	int num = 0;

	cout << "삭제할 번호 입력 : ";
	cin >> num;
	while (temp->pnext != head)
	{
		if (num == temp->pnext->no)
		{
			deleteMate = temp->pnext;
			deleteMate->pnext = temp->pnext->pnext;
			temp->pnext = deleteMate->pnext;
			delete deleteMate;
			

			system("pause");
			return;
		}
		temp = temp->pnext;
	}

	cout << "값이 존재하지않습니다."<<endl;
	system("pause");
	return;
}


void DeleteMenu()
{
	int DeleteChoice = DELETE_NONE;	
	system("cls");

	do
	{
		cout << "1. 맨앞 삭제 \n2. 선택 삭제 \n3. 맨뒤 삭제\n4. 뒤로가기";

		cin >> DeleteChoice;

		if (DeleteChoice <= DELETE_NONE || DeleteChoice >= DELETE_END)
			DeleteChoice = DELETE_NONE;


	} while (DeleteChoice == DELETE_NONE);
	

	switch (DeleteChoice)
	{
	case DELETE_FRONT:
		DeleteFront();
		break;
	case DELETE_CHOICE:
		DeleteMate();
		break;
	case DELETE_BACK:
		DeleteBack();
		break;
	case DELETE_MENU_BACK:
		return;
		break;
	}
	
}

void DeleteFront()
{
	classmate* temp = NULL;
	classmate* deleteMate = new classmate;
	temp = head;
	if (head->pnext == head)
	{
		cout << "값이 없습니다." << endl;
		system("pause");
		return;
	}
	deleteMate= temp->pnext;
	
	temp->pnext = deleteMate->pnext;
	deleteMate->previous = temp;

	delete deleteMate;
}

void DeleteBack()
{
	classmate* temp = NULL;
	classmate* deleteMate = new classmate;
	temp = head;

	if (head->pnext == head)
	{
		cout << "값이 없습니다." << endl;
		system("pause");
		return;
	}

	while (temp->pnext->pnext != temp)
	{
		temp = temp->pnext;
	}
	deleteMate = temp->pnext;
	temp->pnext = temp;


	delete deleteMate;

}
