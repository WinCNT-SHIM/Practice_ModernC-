#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// ���� �����ڿ� ���� ���� �����
///		T(const T& p);
/// 
/// ���� �����ڰ� ���Ǵ� ���
/// 1. ��ü�� ���� �� �ʱ�ȭ: A a(b);
/// 2. ��ü�� ���� ���� ����: 
/// 3. ��ü�� ���� ���� ��ȯ: A F() {  }
/// 
/// 
/// �̵� ������
///		T(T&& a) [noexcept];
///		�̵� �����ڴ� ȣ��Ǹ� ���� ����(shallow copy)�� �ϰ� ������ �������� ������� ����(move)�ϰ�
///		���� ��ü�� nullptr�� �ʱ�ȭ�Ͽ� ������ �� ���� �����
///		(���߿� delete ó���� �� �ص� ��)
///		�̵� �����ڿ� ���� �����ڸ� ��� �����ϸ�, �ڵ� ��Ȳ�� ���� ���� Ȥ�� �̵��� �ȴ�
/// 
/// ����) noexcept
///		�̵� �����ڴ� �ּҰ� �������� ������ �ּ� ���� ���߿� ���ܸ� �߻���Ű��
///		������ �Ұ����ϰ� �ǹǷ�, ������ �����
/// 
/// �̵� �������� ȣ�� ����
///		1. �ӽ� ��ü�� ������ ��
///		2. std::move()�� ����Ͽ� ���ڸ� rValue �����ڷ� ��ȯ�Ͽ� ������ ��
/// 
/// �̵� ������ �� �̵� �Ҵ� �����ڸ� �ۼ��ϸ�,
///		���� ����, �޸� �Ҵ� �� �޸� �Ҵ� ��� �۾��� �����ϱ� ������ ȿ�����̴�
/// 
/// Ŭ������ ������ ��,
///		���� �����ڸ� �� ����� �̵� �����ڸ� ���� ���� ������, �� �ݴ뵵 �����ϴ�
/// 
/// ����) explicit
///		
/// </summary>
/// <returns></returns>

class A
{
public:
	A()				{ cout << "�Ϲ� ������ ȣ��!" << endl; }
	A(const A& a)	{ cout << "���� ������ ȣ��!" << endl; }
	A(A&& a)		{ cout << "�̵� ������ ȣ��!" << endl; }

	A& operator=(const A& rhs)
	{
		if (this != &rhs)
		{
			cout << "���� ���� ������" << endl;
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