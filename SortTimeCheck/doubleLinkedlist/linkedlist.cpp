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
	�Է� ������ ������� ��ȣ ������� ���ĵ� ����Ʈ�� �����ϰ��� �ϴ� ���α׷��� �ۼ��϶�..


	1. ����Ʈ �ʱ�ȭ
	2. ��� �߰�
		-1 ���� �տ� �߰�
		-2 �ǵڿ� �߰�
		-3 ���̿� �߰�
	3. ������
		-1 ���Ͼ� ������
		-2 �ǵ� ������
		-3 ���� ������
	4. �˻�
		-��ȣ�� �Է¹޾Ƽ� �ش��ȣ�� �̸� ���
	5. ���
		����Ʈ���� ���

		�޴����� 1�л��߰� 2�л����� 3 ��ü���
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

	cout << "�޴�����"<<endl;
	cout << "1. �л� �߰�" << endl;
	cout << "2. �л� ����" << endl;
	cout << "3. ��ü ���" << endl;
	cout << "4. ���� " << endl;
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

	cout << "��ȣ : ";
	cin >> num;
	while (temp->pnext != head)
	{
		if (num == temp->pnext->no)
		{
			cout << "�ߺ��Ȱ� ����. �ٸ����� �־��ּ���."<<endl;
			system("pause");
			return;
		}
		/*���� ����*/
		if (num < temp->pnext->no)
		{
			mate->previous = temp;
			temp->pnext->previous = mate;

			mate->pnext = temp->pnext;
			temp->pnext = mate;

			mate->no = num;
			cout << "�̸� : ";
			cin >> mate->name;

			return;
		}
		//�������
		temp = temp->pnext;
	}
	mate->pnext = head;
	mate->previous = temp;
	temp->pnext = mate;

	mate->no = num;
	cout << "�̸� : ";
	cin >> mate->name;

	return;
}

void PrintMate()
{
	if (head->pnext == head)
	{
		cout << "���� �����ϴ�."<<endl;
		system("pause");
		return;
	}

	classmate* temp = NULL;
	temp = head;

	while (temp->pnext != head)
	{
		cout << "��ȣ : " << temp->pnext->no << " �̸� : " << temp->pnext->name<<endl;
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

	cout << "������ ��ȣ �Է� : ";
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

	cout << "���� ���������ʽ��ϴ�."<<endl;
	system("pause");
	return;
}


void DeleteMenu()
{
	int DeleteChoice = DELETE_NONE;	
	system("cls");

	do
	{
		cout << "1. �Ǿ� ���� \n2. ���� ���� \n3. �ǵ� ����\n4. �ڷΰ���";

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
		cout << "���� �����ϴ�." << endl;
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
		cout << "���� �����ϴ�." << endl;
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
