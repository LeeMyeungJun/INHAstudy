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
		cout << "비었습니다." << endl;
	}

	int count =1;
	for (it = hash.begin(); it != hash.end(); it++,count++)
	{
		if (*it == num)
		{
			cout << num << "은 " << key << "번째 키 에"<<count<<"번째에 있습니다." << endl;
			return;
		}
	}

	cout << "값을 찾지 못했습니다." << endl;
	return;
}

void ChainHash::HashAdd(int num)
{
	hash.push_back(num);
	cout << "성공적으로 넣었습니다." << endl;

}

void ChainHash::HashRemove(int num)
{
	if (hash.empty())
	{
		cout << "비었습니다." << endl;
	}

	for (it = hash.begin(); it != hash.end(); it++)
	{
		if (*it == num)
		{
			hash.erase(it);
			cout << "성공적으로 지워졌습니다 ." << endl;
			return;
		}
	}

	cout << "값을 찾지 못했습니다." << endl;

}

void ChainHash::HashClear()
{
	if (hash.empty())
	{
		cout << "비었습니다." << endl;
	}
	hash.clear();
}
