#include <iostream>
#include <string>
#include <vector>


/// <summary>
///									  이동 가능			이동 불가능
/// 정체 명확(주소 획득 가능)		xvalue(int&&)		lvalue(int&)
/// 정체 불명(주소 획득 불가능)		prvalue(int)		 무다무다!
/// 
/// xvalue 식
/// std::move(a)가 xvalue이다
/// 주소 값 있는 것을 move()로 감싼 것
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
///		레퍼런스가 아닌 것을 리턴하는 함수의 호출식 --> str.substr(1, 2), str1 + str2
///		후위 증감 연산자 식 --> a++, a--
///		산술 연산자, 논리 연산자 식 --> a + b, a && b, a < b 등
///		주소값 연산자 식 --> &a
///		this, enum 값, 람다식[]() { return 0; }
/// </summary>
int main()
{
	// move함수: lvalue에 대해서도 빠르게 이동을 시키기 위한 함수
	int a = 3;
	//int&& n = a;	// 컴파일 에러
	int&& n = std::move(a);	// 이동 연산으로 복사 연산보다 빠르게 연산 가능


}