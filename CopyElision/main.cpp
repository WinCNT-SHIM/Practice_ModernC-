#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

/// <summary>
/// Copy Elision(복사 생략) - C++11
///   컴파일러가 복사/이동 연산자를 회피할 수 있으면 회피하는 것을 허용하는 방식
///   Return Value Optimization(RVO) / Named Return Value Optimization(NRVO)
///   Passing Temporary as Value
///   주의) 컴파일러에 따라 지원 여부가 다를 수 있음
/// </summary>

/// <summary>
/// 1) Return Value Optimization(RVO) / Named Return Value Optimization(NRVO)
///   RVO / NRVO는 함수의 반환 값이 특정 객체의 값 형식일 때
///   복사 생성을 회피할 수 있도록 컴파일러 최적화를 의미한다
/// 
///   참고로 NRVO는 최적화 옵션 /O1부터 작동함
///   RVO는 최근의 모든 컴파일러가 지원해준다
///   (NRVO는 컴파일러마다 지원 여부가 다름)
/// </summary>
struct Foo
{
	Foo() { cout << "\n"; }
};

Foo RVO_F()
{
	return Foo();
}


int main()
{
	// 아래의 대입문에서 복사 생성을 생략 (Release 모드에서 확인)
	{
		Foo rvo_foo = RVO_F();
	}
	return 0;
}