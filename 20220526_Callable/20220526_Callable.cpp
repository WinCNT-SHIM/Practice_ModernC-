#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>
#include <algorithm> //for_each

#include <functional>

using namespace std;

/// <summary>
/// Callable이란
///   이름 그대로 호출(Call)할 수 있는 모든 것(함수, 함수 객체, 람다)
/// std::function
///   Callable들을 객체의 형태로 보관할 수 있는 클래스
///   함수를 매개변수로 전달 받거나 리턴, 그리고 보관할 때 편리
/// </summary>
/// <returns></returns>

int some_func1(const string& a)
{
	cout << "Func1 호출! " << a << endl;
	return 0;
}

struct S
{
	void operator() (char c) { cout << "Func2 호출!" << endl; }
};

class A
{
	int c;
public:
	A(int c) : c(c) {}
	int some_func()
	{
		cout << "비상수 함수 : " << ++c << endl;
		return c;
	}
	int some_const_func() const
	{
		cout << "상수 함수 : " << c << endl;
		return c;	//return this->c;
	}
	static void st() {}
};

// 콜리 --> 호출하는 권한
int callback_func(function<void(string)> fn);

struct Widget
{
	function<void(string)> fn;

	int ClickYes()
	{
		fn("yes");	// 2. 콜백 호출
		return 0;
	}
	int ClickNo()
	{
		fn("no");	// 2. 콜백 호출
		return 0;
	}
};

int main()
{
	// 함수
	function<int(const string&)> f1 = some_func1;
	// 함수 객체
	function<void(char)> f2 = S();
	// 람다
	function<void()> f3 = []() {cout << "Func3 호출!" << endl; };

	f1("hello");
	f2('c');
	f3();

	A a(5);

	/// <summary>
	/// 클래스의 멤버 함수들의 경우
	///   암시적 변환이 발생하지 않으므르,
	///   & 연산자를 통해 명시적으로 주소값을 전달해줘야 한다
	/// </summary>
	function<int(A&)> f_a_1 = &A::some_func;
	function<int(const A&)> f_a_2 = &A::some_const_func;	// const 타입

	f_a_1(a);
	f_a_2(a);

	// 콜러 --> 함수를 생성하는 권한
	// 1. 람다 전달
	//callback_func(
	//	[](string s) -> void
	//	{
	//		if (s == "yes") cout << "yes" << endl;;	// 3. 결과에 따라 처리
	//		if (s == "no") cout << "no" << endl;;
	//	}
	//);
	
	Widget widget;
	// 콜러 --> 함수를 생성하는 권한
	// 미래에 대한 처리를 미리 결정해 둠
	widget.fn = [](string s) -> void
	{
		if (s == "yes") cout << "yes" << endl;;	// 3. 결과에 따라 처리
		if (s == "no") cout << "no" << endl;;
	};
	
	cout << "========== 다른 처리 중 ==========" << endl;

	// 미리 결정해둔 처리를 지연해서 처리함
	widget.ClickYes();
	widget.ClickNo();

	return 0;
}
