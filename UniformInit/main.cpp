#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
//using namespace std::literals;

/// <summary>
/// 유니폼 초기화(Uniform initialization)
/// 균일한 초기화, 중괄호 초기화라고도 한다
///   값의 축소, 변환(암시적 캐스팅 등)이 발생하지 않는다
///   함수와 객체 생성의 문법이 헷갈리는 경우를 방지한다
/// 
/// 
/// 
/// </summary>

/// <summary>
/// 초기화자 리스트(Initiaslizer List)
///   예) A a_IL = { 1, 2, 3, 4, 5 };
///
///   auto와 템플릿에 사용할 때에는 주의하자!
/// </summary>
class A
{
public:
	A() { cout << "A의 생성자 호출!!" << endl; }

	// ====================초기화자 리스트(Initiaslizer List) 활용 ====================
	A(std::initializer_list<int> il)
	{
		cout << "A의 생성자(initializer_list) 호출!!" << endl;

		for (auto itr = il.begin(); itr != il.end(); ++itr)
		{
			cout << *itr << endl;
		}
	}
};

class B
{
public:
	B(A a) { cout << "B의 생성자 호출!!" << endl; }
};


//template<typename T>
//void foo(T param) {}		// std::initializer_list는 추론하지 못 함
template<typename T>
void foo(std::initializer_list<T> param) {}

auto CreateInitList(void)
{
	//return { 1, 2, 3 };		// 오류! { 1, 2, 3 }의 타입을 추론할 수 없음!
	auto a = { 1, 2, 3 };
	return a;
}

struct T
{
	int i;
	string v;
	bool b;
};

class Widget
{
public:
	Widget(int i) {}
	Widget(double d) {}
	//Widget(std::initializer_list<double> il) {}
};

int main()
{
	// 일반적인 초기화
	int value1 = 5;
	// 변수(C++에서는 객체기도 함)의 초기화, 함수랑 헷갈린다는 문제가 있다
	int value2(5);
	// C++ 11의 유니폼 초기화(균일한 초기화, 중괄호 초기화)
	int value3{ 5 };
	// Default Initailization to 0
	int value4{};

	// ==================== 값의 축소, 변환(캐스팅 등)이 발생하지 않는다 ====================
	int v1(5.1);
	cout << v1 << endl;			// <-- 자동으로 캐스팅 됨

	//int v2{ 5.1 };	// <-- 컴파일 에러
	double v2{ 5.1 };
	int v3{ static_cast<int>(v2) };
	cout << v3 << endl;


	// ====================
	// A a; A a();
	// 뭐가 출력될까? A()는 함수? 아니면 객체?
	B tmpB(A()); // --> 아무것도 출력 안 됨

	// 위와 같은 상황을 방지하기 위해서 중괄호 초기화를 사용한다
	B b{ A{} }; // --> 생성자가 제대로 출력됨


	cout << "\n==================== 초기화자 리스트(Initiaslizer List) ====================" << endl;
	int arr[] = { 1, 2, 3, 4, 5 };
	vector<int> v = { 1, 2, 3, 4, 5 };
	map<string, int> m =
	{
		{"abc" , 1}, {"def", 2}
	};

	// 중괄호 초기화로 초기화하려고 하면
	// 생성자의 인수로 std::Initiaslizer_List가 있는지 먼저 확인한다
	A a_IL = { 1, 2, 3, 4, 5 };


	// ==================== 초기화자 리스트와 auto 사용 시의 주의점 ====================
	auto a_auto = 1;				// auto --> int
	auto b_auto{ 1 };				// auto --> int // auto b_auto = 1;와 같다
	auto c_auto = { 1, 2 };			// auto --> std::initializer_list<int>
	//auto d_auto{ 1, 2 };			// 컴파일 에러! // auto d_auto = 1, 2;와 같다!!
	//auto e_auto = { 1, 2, 3.0f };	// 컴파일 에러! auto를 추론할 수 없다!!

	auto list_1 = { "a", "b" };		// auto --> std::initializer_list<const char*>
	// 뒤에 s를 붙이면 string으로 바꿀 수 있다(using namespace std::literals가 필요?한가?)
	auto list = { "a"s, "b"s };		// auto --> std::initializer_list<std::string>


	// ==================== 초기화자 리스트와 템플릿 사용 시의 주의점 ====================
	// 초기화자 리스트는 auto와는 다르게 템플릿에서 추론을 하지 않으므로
	// std::initializer_list<T>와 같이 명시적으로 작성해야 한다
	// 예시) void foo(std::initializer_list<T> param);
	foo({ "a"s, "b"s });


	// ==================== 초기화자 리스트의 주의점 ====================
	// vector의 경우 다음의 초기화가 다르다!
	vector<int> v_tmp1(10, 20);		// 요소: 10개, 모두 20
	vector<int> v_tmp1{ 10, 20 };	// 요소: 2개, 10과 20


	// 생성자의 패러미터로 초기화자 리스트가 있는 경우
	// 초기화자 리스트를 우선으로 확인하고,
	// 초기화자 리스트가 감당할 수 있는 타입이면 해당 생성자가 호출되며
	// 아닐 경우는 다른 생성자를 찾는다
	T t{ 1, "acb", true };


}