#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T1, typename T2>
void ex_func(T1 lvar, T2 rvar)
{
	// 방법 1: auto
	auto prod1 = lvar * rvar;	// 타입 T1, T2는 실행 후에 결정되므로 auto는 나중에 추론

	// 방법 2: typedef
	typedef decltype(lvar* rvar) product_type;	// not 계산! only 추론!
	product_type prod2 = lvar * rvar;

	// 방법 3: decltype
	decltype(lvar * rvar) prod3 = lvar * rvar;	// 컴파일 단계에서 decltype 추론
}

struct A
{
	double d;
};

int main()
{
	int ex_a = 0;
	int& ex_b = a;
	const int& ex_c = 0;

	// auto와 마찬가지로 const, 참조형을 무시한다
	cout << typeid(ex_a).name() << endl;	// int
	cout << typeid(ex_b).name() << endl;	// int
	cout << typeid(ex_c).name() << endl;	// int

	// 위와 같은 문제를 해결하기 위한 키워드가 decltype
	// 컴파일 단계에서 타입을 결정한다
	// 따라서 컴파일 단계에서 타입이 결정되는 템플릿 내부에서 주로 사용된다
	const int& ex_d = 0;
	decltype(ex_d) e1 = ex_d;	// e1는 const int&, d의 형식을 그대로 가져온다




	// decltype(표현식)에서 표현식이 복잡해지면 명확성이 떨어진다
	int a = 3;
	decltype(a) b = 2;		// int

	// &: lvalue 참조자
	int& ra = a;
	decltype(ra) rb = b;		// int&

	// &&: rvalue 참조자
	// lvalue에는 변수, rvalue에는 변수/상수가 온다
	// rvalue에 계속 접근할 수 있다
	int&& x = 3;
	decltype(x) y = 2;			// int&&
	
	A* aA;
	decltype(aA->d) dd = 0.1;	// double

	int a1 = 3;
	int a2 = 3;
	int c = a1 + a2;
	// 표현식은 lvalue일 수도 있고, rvalue일 수도 있다
	// a1 + a2의 경우는 결과 값이 상수이므로 rvalue이다
	decltype(a1 + a2) c1 = 2;
	// 다음과 같이 쓰면 알기 쉽다
	decltype(c) c1_1 = 2;

	// (c): c를 가르키고 있는 참조자로 변한다(...)
	//decltype(  (c)  ) c2 = 2; // lvalue를 지정해야 함

//컴파일러는 다음 규칙을 사용하여 식 매개 변수의 형식을 확인합니다.
//	식 매개 변수가
//		식별자 또는 클래스 멤버 액세스인 경우: 식으로 명명된 엔터티의 형식
//		함수 또는 오버로드된 연산자 함수에 대한 호출인 경우: 함수의 반환 형식(오버로드된 연산자를 묶는 괄호는 무시)
//		rvalue이면 식의 형식
//		lvalue이면 식 형식에 대한 lvalue 참조


// 1. 괄호로 둘러쌓이지 않은 식별자 표현식
// 	   변수의 이름, 함수의 이름, enum 이름, 클래스 멤버 변수 등 이름이 있는 것
// 	   어떠한 연산도 하지 않고 단순히 객체 하나만을 가르키는 식
// 
// 2. 식별자 표현식이 아닌 식을 전달하면
// 	   만일 식의 값 종류가 prvalue라면 decltype은 T		ex) int
// 	   만일 식의 값 종류가 lvalue라면 decltype은 T&		ex) int&
// 	   만일 식의 값 종류가 xvalue라면 decltype은 T&&	ex) int&&
// 
// 	   (c)는 ()로 인해 식별자가 아닌 표현식이다
//
}