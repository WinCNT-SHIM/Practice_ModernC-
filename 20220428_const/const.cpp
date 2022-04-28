#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <array>

using namespace std;

/// <summary>
/// constexpr
///   객체나 함수 앞에 붙일 수 있는 키워드로,
///   해당 객체나 함수의 리턴 값을 "컴파일 타임"에 값을 알 수 있다는 의미
///   정수 상수 표현식(Integral Constant Expression)이 요구되는 문맥에서 사용할 수 있다
///   객체의 정의에 constexpr이 오게 된다면, 해당 객체는 어떠한 상수식에도 사용될 수 있음
/// 
/// 상수 표현식, 정수 상수식
///   1. 배열을 선언하는 경우
///   2. 템플릿 타입 인자
///   3. enum에서 값을 지정
/// 
/// constexpr 함수
///   constexpr을 함수에 붙일 수 있다면 붙이는 것이 좋다
///   왜냐하면 constexpr처럼 동작하지 못한다면 그냥 일반 함수 처럼 작동하고,
///   컴파일 타임 상수를 생성할 수 있는 상황이라면 간단히 이용할 수 있기 때문
/// 
/// constexpr 생성자(C++14)
///   C++14부터 constexpr 생성자를 지원함으로써,
///   사용사들이 리터럴 타입들을 직접 만들 수 있게 되었다
///   리터럴 타입은 쉽게 생각하면 컴파일러가 컴파일 타임에 정의할 수 있는 타입을 의미
///     constexpr 함수는 반드시 리터럴 타입들을 받고 돌려줘야 한다
///     constexpr 생성자는 반드시 리터럴 타입이여야만 하고,
///     해당 클래스는 다른 클래스를 가상 상속 받을 수 없다
/// 
/// if constexpr
///   컴파일 타임에 상수 표현식의 boolean(true/false)를 평가한다
///   if constexpr은 조건이 반드시 bool로 타입 변환될 수 있어야 하는 컴파일 타임 상수식이어야만 한다
///   템플릿 특수화 등을 하지 않고도 분기 처리가 쉽게 표현 가능해짐
/// 
/// </summary>

int get_int()
{
	return 1;
}

class A
{
public:
	// v 값의 변화가 없을 경우는 const를 붙이자
	void SetVector(const vector<int>& v) {}
	// v 값의 변화가 없을 경우는 const를 붙이자
	void PrintVec() const {}
	const string& GetNameRef() { return name; }
private:
	string name;
	vector<int> m_v;
};

template<int N>
struct  AA
{
	int operator()() { return N; }
};

constexpr int Factorial(int n)
{
	int total = 1;
	for (int i = 1; i <=n; i++)
	{
		total *= i;
	}
	return total;
}

/// constexpr 생성자(C++14)
class Vector
{
public:
	constexpr Vector(int x, int y) : x_(x), y_(y) {}
	constexpr int x() const { return x_; }
	constexpr int y() const { return y_; }

private:
	int x_;
	int y_;
};

/// constexpr 생성자(C++14)
constexpr Vector AddVec(const Vector& v1, const Vector& v2)
{
	return { v1.x() + v2.x(), v1.y() + v2.y() };
}

/// if constexpr
#include <type_traits>
template <typename T>
void show_value(T t)
{
	if constexpr (is_pointer<T>::value)
	{
		cout << "포인터이다" << endl;
	}
	else
	{
		cout << "포인터가 아니다" << endl;
	}

}

// if constexpr가 없으면 아래와 같이 작성해야 함
// 타임 추정에 실패하면 에러 발생이 아니라 스킵되기 때문에 의사 if문으로 사용했다
template<typename T, enable_if_t < is_pointer<T>{} > * = nullptr >
auto get_value(T t)
{
	return *t;
}
template<typename T, enable_if_t < !is_pointer<T>{} > * = nullptr >
auto get_value(T t)
{
	return t;
}

int main(void)
{
	// 컴파일러가 최정화
	const int a = 0;
	// 변수 할당 간으, 값이 컴파일 타임에 정해진다는 보장 없음
	const int b = a;

	// 컴파일 타임에 상수로 결정되는 것이 아니라
	// 런타임으로 받아온 값을 유지할 것이라는 알 수 있다
	// 따라서 템플릿에는 사용할 수 없다
	const int c = get_int();			// 컴파일

	// constexpr 컴파일 타임에서 사용할 때 더 확실히 오류 검출
	constexpr int a2 = 0;
	constexpr int b2 = a2;
	// get_int()가 런타임에 확정되므로 constexpr는 컴파일 오류가 발생한다
	//constexpr int c2 = get_int();		// 컴파일 오류


	// ==================== const vs constexpr ====================
	// 1. 배열을 선언하는 경우
	int sz = 10;
	const auto arraySize1 = sz;
	//array<int, arraySize1> data1;	// 컴파일 에러

	constexpr auto arraySize2 = 10;	// OK, 10은 확실히 컴파일 시점에서 상수
	array<int, arraySize2> data2;

	// 2. 템플릿 타입 인자
	constexpr auto N = 10;
	AA<N> a_ex;

	// ==================== constexpr 함수 ====================
	// Factorial(5)는 constexpr
	AA<Factorial(5)> a3;
	cout << a3() << endl;

	// 일반 함수처럼 동작
	int n;
	cin >> n;
	cout << Factorial(n) << endl;

	// ==================== constexpr 생성자 ====================
	constexpr Vector v1{ 1, 2 };
	constexpr Vector v2{ 2, 3 };

	// constexpr 객체의 constexpr 멤버 함수는 역시 constexpr!
	AA<v1.x()> aa1;
	cout << aa1() << endl;

	// AddVec 역시 constexpr를 리턴한다
	AA<AddVec(v1, v2).x()> AAb1;
	cout << AAb1() << endl;


	// ==================== if constexpr ====================
	cout << endl;
	cout << "if constexpr" << endl;
	int x = 3;
	show_value(x);
	int* p = &x;
	show_value(p);


	return 0;
}