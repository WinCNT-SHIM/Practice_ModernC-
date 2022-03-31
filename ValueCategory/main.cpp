#include <iostream>
#include <string>
#include <vector>


/// <summary>
///									  이동 가능			이동 불가능
/// 정체 명확(주소 획득 가능)		xvalue(int&&)		lvalue(int&)
/// 정체 불명(주소 획득 불가능)		prvalue(int)		 무다무다!
/// 
/// lvalue 식
/// 객체를 참조하는 표현식(메모리 위치를 가지고 있음)
/// 
/// rvalue 식
/// lvalue가 아닌 모든 것
/// 정확하게 말하자면, 구분 가능한 메모리 영역을 가지는 객체를 나타낼 필요가 없는 표현
/// (즉, 메모리에 보관할 필요가 없는 것들)
/// 포인터보다 안전하게 참조할 수 있게 되었다
/// 
/// prvalue 식
/// 정체 불명의, 즉 주소값을 획득할 수 없으며, 좌측에 올 수 없다
/// 우측 값 레퍼런스와 상수 좌측 값 레퍼런스를 초기화하는데 사용한다
/// 예)
///		int&& r = 42;
///		const int& = 42;
///		int& rrr = 42; // 컴파일 에러
/// 
///		문자열 레터럴을 제외한 모든 리터럴들 --> 42, true,nullptr 등등
///		(문자열은 가변이므로 lvalue로써 취급해야 한다)
///		레퍼런스가 아닌 것을 리턴하는 함수의 호출식 --> str.substr(1, 2), str1 + str2
///		후위 증감 연산자 식 --> a++, a--
///		산술 연산자, 논리 연산자 식 --> a + b, a && b, a < b 등
///		주소값 연산자 식 --> &a
///		this, enum 값, 람다식[]() { return 0; }
/// 
/// 
/// glvalue 식
/// 주소를 가질 수 있는 것을 통합하면서 생겨난 개념
/// 
/// xvalue 식
/// C++11에서 ravalue의 추가로 생겨난 개념
/// 원래는 사용하고 없어질 ravalue를 잠시 보관할 수 있게 되면서 생겨났다
/// 또한 xvalue가 생겨남으로써 "이동"에 대한 개념도 생겨났다
/// 
/// std::move(a)가 xvalue이다(주소 값 있는 것을 move()로 감싼 것)
/// (이동에 대한 자세한 내용은 ValueCategory_Move에 정리)
/// 
/// </summary>

int NextVal_1(int* p);
int* NextVal_2(int* p);

class A
{
	static int g();
	int f();
};

int main()
{
	// move함수: lvalue에 대해서도 빠르게 이동을 시키기 위한 함수
	int a = 3;

	// 포인터형과 참조형(구조적으로는 같다)
	int* c_1 = &a;	// 결국 변수이기 때문에 바뀔 수 있다
	int& b_1 = a;		// 손쉽게 매개변수 등을 전달할 수 있다
	
	// =의 왼쪽: lvalue만 가능
	// =의 오른쪽: lvalue, rvalue 둘 다 가능
	// lvalue에는 변수(주소를 가진 것)만 올 수 있다
	int c_2 = a;

	int a_3 = 3;
	int& b_3 = a_3;	// lvalue 참조
	//int& c = 3;	// 컴파일 에러
	int&& c = 3;	// 그래서 rvalue 참조라는 새로운 문법을 추가
	
	// C++11부터는 상수 또한 참조를 할 수 있게 되었다

	//int&& n = a;	// 컴파일 에러
	int&& n = std::move(a);	// 이동 연산으로 복사 연산보다 빠르게 연산 가능


	// ==================== MSDN 예제 ====================
	int i, j, * p;
	i = 7;

	// 왼쪽이 특정 상수(즉, prvalue)가 되서 컴파일 에러 발생
	//7 = i; // C2106
	//j * 4 = 7; // C2106

	// 포인터 참조는 lvalue라서 OK
	*p = i;

	// 왼쪽의 식은 결국 변수라서 OK
	((i < 3) ? i : j) = 7;

	// const로 int가 prvalue로 변경되서 컴파일 에러 발생
	const int ci = 7;
	//ci = 9;	// C3892


	// ==================== 예제 ====================
	int arrA[] = { 1, 2, 3, 4, 5 };
	//NextVal_1(arrA) = 9;	// 반환 값이 rvalue라서 컴파일 에러
	*NextVal_2(arrA) = 9;


	// ==================== 예제 ====================
	A classA;	// lvalue
	//classA.g;	// lvalue(어딘가 보관하고 있기 때문)
	//classA.f;	// lvalue 아님, 함수의 주소 값 자체이므로 prvalue


	// ==================== 예제 ====================
	int&& r_1 = 42;
	const int& rr_1 = 42;
}

int NextVal_1(int* p) { return *(p + 1); }
int* NextVal_2(int* p) { return (p + 1); }

// ==================== 예제 ====================
void Func1(int&& a)
{
	// a 자체는 변수이므로 lvalue
	// 형태가 rvalue 참조형일 뿐!!
	a;
}