
#define SafeRelease(p) {if(p) p->Release() ; p = NULL;} //�ִ� �İ� ������ ���°Ŵ� .

#define SafeDelete(p){if(p) delete p; p = NULL;} //delete ��ũ��

//>> :�̱��� ��ũ��
#define Singletone(class_name) \
private: \
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance() \
	{ \
		static class_name instance;\
		return &instance;\
	}
//<< :


//get set ��ũ�� 
#define Synthesize(varType , varName, funName) \
	protected: varType varName; \
	public: inline varType Get##funName(void) const{ return varName;}\
	public: inline void Set##funName(varType var) {varName = var;}


//�ּڰ� get set ��ũ��
#define Synthesize_pass_by_Ref(varType , varName, funName) \
	protected: varType varName; \
	public: inline varType& Get##funName(void) const{ return varName;}\
	public: inline void Set##funName(varType& var) {varName = var;}
