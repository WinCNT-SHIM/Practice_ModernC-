#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// 임시 객체, 또는 익명 객체(Temporary Object)
///		익명 객체는 R-Value처럼 작동한다
///		따라서 익명 객체는 생성되고 멤버를 호출한 후 실행이 끝나자마자 바로 사라진다
///		익명 객체는 Move 등을 사용하면 효율적이다
/// </summary>

class A
{
public:
	void Print() { cout << "Hello, World!" << endl; }
};


int main()
{
	// 일반적인 객체
	int n = 1;
	// 아래는 n = 1;와 같음
	int n2(1);
	int n3{ 1 };

	// 임시 객체(익명 객체)
	int(1);		// 1이라는 값이 할당된 이름 없는 객체

	// 일반적인 클랙스의 객체
	A a;
	a.Print();

	// 클랙스의 임시 객체(익명 객체)
	A();
	A().Print();

	return 0;
}