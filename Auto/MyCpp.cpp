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
	long a = 0L;
	auto i = 1 + 2;

	auto i2 = 0.123;
	int size = sizeof(i2);
	std::cout << i2 << " " << size << std::endl;

	// auto�� ���ٰ� ���װ� �߻��ϴ� ��
	unsigned char ucx = 1;
	auto xAuto = ucx;					// ������ Ÿ�ӿ� �ڷ��� ����
	xAuto = 1.3;					// unsigned char�� 1.3�� �����ϰ� ����
	printf("%d %f \n", ucx, xAuto);	// 1 0.0000 --> unsigned char�� %f�� ��� ������ �ٸ��Ƿ� 0.000�� ���

	// return ���� auto�� ���� �� �ִ�
	auto sum = add(3, 5);

	// auto�� �����ͳ� ���� Ÿ���� ���� �� �ִ�(�ڵ尡 ��Ȯ����)
	Cat* myCat = new Cat("CoCo", 2);
	auto* myCatPtr = myCat;
	auto& myCatRef = myCat;

	// ���������� auto���� const�� ���� �� �ִ�(�ڵ尡 ��Ȯ����)
	const int b = 1;
	auto a1 = b;			// a1�� int
	const auto a2 = b;		// a2�� const int 
	auto& a3 = b;			// a3�� const int&
	const auto& a4 = b;		// a4�� const int&

	// volatile ���� Ű���嵵 ���������̴�
	volatile int vx = 1024;
	auto avx = vx;				// int
	volatile auto vavx = vx;	// volatile int

	int x = int();
	auto auto_x = x;

	const int& crx = x;
	auto auto_crx1 = crx;
	const auto& auto_crx2 = crx;


	// std ��� �� auto�� ����ϸ� ���ϴ�(Ư�� iterator)
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	//for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {}
	for (auto it = v.begin(); it != v.end(); ++it){ }

	// ���ø��� ����� Ŭ���� � auto�� ����ϸ� ����� �� �ִ�
	// MyArr<int>* a = new MyArr<int>(10);
	// auto* a = new MyArr<int>(10);

	// �Լ� ������
	// �Լ� �̸��� (*�Լ���)���� �����ϸ� ��
	// ������ ������ �Լ� �����Ϳ� auto�� ����ϸ� ���� ������ �� �ִ�
	//int (*funcPtr)(int, int) = add;
	auto funcPtr = add;
	auto result = funcPtr(1, 2);


	int aaa = 1;
	int aaa(1);	// �Լ� ����� �ʹ� �򰥸���
	int aaa{ 1 }; // �߰�ȣ �ʱ�ȭ

	int b(a); // int b = a;

	int(10); // �ӽ� ��ü, ���� �������� �Լ� ���� ����� �� --> �������� ���� int�� 10
	
	int c = 1 + 2; // 1 + 2�� ���� 3�� ��򰡿� �����ϴ� �Ͱ� ����
	// �̵� ������
	// ���� �������� ��� 1�Ⱑ + 2�Ⱑ�� �ӽ� ��ü�� ������ 3�Ⱑ��
	// �װ��� ������ ������ 3�Ⱑ, ���� 6�Ⱑ�� �ʿ��ϴ�
	// ������ 1�Ⱑ + 2�Ⱑ = 3�Ⱑ�� �ٷ� �������� ���̸� ����� �ξ� ���� �� �ִ�

}