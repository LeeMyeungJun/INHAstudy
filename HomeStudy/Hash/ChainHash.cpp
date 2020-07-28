#include "stdafx.h"



ChainHash::ChainHash()
{
	Hashinit();
}

ChainHash::~ChainHash()
{
}

void ChainHash::Hashinit()
{
	hash.clear();
}

void ChainHash::HashSearch(int num, int key)
{
	if (hash.empty())
	{
		cout << "������ϴ�." << endl;
	}

	int count =1;
	for (it = hash.begin(); it != hash.end(); it++,count++)
	{
		if (*it == num)
		{
			cout << num << "�� " << key << "��° Ű ��"<<count<<"��°�� �ֽ��ϴ�." << endl;
			return;
		}
	}

	cout << "���� ã�� ���߽��ϴ�." << endl;
	return;
}

void ChainHash::HashAdd(int num)
{
	hash.push_back(num);
	cout << "���������� �־����ϴ�." << endl;

}

void ChainHash::HashRemove(int num)
{
	if (hash.empty())
	{
		cout << "������ϴ�." << endl;
	}

	for (it = hash.begin(); it != hash.end(); it++)
	{
		if (*it == num)
		{
			hash.erase(it);
			cout << "���������� ���������ϴ� ." << endl;
			return;
		}
	}

	cout << "���� ã�� ���߽��ϴ�." << endl;

}

void ChainHash::HashClear()
{
	if (hash.empty())
	{
		cout << "������ϴ�." << endl;
	}
	hash.clear();
}
