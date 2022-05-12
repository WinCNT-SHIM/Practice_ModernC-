#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>

using namespace std;

/// <summary>
/// noexcept
/// ���ܸ� �������� ���� �Լ��� noexcept�� ����ϴ� ���� ����
/// 
/// C+11���� throw()�� deprecated�ǰ�, noexcept Ű���尡 �߰��Ǿ���
/// noexcept Ű����� �������� ���¿� �������� ���·� �����ȴ�
/// </summary>

/// <summary>
/// ���ܰ� �߻��� ������ �ƴ����� �߿�����
/// � Ÿ������ ���ܰ� �߻��� �������� �߿����� �ʴ�
/// C++11������ �׷��� noexcept��� Ű���尡 �����
/// </summary>
int f(int x) throw(int, double);	// f�Լ��� ���ܸ� �������� ����(C++98)
// noexcept ������
int f_noexcept(int x) noexcept;				// f�� ���ܸ� �������� ����(C++11)

/// <summary>
/// C++11 ���� ��������, �Լ��� ���� ���� �ൿ�� ���� ������ �ǹ� �ִ�
/// �Լ��� ���ܸ� �ϳ��� ������, �ƴϸ� ����� ������ �ʴ�����
/// �� �Լ��� ���ܸ� �������� ���� ������ ����� ������ noexcept���
/// </summary>
int f2(int x) noexcept(true);	// ���� ���� ���ɼ� ����, int f(int x) noexcept�� ����
int f3(int x) noexcept(false);	// ���� ���� ���ɼ� ����

/// <summary>
/// noexcept�� ���ܰ� �߻����� ���� ���̶�� ��������� ������ ��
/// ������ ���� �߻��� ������������ �ʴ´�(...)
/// (���� ���ܰ� �߻����� ���� ���̶� �Ƚ��� ������ ����ϴ� ���� ����)
/// 
/// �׷� �� ����ϴ� ���ϱ�?
/// 
/// 
/// </summary>
void f() noexcept {}

/// <summary>
/// noexcept ������
/// �Լ��� noexcept���� �ƴ����� �Ǵ��ϴ� ������
/// 
/// ���ܰ� �߻��ϴ� �Լ��� ������ �̵��� �ϸ�
/// ���� �߻� �� ������ ������ �Ұ����ϴ�
/// �� ���� noexcept�� �Ǵ��ϰ� �̵����� �������� ���� �� �ִ�
/// </summary>
void f5() {}
void g5() noexcept {}

// ���ܸ� ������ �ʴ´�
void bar() noexcept {}
// ���ܸ� ������ �ʴ´ٰ� ����س��� ���ܸ� ����
void baz() noexcept { throw 55; }

/// <summary>
/// ���ø����� noexcept(noexcept(T))�� ���� ����
/// T() �����ڰ� ���ܸ� �������Ŀ� ���� noexcept(true), noexcept(false)�� ������
///   �⺻ throw�δ� �Ұ����� ó��
/// ������ noexcept(T)�� operator, �ٱ����� noexcept�� specifier�� ���Ǿ���
/// </summary>
template<typename T>
void foo() noexcept(noexcept(T)) {}

/// <summary>
/// �����Ϸ� ����ȭ�� �����ؼ�....
/// 
/// noexcept �Լ����� �����Ϸ��� ����ȭ��(optimizer)��
/// ���ܰ� �Լ� �ٱ����� ���ĵ� �� �ִٰ� �ص� ���� ���� ������ Ǯ�� ���� ���·� ������ �ʿ䰡 ����
/// ����, ���ܰ� noexcept �Լ��� ����ٰ� �ص� 
/// noexcept 
/// </summary>

/// <summary>
/// noexcept �Լ����� ���ܸ� ������ std::terminate
/// </summary>

/// <summary>
/// noexcept�� ���� ���Ǵ� ��
/// 1. �̵� ����
///   C++11�� �̵� ������ ���� ����ȭ�� �ϸ� push_back�� ������ ���� �������� ������ �� ���� �ȴ�.
///   �̵� ������ ���ܸ� �������� ������ Ȯ���� ��쿡�� ���縦 �̵����� ��ü�ص� �����ϴ�
///   std::vector::push_back ���� �Լ��� std::move_if_noexcept�� �����Ǿ� �ִ�
///   ��, �̵� ������ ������ �������� noexcept�� �����Ѵ�
/// 
/// 2. Swap �Լ���
///   Swap �Լ����� noexcept�� ���ؼ� ����ȭ�� ��ġ�� ũ��
///   ǥ�� ���̺귯���� �ִ� swap���� noexcept ���δ�
///   ����� ���� swap���� noexcept ���ο� ��� ���� �����Ѵ�
///   
/// 3. �޸� ���� �Լ���
///   noexcept�� �����ϴ� ���� ���� �߿��� �Ϻ� �Լ����� �⺻������ noexcept�� ����ȴ�
///   �⺻������ ��� �޸� ���� �Լ�(delete�� delete[] ������)�� ��� �Ҹ��ڴ� �Ϲ������� noexcept�̴�
/// </summary>

