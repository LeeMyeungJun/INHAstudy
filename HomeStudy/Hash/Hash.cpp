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


	cout << "키값을 입력해주세요 . " << endl;
	cin >> hashKey;

	return hashKey;
}

void Hashmenu(ChainHash* hash, int key)
{
	int hashMenu = HASH_NONE;
	int num = 0;
	while (true)
	{
		cout << "1. 데이터추가 \n2. 데이터 검색\n3. 데이터 삭제\n4. 모든 데이터삭제\n5. 종료"<<endl;
		cin >> hashMenu;
		switch (hashMenu)
		{
		case HASH_ADD:
			{
			
				cout << "데이터값을 입력해주세요. :";
				cin >> num;
			
				hash[num %key].HashAdd(num);

			}
			break;
		case HASH_SEARCH:
			{
				cout << "검색할 데이터값을 입력해주세요. :";
				cin >> num;

				hash[num %key].HashSearch(num, num %key);
			}
			break;
		case HASH_REMOVE:
			{
				cout << "삭제할 데이터값을 입력해주세요. :" ;
				cin >> num;

				hash[num %key].HashRemove(num);
			}
			break;
		case HASH_CLEAR:
			{
				cout << "데이터를 전부 지웁니다."<<endl;

				for (int i = 0; i < key; i++)
					hash[i].HashClear();

			}
			break;
		case HASH_EXIT:
			{
				cout << "종료합니다." << endl;
				return;
			}
			break;
		default:
			break;
		}
		cout << endl << endl;

	}
}

