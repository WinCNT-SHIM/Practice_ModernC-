#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// ������ ����, ������ ���۷���(Universal Reference)
/// auto&&�� ����� �� �ִ�
/// �����Ϸ��� lValue���� rValue���� �˾Ƽ� �������ش�
/// ������ ���� �� �����ϴ�
/// 
/// forward(): rValue�� �� move(rValue)�� �ٲ��ش�
/// 
/// </summary>
/// <returns></returns>

class A
{
};

void foo(A& a)			{ cout << "���� �� ���۷��� ȣ��" << endl; }
void foo(const A& a)	{ cout << "���� ��� �� ���۷��� ȣ��" << endl; }
void foo(A&& a)			{ cout << "���� �� ���۷��� ȣ��" << endl; }

// ���� �Լ����� ���ø����� ������!!
template <typename T>
void wrapper(T&& u)		// T&&�� ���� ����(auto&&)�� ����
{
	// u��ü�� lValue�̹Ƿ� �μ��� rValue�� �ִ���
	// foo(A& a), foo(const A& a) �ۿ� ȣ������ �ʴ´�
	// ��, ���ø��� �ǹ̰� ��������
	//foo(u);

	// �Ű� ������ u��ü�� ����(lValue)������, std::forward �Լ���
	// ������ �μ��� lValue�� ���� lValue �״�� �����ϹǷ� foo(A& a)�� foo(const A& a)�� ȣ��,
	// ������ �μ��� rValue�� ���� u�� rValue�� ĳ���� �����ϹǷ� foo(A&& a)�� ȣ���Ѵ�
	// ������ �μ��� lValue���� rValue���� �� �� �������
	foo(forward<T>(u));
}

int main()
{
	const int i = 10;
	auto& var = i;
	
	// ���� ����
	// auto&&�� �ڵ����� lValue, rValue�� �߷�����
	auto&& var2 = i;	// const int&�� ��������
	auto&& var3 = 12;	// int&&�� ����

	// rValue ������ lValue�� �����ϸ� ������ ����(���� ������ �ƴ�)
	//int&& var2 = i;
	// const auto&&�� lValue�� �����ϸ� ������ ���� �߻�(���� ������ �ƴ�)
	//const auto&& var4 = i;

	// ==================== ====================
	A a;
	const A cA;

	// ����
	cout << "����" << endl;
	foo(a);
	foo(cA);
	foo(A());

	// Wrapper
	cout << "Wrapper" << endl;
	wrapper(a);
	wrapper(cA);
	wrapper(A());
}