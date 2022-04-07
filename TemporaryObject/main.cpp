#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// �ӽ� ��ü, �Ǵ� �͸� ��ü(Temporary Object)
///		�͸� ��ü�� R-Valueó�� �۵��Ѵ�
///		���� �͸� ��ü�� �����ǰ� ����� ȣ���� �� ������ �����ڸ��� �ٷ� �������
///		�͸� ��ü�� Move ���� ����ϸ� ȿ�����̴�
/// </summary>

class A
{
public:
	void Print() { cout << "Hello, World!" << endl; }
};


int main()
{
	// �Ϲ����� ��ü
	int n = 1;
	// �Ʒ��� n = 1;�� ����
	int n2(1);
	int n3{ 1 };

	// �ӽ� ��ü(�͸� ��ü)
	int(1);		// 1�̶�� ���� �Ҵ�� �̸� ���� ��ü

	// �Ϲ����� Ŭ������ ��ü
	A a;
	a.Print();

	// Ŭ������ �ӽ� ��ü(�͸� ��ü)
	A();
	A().Print();

	return 0;
}