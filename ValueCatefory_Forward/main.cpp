#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// 보편적 참조, 보편적 레퍼런스(Universal Reference)
/// auto&&로 사용할 수 있다
/// 컴파일러가 lValue인지 rValue인지 알아서 추정해준다
/// 컴파일 만들 때 유용하다
/// 
/// forward(): rValue일 때 move(rValue)로 바꿔준다
/// 
/// </summary>
/// <returns></returns>

class A
{
};

void foo(A& a)			{ cout << "좌측 값 레퍼런스 호출" << endl; }
void foo(const A& a)	{ cout << "좌측 상수 값 레퍼런스 호출" << endl; }
void foo(A&& a)			{ cout << "우측 값 레퍼런스 호출" << endl; }

// 위의 함수들을 템플릿으로 만들자!!
template <typename T>
void wrapper(T&& u)		// T&&는 보편 참조(auto&&)와 같다
{
	// u자체는 lValue이므로 인수에 rValue를 넣더라도
	// foo(A& a), foo(const A& a) 밖에 호출하지 않는다
	// 즉, 템플릿의 의미가 없어진다
	//foo(u);

	// 매개 변수인 u자체는 변수(lValue)이지만, std::forward 함수는
	// 실제의 인수가 lValue일 때는 lValue 그대로 전달하므로 foo(A& a)나 foo(const A& a)를 호출,
	// 실제의 인수가 rValue일 때는 u를 rValue로 캐스팅 전달하므로 foo(A&& a)를 호출한다
	// 실제의 인수가 lValue인지 rValue인지 모를 때 사용하자
	foo(forward<T>(u));
}

int main()
{
	const int i = 10;
	auto& var = i;
	
	// 보편 참조
	// auto&&가 자동으로 lValue, rValue를 추론해줌
	auto&& var2 = i;	// const int&로 연역해줌
	auto&& var3 = 12;	// int&&로 연역

	// rValue 참조에 lValue를 대입하면 컴파일 에러(보편 참조가 아님)
	//int&& var2 = i;
	// const auto&&에 lValue를 대입하면 컴파일 에러 발생(보편 참조가 아님)
	//const auto&& var4 = i;

	// ==================== ====================
	A a;
	const A cA;

	// 원본
	cout << "원본" << endl;
	foo(a);
	foo(cA);
	foo(A());

	// Wrapper
	cout << "Wrapper" << endl;
	wrapper(a);
	wrapper(cA);
	wrapper(A());
}