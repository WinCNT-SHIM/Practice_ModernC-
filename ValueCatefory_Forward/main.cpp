#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// ���� ����
/// auto&&
///		
/// </summary>
/// <returns></returns>

class A {};

void g(A& a) { cout << "���� �� ���۷��� ȣ��" << endl; }
void g(const A& a) { cout << "���� ��� �� ���۷��� ȣ��" << endl; }
void g(A&& a) { cout << "���� �� ���۷��� ȣ��" << endl; }

template <typename T>
void wrapper(T&& u)		// T&&�� ���� ����, u��ü�� �����̹Ƿ� lValue
{
	// u��ü�� ����(lValue)�̹Ƿ� ���� �� ���۷���, Ȥ�� ���� ��� �� ���۷��� �ۿ� ȣ����� �ʴ´�
	// ��, ���ø��� �ǹ̰� ��������
	g(u);

	// �Ű� ������ u��ü�� ����(lValue)������, std::forward �Լ���
	// ������ �μ��� ���� ���� ���� &, ���� ���� ���� &&�� �״�� ������
	// ������ �μ��� lValue���� rValue���� �� �� �������
	g(forward<T>(u));
}

int main()
{
	const int i = 10;
	
	auto& var = i;
	
	// ���� ����
	// auto&&�� �ڵ����� lValue, rValue�� �߷�����
	//int&& var2 = i;	// lValue�� �����Ϸ��� ������ ������ ����(���� ������ �ƴ�)
	auto&& var2 = i;	// const int&�� ��������
	auto&& var3 = 12;	// int&&�� ����

	// const auto&&�� ���� ������ �ƴϹǷ� ������ ���� �߻�
	//const auto&& var4 = i;
}