#include <iostream>
#include <vector>

int add(int x, int y) { return x + y; }
auto addRetAuto(int x, int y) { return x + y; } // C++ 18 ������ ��������

class Cat
{
	std::string name = "";
	int age = 0;
public:
	Cat(std::string s, int n) { name = 5; age = n; }
};

int main()
{
	/// <summary>
	/// C���� � ü��(���н�)�� ����� ���� ���� ���
	/// �ڷ����� � ü�� ���� ��, ���α׷����� �Ǽ��� �� �� �ֵ��� ����� �� ��
	/// �ڷ������� �����͵��� �����ϸ�, ������ ���� ������ ���׸� �̸� �ľ��� �� �ְ� �ǰ�
	/// ��������� ��Ÿ�� ������ ���� �� �ְ� �� ���̴�
	/// �׷��Ƿ� ���α׷����� ���� ��Ģ�� �ڷ����� ��Ȯ�ϰ� �ϴ� ���̶� �� �� �ִ�
	/// 
	/// �ݴ��, Ÿ���� ���� �ʿ䰡 ���� ��쿡�� auto�� ����Ͽ� ���꼺�� ���� �� �ִ�
	/// �Լ��� ���� ���� auto�� �ްų�(C++ 18���ʹ� ���Ͽ� auto ����� ��������),
	/// �� �ڷ����� ����ϰų�(std ��� �� ����) ���
	/// </summary>
	/// <returns></returns>
	long a = 0L;
	auto i = 1 + 2;

	auto i2 = 0.123;
	int size = sizeof(i2);
	std::cout << i2 << " " << size << std::endl;

	// auto�� ���ٰ� ���װ� �߻��ϴ� ��
	unsigned char x = 1;
	auto xAuto = x;					// ������ Ÿ�ӿ� �ڷ��� ����
	xAuto = 1.3;					// unsigned char�� 1.3�� �����ϰ� ����
	printf("%d %f \n", x, xAuto);	// 1 0.0000 --> unsigned char�� %f�� ��� ������ �ٸ��Ƿ� 0.000�� ���

	// return ���� auto�� ���� �� �ִ�
	auto sum = add(3, 5);

	// auto�� �����ͳ� ���� Ÿ���� ���� �� �ִ�(�ڵ尡 ��Ȯ����)
	Cat* myCat = new Cat("CoCo", 2);
	auto* myCatPtr = myCat;
	auto& myCatRef = myCat;

	// ���������� auto���� const ���� ���� �� �ִ�(�ڵ尡 ��Ȯ����)
	const int b = 1;
	const auto& a1 = b;

	// std ��� �� auto�� ����ϸ� ���ϴ�(Ư�� iterator)
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	//for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {}
	for (auto it = v.begin(); it != v.end(); ++it){ }

	// ���ø��� ����� Ŭ���� � auto�� ����ϸ� ����� �� �ִ�
	// MyArr<int>* a = new MyArr<int>(10);
	// auto* a = new MyArr<int>(10);

	// �Լ� ������
	// �Լ� �̸��� (*�Լ���)���� �����ϸ� ��
	// int (*funcPtr)(int, int);
	// �Լ� �������� ������ �����ϱ⿡ auto�� ����ϸ� ���ϴ�
	auto fp = add;
	auto result = fp(1, 2);
}