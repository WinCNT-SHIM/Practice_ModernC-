#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// ���ø� Ÿ�� �߷� ��Ģ
/// 
/// T�� param�� Type ���� ��ΰ� &&�� ���� &&(R-Value ����)
/// OR �����̶�� �����ϸ� ����
/// 
/// typedef int& T;
///   T&	r1;		// T: int&	|| Type: &		--> r1�� int&
///   T&&	r2;		// T: int&	|| Type: &&		--> r2�� int&
/// 
/// typedef int&& U;
///   U&	r3;		// U: int&&	|| Type: &		--> r3�� int&
///   U&&	r4;		// U: int&&	|| Type: &&		--> r4�� int&&
/// </summary>


template<typename T>		// T
void foo(const T& param)	// const &T, ParamType�� �ٸ� 
{
	// T, param�� Ÿ����??
}

/// <summary>
/// Case1
///   param�� Ÿ���� �����Ͱ� �ƴϰ� ������ �ƴ� ���
///   param�� �־��� �μ��� ���纻, �� ������ ���ο� ��ü�̴�
///   
///   expr(ǥ����, ���⼭�� �μ�)�� Ÿ���� �����̸�, ���� �κ��� �����Ѵ�
///   expr�� const�̸� �� const ���� �����Ѵ�
///   volatile�̸� �װ͵� �����Ѵ�
/// 
///   ��, T�� auto�� ����ϰ� �����Ѵ�
/// </summary>
template<typename T>	// T
void fooCase1(T param)	// const, &�� ���� ������ "const T& param"���� ����
{
}

/// <summary>
/// Case2
///   param�� Type�� ������ �Ǵ� ���� Ÿ��(T&)������ ���� ����(Universal Reference)�� �ƴ� ���
///   ���� expr�� ���� Ÿ��(&)�̸� ���� �κ��� �����Ѵ�
///   (�� &�� �����ϰ� const�� �״�� ����)
/// </summary>
template<typename T>
void fooCase2(T& param)
{
}

/// <summary>
/// Case3
///   param�� Type�� ���� ����(Universal Reference)�� ���
///   ���� ������ �����ϸ� L-Value �μ��� R-Value �μ��� ���ؼ� ���� �ٸ� �߷� ��Ģ���� ����ȴ�
///   ���� expr�� L-Value��, ��������(�� Case2��) ��Ģ�� ����
///   ���� expr�� R-Value��, T�� &&�� �����ϰ�, param�� Type�� R-Value ������ �߷�
///   (T�� &&�� �����ϴ� ������ param�� Type�� &&�� ���̱� ���ؼ�)
///   ���� ������ �ƴ� �Ű������鿡 ���ؼ��� �׷��� ���� ���� �߻����� �ʴ´�
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
	foo(x);				// T --> int, param�� Type --> const int&
	foo(cx);
	foo(rx);

	// ==================== Case1 ====================
	fooCase1(x);		// T --> int		|| param�� Type --> int
	fooCase1(cx);		// T --> int		|| param�� Type --> int
	fooCase1(rx);		// T --> int		|| param�� Type --> int
	fooCase1(11);		// T --> int		|| param�� Type --> int

	// ==================== Case2 ====================
	fooCase2(x);		// T --> int		|| param�� Type --> int&
	fooCase2(cx);		// T --> const int	|| param�� Type --> const int&
	fooCase2(rx);		// T --> const int	|| param�� Type --> const int&
	//fooCase2(11);		// L-Value�� param�� R-Value�� �����ϴ� ���̶� ������ ���� 

	// ==================== Case3 ====================
	fooCase3(x);		// T --> int		|| param�� Type --> int&
	fooCase3(cx);		// T --> const int&	|| param�� Type --> const int&
	fooCase3(rx);		// T --> const int&	|| param�� Type --> const int&
	fooCase3(11);		// T --> int		|| param�� Type --> int&&

	// ==================== Case4 ====================
	// "abc" ��ü�� const char*(��Ȯ���� char[])
	const char* const ptr = "abc";	// prt�� const ��ü�� ����Ű�� const ������
	fooCase4(ptr);					// const char* const Ÿ���� �μ��� ����

	const char name[] = "abc";		// name�� �迭
	fooCase4(name);					// T�� param�� Type ��� const char*

	int arr[3] = { 1, 2, 3 };
	int* ptr1 = arr;
	int(*ptr2)[3] = &arr;

	cout << ptr1 << ", " << ptr1 + 1 << endl;
	cout << ptr1 << ", " << ptr2 + 1 << endl;

	return 0;
}