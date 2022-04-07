#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

/// <summary>
/// Copy Elision(���� ����) - C++11
///   �����Ϸ��� ����/�̵� �����ڸ� ȸ���� �� ������ ȸ���ϴ� ���� ����ϴ� ���
///   Return Value Optimization(RVO) / Named Return Value Optimization(NRVO)
///   Passing Temporary as Value
///   ����) �����Ϸ��� ���� ���� ���ΰ� �ٸ� �� ����
/// </summary>

/// <summary>
/// 1) Return Value Optimization(RVO) / Named Return Value Optimization(NRVO)
///   RVO / NRVO�� �Լ��� ��ȯ ���� Ư�� ��ü�� �� ������ ��
///   ���� ������ ȸ���� �� �ֵ��� �����Ϸ� ����ȭ�� �ǹ��Ѵ�
/// 
///   ����� NRVO�� ����ȭ �ɼ� /O1���� �۵���
///   RVO�� �ֱ��� ��� �����Ϸ��� �������ش�
///   (NRVO�� �����Ϸ����� ���� ���ΰ� �ٸ�)
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
	// �Ʒ��� ���Թ����� ���� ������ ���� (Release ��忡�� Ȯ��)
	{
		Foo rvo_foo = RVO_F();
	}
	return 0;
}