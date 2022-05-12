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

int main()
{
	// noexcept ������
	cout << noexcept(f5()) << endl;	// false
	cout << noexcept(g5()) << endl;	// true

	bar();		// OK
	//baz();	// �������� ���� ������, ��Ÿ�ӿ� std::terminate�� ȣ��

	// noexcept(noexcept(T))�� noexcept(true)�� �ȴ�
	foo<int>();

	vector<foo5> foo5s;
	foo5s.emplace_back(1);
	
	// �̶�, ������ (������)Ȯ���� ���� reserve�� �߻�
	// ���� foo5�� �̵� �����ڰ� noexcept�� �������� ������, ���� �����ڰ� �߻��Ѵ�
	// ��, reallocating �������� �̵��� �ƴ� ���簡 �߻��Ͽ� ���� �̵��� ���� ���ϰ� �ȴ�
	foo5s.emplace_back(2);
}