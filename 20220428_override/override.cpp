#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

/// <summary>
/// override
/// 
/// 멤버 함수 참조 한정자 C++11
///   const : 상수 멤버를 사용하겠다
/// 
/// 
/// </summary>

class Base
{
public:
	Base() {};
	~Base() {};

	virtual void mf1(void) const;
	virtual void mf2(int x);
	virtual void mf3(void)&;		// 멤버 함수 참조 한정자
	virtual void mf4(void) const;
};

class Derived : public Base
{
public:
	Derived() {};
	~Derived() {};

	// 아래의 함수들은 모두 override가 되지 않음
	virtual void mf1(void);				// const 없음
	virtual void mf2(unsigned int x);	// unsigned 있음
	virtual void mf3(void)&&;			// R-Value
	void mf4(void) const;				// virtual 키워드 없음

	// override를 써주면 컴파일 에러를 발생시켜주므로 써주자
	virtual void mf1(void) const override;
	virtual void mf2(int x) override;
	virtual void mf3(void)& override;
	virtual void mf4(void) const override;

};

int main(void)
{
	

	return 0;
}