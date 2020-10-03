
#define SafeRelease(p) {if(p) p->Release() ; p = NULL;} //애는 컴과 연결을 끊는거다 .

#define SafeDelete(p){if(p) delete p; p = NULL;} //delete 매크로

//>> :싱글톤 매크로
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


//get set 매크로 
#define Synthesize(varType , varName, funName) \
	protected: varType varName; \
	public: inline varType Get##funName(void) const{ return varName;}\
	public: inline void Set##funName(varType var) {varName = var;}


//주솟값 get set 매크로
#define Synthesize_pass_by_Ref(varType , varName, funName) \
	protected: varType varName; \
	public: inline varType& Get##funName(void) const{ return varName;}\
	public: inline void Set##funName(varType& var) {varName = var;}
