// Hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

enum HASH
{
	HASH_NONE,
	HASH_ADD,
	HASH_SEARCH,
	HASH_REMOVE,
	HASH_CLEAR,
	HASH_EXIT,
	HASH_END

};


int InsertKey();
void Hashmenu(ChainHash*,int value);


int main()
{
	int key =InsertKey();

	ChainHash *hash = new ChainHash[key];

	Hashmenu(hash,key);

    return 0;
}

int InsertKey()
{
	int hashKey = 0;


	cout << "Ű���� �Է����ּ��� . " << endl;
	cin >> hashKey;

	return hashKey;
}

void Hashmenu(ChainHash* hash, int key)
{
	int hashMenu = HASH_NONE;
	int num = 0;
	while (true)
	{
		cout << "1. �������߰� \n2. ������ �˻�\n3. ������ ����\n4. ��� �����ͻ���\n5. ����"<<endl;
		cin >> hashMenu;
		switch (hashMenu)
		{
		case HASH_ADD:
			{
			
				cout << "�����Ͱ��� �Է����ּ���. :";
				cin >> num;
			
				hash[num %key].HashAdd(num);

			}
			break;
		case HASH_SEARCH:
			{
				cout << "�˻��� �����Ͱ��� �Է����ּ���. :";
				cin >> num;

				hash[num %key].HashSearch(num, num %key);
			}
			break;
		case HASH_REMOVE:
			{
				cout << "������ �����Ͱ��� �Է����ּ���. :" ;
				cin >> num;

				hash[num %key].HashRemove(num);
			}
			break;
		case HASH_CLEAR:
			{
				cout << "�����͸� ���� ����ϴ�."<<endl;

				for (int i = 0; i < key; i++)
					hash[i].HashClear();

			}
			break;
		case HASH_EXIT:
			{
				cout << "�����մϴ�." << endl;
				return;
			}
			break;
		default:
			break;
		}
		cout << endl << endl;

	}
}

