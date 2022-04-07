#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// 템플릿 타입 추론 규칙
/// 
/// T와 param의 Type 양쪽 모두가 &&일 때만 &&(R-Value 참조)
/// OR 연산이라고 생각하면 쉽다
/// 
/// typedef int& T;
///   T&	r1;		// T: int&	|| Type: &		--> r1은 int&
///   T&&	r2;		// T: int&	|| Type: &&		--> r2는 int&
/// 
/// typedef int&& U;
///   U&	r3;		// U: int&&	|| Type: &		--> r3은 int&
///   U&&	r4;		// U: int&&	|| Type: &&		--> r4는 int&&
/// </summary>


template<typename T>		// T
void foo(const T& param)	// const &T, ParamType이 다른 
{
	// T, param의 타입은??
}

/// <summary>
/// Case1
///   param의 타입이 포인터가 아니고 참조도 아닌 경우
///   param은 주어진 인수의 복사본, 즉 완전히 새로운 객체이다
///   
///   expr(표현식, 여기서는 인수)의 타입이 참조이면, 참조 부분은 무시한다
///   expr이 const이면 그 const 역시 무시한다
///   volatile이면 그것도 무시한다
/// 
///   즉, T는 auto와 비슷하게 동작한다
/// </summary>
template<typename T>	// T
void fooCase1(T param)	// const, &를 쓰고 싶으면 "const T& param"으로 쓴다
{
}

/// <summary>
/// Case2
///   param의 Type이 포인터 또는 참조 타입(T&)이지만 보편 참조(Universal Reference)가 아닌 경우
///   만일 expr이 참조 타입(&)이면 참조 부분을 무시한다
///   (즉 &만 무시하고 const는 그대로 간다)
/// </summary>
template<typename T>
void fooCase2(T& param)
{
}

/// <summary>
/// Case3
///   param의 Type이 보편 참조(Universal Reference)일 경우
///   보편 참조가 관여하면 L-Value 인수와 R-Value 인수에 대해서 서로 다른 추론 규칙들이 적용된다
///   만일 expr이 L-Value면, 정상적인(즉 Case2의) 규칙이 적용
///   만일 expr이 R-Value면, T는 &&를 무시하고, param의 Type를 R-Value 참조로 추론
///   (T는 &&를 무시하는 이유는 param의 Type에 &&를 붙이기 위해서)
///   보편 참조가 아닌 매개변수들에 대해서는 그러한 일이 절대 발생하지 않는다
/// </summary>
template<typename T>
void fooCase3(T&& param)
{
}

/// <summary>
/// Case4
/// </summary>
template<typename T>
void fooCase4(T param)
{
}

int main()
{
	int x = 0;
	const int cx = x;
	const int& rx = x;
	foo(x);				// T --> int, param의 Type --> const int&
	foo(cx);
	foo(rx);

	// ==================== Case1 ====================
	fooCase1(x);		// T --> int		|| param의 Type --> int
	fooCase1(cx);		// T --> int		|| param의 Type --> int
	fooCase1(rx);		// T --> int		|| param의 Type --> int
	fooCase1(11);		// T --> int		|| param의 Type --> int

	// ==================== Case2 ====================
	fooCase2(x);		// T --> int		|| param의 Type --> int&
	fooCase2(cx);		// T --> const int	|| param의 Type --> const int&
	fooCase2(rx);		// T --> const int	|| param의 Type --> const int&
	//fooCase2(11);		// L-Value인 param에 R-Value를 대입하는 것이라 컴파일 에러 

	// ==================== Case3 ====================
	fooCase3(x);		// T --> int		|| param의 Type --> int&
	fooCase3(cx);		// T --> const int&	|| param의 Type --> const int&
	fooCase3(rx);		// T --> const int&	|| param의 Type --> const int&
	fooCase3(11);		// T --> int		|| param의 Type --> int&&

	// ==================== Case4 ====================
	// "abc" 자체가 const char*(정확히는 char[])
	const char* const ptr = "abc";	// prt는 const 객체를 가리키는 const 포인터
	fooCase4(ptr);					// const char* const 타입의 인수로 전달

	const char name[] = "abc";		// name은 배열
	fooCase4(name);					// T와 param의 Type 모두 const char*

	int arr[3] = { 1, 2, 3 };
	int* ptr1 = arr;
	int(*ptr2)[3] = &arr;

	cout << ptr1 << ", " << ptr1 + 1 << endl;
	cout << ptr1 << ", " << ptr2 + 1 << endl;

	return 0;
}