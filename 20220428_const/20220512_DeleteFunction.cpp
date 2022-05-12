#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>

using namespace std;

/// <summary>
/// 삭제된 함수(Delete Function)
/// 
/// 정의되지 않은 비공개 함수보다 삭제된 함수를 선호하라
/// 
/// 어떤 함수의 사용을 막고 싶으면
/// 1. 함수를 private으로 선언하고 함수의 정의를 만들지 않는 방법	// C++98 priavate
/// 2. 사용을 막을 함수의 선언 끝에 "= delete"를 붙이는 것			// C++11 delete
/// 
/// 사용을 막아둔 함수를 사용하려고 했을 경우, 
///   C++98은 링크 시점에 가서야 발견되지만
///   C++11의 삭제된 함수는 컴파일 시점에서 발견할 수 있다
/// </summary>

class A
{
public:
	A() = delete;
	void Func() = delete;
};

template<class charT, class traits = char_traits<charT>>
class basic_ios : public ios_base
{
	basic_ios(const basic_ios&) = delete;
	basic_ios& operator=(const basic_ios&) = delete;
};

bool isLucky(int number) { return true; }
// 암묵적 형변환을 방지(객체의 explicit와 비슷)
bool isLucky(char) = delete;
bool isLucky(bool) = delete;
bool isLucky(double) = delete;

template<typename T>
void processPointer(T* ptr) {}
// 원하지 않은 템플릿 인스턴스화 방지
template<>
void processPointer(char*) = delete;		// char* 타입의 포인터로 호출 불가
template<>
void processPointer(const char*) = delete;	// const char* 타입의 포인터로 호출 불가

int main()
{
	if (isLucky(7))	{}
	//if (isLucky('a')) {}		// 암묵적 형변환 방지
	//if (isLucky(true)) {}		// 암묵적 형변환 방지
	//if (isLucky(3.5)) {}		// 암묵적 형변환 방지

	return 0;
}