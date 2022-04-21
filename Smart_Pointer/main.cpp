#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>

using namespace std;

/// <summary>
/// 스마트 포인터의 개요
///   <memory> 헤더 파일에 존재한다
///   C++에서는 메모리 누수로부터 프로그램의 안전성을 보장하기 위해 스마트 포인터를 제공
///   스마트 포인터란 포인터처럼 동작하는 클래스 템플릿으로
///   사용이 끝난 메모리를 자동으로 해제해준다
/// 
/// C++11부터 다음과 같은 스마트 포인터를 제공한다
///   unique_ptr<> : 배타적 소유권
///   shared_ptr<> : 공유 자원 관리
///   weak_ptr<>   : shared_ptr를 보완하기 위해 사용
///   (과거에는 auto_ptr이란 것도 존재했음)
/// 
/// C++에서 자원을 관리하는 방법
/// RAII(Resource Acquisition Is Initialize) 패턴
///   자원의 획득은 초기화이다
///   획득한 동시에 해제에 대해서도 확실하게 설정하기
///   스택에 할당된 메모리는 자동으로 해제되는 것을 이용한 디자인 패턴
/// 
/// </summary>

class Foo
{
public:
	Foo() { cout << "생성\n"; }
	Foo(int) { cout << "생성(int)\n"; }
	~Foo() { cout << "소멸\n"; }
};

/// <summary>
/// RAII 패턴 예제
/// </summary>
class MyString
{
public:
	char* c = nullptr;
	MyString(size_t len)
	{
		// RAII - 자원의 획득은 초기화이다
		cout << "MyString 자원 획득함!\n";
		c = new char[len];
	}
	~MyString()
	{
		// RAII - 해제 시에는 자원의 해제도 확실하게!
		cout << "MyString 자원 delete!\n";
		delete[] c;
	}

	void func() { cout << c << endl; }
};

class MyString_SPtr
{
	MyString* data;
public:
	MyString_SPtr(MyString* d):data(d) { }
	~MyString_SPtr() { delete data; }

	MyString& operator*() const { return *data; }	// *
	MyString* operator->() const { return data; }	// ->
};

int main()
{
	Foo* ptr = new Foo();
	delete ptr;

	// 내가 생성한 객체를 스마트 포인터가 관리하라는 느낌
	unique_ptr<Foo> smartPtr1(new Foo());				// C++11
	// 위의 코드를 보완한 것
	unique_ptr<Foo> smartPtr2 = make_unique<Foo>();	// C++14
	auto smartPtr3 = make_unique<Foo>();

	cout << "중괄호 start\n";
	{
		auto smartPtr4 = make_unique<Foo>();
	}
	cout << "중괄호 end\n";

	// ==================== 스마트 포인터 구현 예제 ====================
	// RAII 패턴 예제
	cout << "\n일반 MyString\n";
	{
		MyString* a = new MyString(100);
		strcpy_s(a->c, 14, "Hello, World!");
		//MyString a(100);
		//strcpy_s(a.c, 14, "Hello, World!");
	}
	cout << "\n";

	cout << "\nMyString_SPtr\n";
	{
		MyString_SPtr sp = new MyString(100);	//MyString* sp = new MyString(100);
		strcpy_s(sp->c, 14, "Hello, World!");
		sp->func();
	}
	cout << "\n";

	// ==================== unique_ptr 예제 ====================
	cout << "unique_ptr with unique_ptr\n";
	{
		unique_ptr<MyString> pa(new MyString(100));
		strcpy_s(pa->c, 14, "Hello, World!");
		pa->func();
	}
	cout << "\n";

	cout << "unique_ptr with unique_ptr\n";
	{
		unique_ptr<MyString> pa2 = make_unique<MyString>(100);
		strcpy_s(pa2->c, 14, "Hello, World!");
		pa2->func();
	}
	cout << "\n";

	return 0;
}