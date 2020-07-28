// tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <random>
using namespace std;

template<typename T>
void print(const T& v, const char* message = "")
{
	typename T::const_iterator it;
	std::cout << message;
	std::cout << "( ";
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << " )" << std::endl;
}

void HeapSort(int *arr, int size)
{
	int node = 0, parent = 0;


	for (int i = 1; i < size; i++)
	{
		node = i;
		while (node != 0)
		{
			parent = (node - 1) / 2;
			if (arr[parent] < arr[node])
				swap(arr[parent], arr[node]);

			node = parent;
		}

		for (int i = size - 1; i >= 0; i--)
		{
			//����ū���� �ǵڷ� ������
			swap(arr[0], arr[i]);
			parent = 0;
			//�������θ���� 
			do {
				node = 2 * parent + 1;
				if (arr[node] < arr[node + 1] && node < i - 1) //�������ڽİ��� ��ũ�ٸ� ++ �ƴ϶�� ���ʰ��̶�¶�
					node++;

				if (arr[parent] < arr[node] && node < i) //�ڽ��� ũ�� ��ȯ
					swap(arr[parent], arr[node]);

				parent = node;
			} while (node<i);
		}
	}
}

enum TREE
{
	TREE_NONE,
	TREE_INSERT,
	TREE_SEARCH,
	TREE_DELEETE,
	TREE_PRINT,
	TREE_EXIT,
	TREE_END
};

struct Tree
{
	int num;
	string name;
	struct Tree *leftNode;
	struct Tree *rightNode;
};

Tree* head = new Tree;

int MenuTree();
void insertTree();
void DeleteTree();
void subDeleteTree(Tree*,int);
void SearchTree(int);
void Initialize();
void PrintTree();
void subPrintTree(Tree*);

int main()
{
	Initialize();
	int check = 0;
	do 
	{
		system("cls");
		check = MenuTree();
	} while (check !=1);

    return 0;
}

void Initialize()
{
	head->leftNode = nullptr;
	head->rightNode = nullptr;
	head->num = 0;
	head->name = "";
}

int MenuTree()
{
	int iChoice = TREE_NONE;

	while (iChoice == TREE_NONE)
	{
		cout << "1.����\n2.����\n3.�˻�\n4.���\n5.����\n";

		cin >> iChoice;
		switch (iChoice)
		{
		case TREE_INSERT:
			insertTree();
			break;
		case TREE_DELEETE:
			break;
		case TREE_SEARCH:
			break;
		case TREE_PRINT:
			PrintTree();
			break;
		case TREE_EXIT:
			return 1;
			break;
		default:
			{
				iChoice == TREE_NONE;
			}
			break;
		}
	}

	return 0;
}

void insertTree()
{
	
	Tree* temp = nullptr;
	temp = head;
	int insertNum = 0;
	string strTemp;

	cout << "�̸��� �Է����ּ���.";
	cin >> strTemp;

	cout << "��ȣ�� �Է����ּ���.";
	cin >> insertNum;

	if (temp->leftNode == nullptr && temp->rightNode == nullptr && temp->num == 0&&temp->name=="") //ù��
	{
		temp->num = insertNum;
		temp->name = strTemp;

	}
	else
	{
		Tree *insert = new Tree;
		insert->name = strTemp;
		insert->num = insertNum;
		insert->leftNode = nullptr;
		insert->rightNode = nullptr;
		
		while (temp->leftNode != nullptr || temp->rightNode != nullptr)
		{
			if (temp->num < insert->num) //���԰��� ��Ŭ��
			{
				if (temp->rightNode == nullptr)
				{
					temp->rightNode = insert;
				}
				else
				{
					temp = temp->rightNode;
				}
				
			}
			else
			{
				if (temp->leftNode == nullptr)
				{
					temp->leftNode = insert;
				}
				else
				{
					temp = temp->leftNode;
					
				}	
			}
		}

		if (temp->num < insert->num)
		{
			if (temp->rightNode == nullptr)
			temp->rightNode = insert;
		}
		else
		{
			if(temp->leftNode ==nullptr)
				temp->leftNode = insert;
		}	
	}
}

void DeleteTree()
{
	Tree* temp = nullptr;
	temp = head;

	int deleteNum = 0;
	cout << "������ ��ȣ�� �Է����ּ���.";
	cin >> deleteNum;


	if (temp->leftNode == nullptr && temp->rightNode == nullptr)
	{
		cout << "�ƹ����� �����ϴ� . \n";
		system("pause");
		return;
	}

	subDeleteTree(temp, deleteNum);
}

void subDeleteTree(Tree* node, int delNum)
{


}

void SearchTree(int)
{

}

void PrintTree()
{
	Tree* temp = nullptr;
	temp = head;

	if (temp->leftNode == nullptr && temp->rightNode == nullptr)
	{
		cout << "�ƹ����� �����ϴ� . \n";
		system("pause");
		return;
	}
	subPrintTree(temp);
	system("pause");

}

void subPrintTree(Tree* node)
{
	if (node->leftNode == nullptr)
	{
		cout << "�̸� : " << node->name << "��ȣ : " << node->num << endl;
		if (node->rightNode != nullptr)
			subPrintTree(node->rightNode);
		return;
	}

		subPrintTree(node->leftNode);
		cout << "�̸� : " << node->name << "��ȣ : " << node->num << endl;
	if (node->rightNode != nullptr)
		subPrintTree(node->rightNode);

	cout << "�̸� : " << node->name << "��ȣ : " << node->num << endl;
	return;
}
