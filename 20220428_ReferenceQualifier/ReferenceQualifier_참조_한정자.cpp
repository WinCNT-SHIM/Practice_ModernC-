#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

/// <summary>
/// 멤버 함수 참조 한정자 (Reference Qualifier)
///   this 함수 참조 한정자를 지정하여,
///   암시적 개체 매개변수가 L-Value인지 R-Value인지에 따라,
///   비정적 멤버함수를 오버로드 할 수 있다
/// </summary>

struct MyStruct
{
	void func()& { cout << "L-Value" << endl; }
	void func() && { cout << "R-Value" << endl; }
	void func() const& { cout << "const L-Value" << endl; }
};

// 연산자 오버로딩에서도 사용 가능
template <typename T>
class A
{
public:
	A() {}
	~A() {}

	T const& operator*() const& { T _tmp; return _tmp; }
	T& operator*()& { T _tmp; return _tmp; }
	T&& operator*() const&& { T _tmp; return move(_tmp); }
};

int main(void)
{
	MyStruct s;
	s.func();				// L-Value

	MyStruct().func();		// R-Value, 임시 객체이므로 R-Value

	std::move(s).func();	// R-Value, 이동이므로 R-Value

	const MyStruct s2;
	s2.func();				// const L-Value


	// 연산자 오버로딩에서도 사용 가능
	cout << "연산자 오버로딩에서도 사용 가능" << endl;
	// const&는 오버로드가 const, non - const 및 L-Value 객체에만 사용된다는 것을 의미한다
	const A<int> a1 = A<int>();
	*a1;

	// &는 오버로드가 상수가 아닌 객체에만 사용된다는 것을 의미한다
	A<int> a2;
	*a2;

	// &&는 R-Value 객체에만 사용된다는 것을 의미한다
	*A<int>();

	return 0;
}