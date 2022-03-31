#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// 보편 참조
/// auto&&
///		
/// </summary>
/// <returns></returns>

class A {};

void g(A& a) { cout << "좌측 값 레퍼런스 호출" << endl; }
void g(const A& a) { cout << "좌측 상수 값 레퍼런스 호출" << endl; }
void g(A&& a) { cout << "우측 값 레퍼런스 호출" << endl; }

template <typename T>
void wrapper(T&& u)		// T&&는 보편 참조, u자체는 변수이므로 lValue
{
	// u자체는 변수(lValue)이므로 좌측 값 레퍼런스, 혹은 좌측 상수 값 레퍼런스 밖에 호출되지 않는다
	// 즉, 템플릿의 의미가 없어진다
	g(u);

	// 매개 변수인 u자체는 변수(lValue)이지만, std::forward 함수는
	// 실제의 인수가 좌측 값일 때는 &, 우측 값일 때는 &&로 그대로 보내줌
	// 실제의 인수가 lValue인지 rValue인지 모를 때 사용하자
	g(forward<T>(u));
}

int main()
{
	const int i = 10;
	
	auto& var = i;
	
	// 보편 참조
	// auto&&가 자동으로 lValue, rValue를 추론해줌
	//int&& var2 = i;	// lValue를 대입하려고 했으니 컴파일 에러(보편 참조가 아님)
	auto&& var2 = i;	// const int&로 연역해줌
	auto&& var3 = 12;	// int&&로 연역

	// const auto&&은 보편 참조가 아니므로 컴파일 에러 발생
	//const auto&& var4 = i;
}