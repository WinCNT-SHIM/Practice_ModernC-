#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// 복사 생성자와 복사 대입 연산사
///		T(const T& p);
/// 
/// 복사 생성자가 사용되는 경우
/// 1. 객체의 선언 및 초기화: A a(b);
/// 2. 객체의 값에 의한 전달: 
/// 3. 객체의 값에 의한 반환: A F() {  }
/// 
/// 
/// 이동 생성자
///		T(T&& a) [noexcept];
///		이동 생성자는 호출되면 얕은 복사(shallow copy)를 하고 원본의 소유권을 대상으로 이전(move)하고
///		원본 객체를 nullptr로 초기화하여 접근할 수 없게 만든다
///		(나중에 delete 처리를 안 해도 됨)
///		이동 생성자와 복사 생성자를 모두 구현하면, 코드 상황에 따라 복사 혹은 이동이 된다
/// 
/// 번외) noexcept
///		이동 생성자는 주소가 없어지기 때문에 주소 이전 도중에 예외를 발생시키면
///		복구가 불가능하게 되므로, 문제가 생긴다
/// 
/// 이동 생성자의 호출 조건
///		1. 임시 객체를 전달할 때
///		2. std::move()를 사용하여 인자를 rValue 참조자로 변환하여 전달할 때
/// 
/// 이동 생성자 및 이동 할당 연산자를 작성하면,
///		적은 복사, 메모리 할당 및 메모리 할당 취소 작업을 수행하기 때문에 효율적이다
/// 
/// 클래스를 설계할 때,
///		복사 생성자를 안 만들고 이동 생성자만 만들 수도 있으며, 그 반대도 가능하다
/// 
/// 번외) explicit
///		
/// </summary>
/// <returns></returns>

class A
{
public:
	A()				{ cout << "일반 생성자 호출!" << endl; }
	A(const A& a)	{ cout << "복사 생성자 호출!" << endl; }
	A(A&& a)		{ cout << "이동 생성자 호출!" << endl; }

	A& operator=(const A& rhs)
	{
		if (this != &rhs)
		{
			cout << "복사 대입 연산자" << endl;
		}
	}
};

class B
{
public:
	//B(A a) { }
	B(const A& a) : m_a(a) {}
	B(A&& a) : m_a(move(a)) { }
	A m_a;
};

int main()
{
	A a;
	A a2(a);
	A a3(move(a));

	cout << "Create B\n";

	B b1((a));
	B b2(a);
	//B b3(move(a));
}