// Swap �Լ���
template<class T, size_t N>
void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b)));

template<class T1, class T2>
struct pair
{
	void swap(pair& p) noexcept(noexcept(swap(first, p.first)) && noexcept(swap(second, p.second)));
};

/// <summary>
/// strong exception guarantee
/// </summary>

struct foo5
{
	int value;

	explicit foo5(int value) : value(value)
	{
		cout << "foo5(" << value << ")" << endl;
	}

	foo5(foo5 const& other) : value(other.value)
	{
		cout << "foo5(foo5(" << value << "))" << endl;
	}

	foo5(foo5&& other) noexcept : value(move(other.value))
	{
		cout << "foo5(move(foo5(" << value << ")))" << endl;
	}

	~foo5()
	{
		if (value != -1)
			cout << "~foo5(" << value << ")" << endl;
	}

};

/// <summary>
/// move_if_noexcpet
/// �̵�, Ȥ�� ����� �� �ִ� X�� ���ڷ� �޾�
/// �̵� �����ڰ� noexcpet�� ��쿡�� �̵� �����ڸ� ��ȯ�ϰ�
/// �̵� �����ڰ� noexcpet�� �ƴ� ��쿡�� ���� �����ڸ� ��ȯ�Ѵ�
/// </summary>
struct Good
{
	Good() {}
	Good(Good&&) noexcept
	{
		cout << "Non-Throing move constructor called" << endl;
	}
	Good(const Good&)
	{
		cout << "Non-Throing copy constructor called" << endl;
	}
};

struct Bad
{
	Bad() {}
	Bad(Bad&&)
	{
		cout << "Throing move constructor called" << endl;
	}
	Bad(const Bad&)
	{
		cout << "Throing copy constructor called" << endl;
	}
};

/// <summary>
/// ���� �Լ����� �⺻������ noexcept�� ������
///   �Ͻ������� �����Ǵ� �⺻ ������, ���� ������, ���� ������, �̵� ������, �̵� ������, �Ҹ���
///   ������ ��������� noexcept(false)�� �����ϰų�, �θ��� �Ҹ��ڰ� �׷����� ���� ��츦 ������
///   ��� ���� ���� �Ҹ��� operator delete �Լ���(�Ҵ� ���� �Լ���)
/// 
/// �� �� �Ͻ������� �����Ǵ� ����/�̵� �����ڳ� ����/�̵� ������
/// 
/// �̵��� �����ڳ� �����ڰ� �⺻������ noexcept�� ���� �� �ִ�
/// </summary>
void may_throw();					//
void no_throw() noexcept;			//

auto lmay_throw = [] {};			// ����
auto lno_throw = []() noexcept {};	//

class T_class
{
public:
	// ������� �Ҹ��� �������� ���� �̵� ������, �̵� �������� �Ͻ��� ���� ����
	// ������ ���� ������, ���� �����ڴ� noexcept�� �Ͻ������� �����ȴ�
	~T_class() {};
};

class U_class
{
	vector<int> v;
public:
	~U_class() {};
};

class V_class
{
	vector<int> v;
};


int main()
{
	// noexcept ������
	cout << noexcept(f5()) << endl;	// false
	cout << noexcept(g5()) << endl;	// true

	bar();		// OK
	//baz();	// �������� ���� ������, ��Ÿ�ӿ� std::terminate�� ȣ��

	// noexcept(noexcept(T))�� noexcept(true)�� �ȴ�
	foo<int>();

	// strong exception guarantee
	vector<foo5> foo5s;
	foo5s.emplace_back(1);
	
	// �̶�, ������ (������)Ȯ���� ���� reserve�� �߻�
	// ���� foo5�� �̵� �����ڰ� noexcept�� �������� ������, ���� �����ڰ� �߻��Ѵ�
	// ��, reallocating �������� �̵��� �ƴ� ���簡 �߻��Ͽ� ���� �̵��� ���� ���ϰ� �ȴ�
	// (���⼭�� noexcept�� �����߱� ������ reallocating �������� ���� �߰��� 1�̶� ��Ұ� �̵� �����ڷ� �̵��ȴ�)
	foo5s.emplace_back(2);

	Good g;
	Bad b;
	// Good �̵� �����ڴ� ���ܸ� ������ �����Ƿ�, std::move(g)�� ��ȯ --> �̵� �����ڰ� ����ȴ�
	Good g2 = std::move_if_noexcept(g);
	// Bad �̵� �����ڴ� ���ܸ� ���� �� �����Ƿ� b�� ��ȯ --> ���� �����ڰ� ����ȴ�
	Bad b2 = std::move_if_noexcept(b);

	// �⺻������ noexcept ������ ���
	T_class t;
	U_class u;
	V_class v;

	cout << noexcept(std::declval<T_class>().~T_class()) << endl;	//
	cout << noexcept(T_class(std::declval<T_class>())) << endl;		//
	cout << noexcept(T_class(t)) << endl;							//
}