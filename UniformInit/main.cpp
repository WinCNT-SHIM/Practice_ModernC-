#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
//using namespace std::literals;

/// <summary>
/// ������ �ʱ�ȭ(Uniform initialization)
/// ������ �ʱ�ȭ, �߰�ȣ �ʱ�ȭ��� �Ѵ�
///   ���� ���, ��ȯ(�Ͻ��� ĳ���� ��)�� �߻����� �ʴ´�
///   �Լ��� ��ü ������ ������ �򰥸��� ��츦 �����Ѵ�
/// 
/// 
/// 
/// </summary>

/// <summary>
/// �ʱ�ȭ�� ����Ʈ(Initiaslizer List)
///   ��) A a_IL = { 1, 2, 3, 4, 5 };
///
///   auto�� ���ø��� ����� ������ ��������!
/// </summary>
class A
{
public:
	A() { cout << "A�� ������ ȣ��!!" << endl; }

	// ====================�ʱ�ȭ�� ����Ʈ(Initiaslizer List) Ȱ�� ====================
	A(std::initializer_list<int> il)
	{
		cout << "A�� ������(initializer_list) ȣ��!!" << endl;

		for (auto itr = il.begin(); itr != il.end(); ++itr)
		{
			cout << *itr << endl;
		}
	}
};

class B
{
public:
	B(A a) { cout << "B�� ������ ȣ��!!" << endl; }
};


//template<typename T>
//void foo(T param) {}		// std::initializer_list�� �߷����� �� ��
template<typename T>
void foo(std::initializer_list<T> param) {}

auto CreateInitList(void)
{
	//return { 1, 2, 3 };		// ����! { 1, 2, 3 }�� Ÿ���� �߷��� �� ����!
	auto a = { 1, 2, 3 };
	return a;
}

struct T
{
	int i;
	string v;
	bool b;
};

class Widget
{
public:
	Widget(int i) {}
	Widget(double d) {}
	//Widget(std::initializer_list<double> il) {}
};

int main()
{
	// �Ϲ����� �ʱ�ȭ
	int value1 = 5;
	// ����(C++������ ��ü�⵵ ��)�� �ʱ�ȭ, �Լ��� �򰥸��ٴ� ������ �ִ�
	int value2(5);
	// C++ 11�� ������ �ʱ�ȭ(������ �ʱ�ȭ, �߰�ȣ �ʱ�ȭ)
	int value3{ 5 };
	// Default Initailization to 0
	int value4{};

	// ==================== ���� ���, ��ȯ(ĳ���� ��)�� �߻����� �ʴ´� ====================
	int v1(5.1);
	cout << v1 << endl;			// <-- �ڵ����� ĳ���� ��

	//int v2{ 5.1 };	// <-- ������ ����
	double v2{ 5.1 };
	int v3{ static_cast<int>(v2) };
	cout << v3 << endl;


	// ====================
	// A a; A a();
	// ���� ��µɱ�? A()�� �Լ�? �ƴϸ� ��ü?
	B tmpB(A()); // --> �ƹ��͵� ��� �� ��

	// ���� ���� ��Ȳ�� �����ϱ� ���ؼ� �߰�ȣ �ʱ�ȭ�� ����Ѵ�
	B b{ A{} }; // --> �����ڰ� ����� ��µ�


	cout << "\n==================== �ʱ�ȭ�� ����Ʈ(Initiaslizer List) ====================" << endl;
	int arr[] = { 1, 2, 3, 4, 5 };
	vector<int> v = { 1, 2, 3, 4, 5 };
	map<string, int> m =
	{
		{"abc" , 1}, {"def", 2}
	};

	// �߰�ȣ �ʱ�ȭ�� �ʱ�ȭ�Ϸ��� �ϸ�
	// �������� �μ��� std::Initiaslizer_List�� �ִ��� ���� Ȯ���Ѵ�
	A a_IL = { 1, 2, 3, 4, 5 };


	// ==================== �ʱ�ȭ�� ����Ʈ�� auto ��� ���� ������ ====================
	auto a_auto = 1;				// auto --> int
	auto b_auto{ 1 };				// auto --> int // auto b_auto = 1;�� ����
	auto c_auto = { 1, 2 };			// auto --> std::initializer_list<int>
	//auto d_auto{ 1, 2 };			// ������ ����! // auto d_auto = 1, 2;�� ����!!
	//auto e_auto = { 1, 2, 3.0f };	// ������ ����! auto�� �߷��� �� ����!!

	auto list_1 = { "a", "b" };		// auto --> std::initializer_list<const char*>
	// �ڿ� s�� ���̸� string���� �ٲ� �� �ִ�(using namespace std::literals�� �ʿ�?�Ѱ�?)
	auto list = { "a"s, "b"s };		// auto --> std::initializer_list<std::string>


	// ==================== �ʱ�ȭ�� ����Ʈ�� ���ø� ��� ���� ������ ====================
	// �ʱ�ȭ�� ����Ʈ�� auto�ʹ� �ٸ��� ���ø����� �߷��� ���� �����Ƿ�
	// std::initializer_list<T>�� ���� ��������� �ۼ��ؾ� �Ѵ�
	// ����) void foo(std::initializer_list<T> param);
	foo({ "a"s, "b"s });


	// ==================== �ʱ�ȭ�� ����Ʈ�� ������ ====================
	// vector�� ��� ������ �ʱ�ȭ�� �ٸ���!
	vector<int> v_tmp1(10, 20);		// ���: 10��, ��� 20
	vector<int> v_tmp1{ 10, 20 };	// ���: 2��, 10�� 20


	// �������� �з����ͷ� �ʱ�ȭ�� ����Ʈ�� �ִ� ���
	// �ʱ�ȭ�� ����Ʈ�� �켱���� Ȯ���ϰ�,
	// �ʱ�ȭ�� ����Ʈ�� ������ �� �ִ� Ÿ���̸� �ش� �����ڰ� ȣ��Ǹ�
	// �ƴ� ���� �ٸ� �����ڸ� ã�´�
	T t{ 1, "acb", true };


}