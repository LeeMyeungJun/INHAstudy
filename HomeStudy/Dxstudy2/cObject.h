#pragma once
class cObject
{
public:
	cObject();
	//~cObject();

protected:
	ULONG m_ulRefCount; //마이너스가 될이유가없지 int형이여도됨
public:
	virtual ~cObject(void);
	virtual void AddRef();
	virtual void Release();

	

	
};

