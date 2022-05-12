#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>

using namespace std;

/// <summary>
/// 기본 연산 활성화
/// C++11에서는 명시적으로 선언된 특수 멤버 함수가 기본 행동을 사용하겠다는 의사를
/// = default를 이용해서 명시적으로 표현할 수 있다
/// </summary>
class Widget
{
public:
	~Widget(void) {};								// 
	Widget(const Widget&) = default;				// 기본 복사 대입, 기본 행동 OK
	Widget& operator=(const Widget&) = default;		// 기본 복사 대입, 기본 행동 OK
};

/// <summary>
/// 파생 클래스 객체들을 조작하는데 쓰이는 인터페이스를 정의하는 클래스에 유용
/// 상속 시 소멸자의 경우 부모 클래스가 가상일 경우 자식도 가상으로 자동 생성된다
/// </summary>
class Base
{
public:
	virtual ~Base(void) = default;	// 소멸자를 가상으로
	Base(Base&&) = default;
	Base& operator=(Base&&) = default;
	Base(const Base&) = default;
	Base& operator=(const Base&) = default;
};

class StringTable
{
public:
	StringTable(void) {}
	~StringTable(void) {}

private:
	std::map<int, std::string> value;
};

/// <summary>
/// 멤버 함수 템플릿이 존재하면 특수 멤버 함수의 자동 작성이 비활성화된다는 규칙은 없음!!
/// 
/// </summary>
class Widget2
{
public:
	template <typename T>
	Widget2(const T& rhs) {}
	template <typename T>
	Widget2(const T&) {};
};