#pragma once
class ChainHash
{
	
public:
	vector<int> hash;
	vector<int>::iterator it;

	ChainHash();
	~ChainHash();

	void Hashinit();


	void HashSearch(int, int);
	void HashAdd(int);
	void HashRemove(int);
	void HashClear();

	
};

