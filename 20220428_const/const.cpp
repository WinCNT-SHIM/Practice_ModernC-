#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <array>

using namespace std;

/// <summary>
/// constexpr
///   ��ü�� �Լ� �տ� ���� �� �ִ� Ű�����,
///   �ش� ��ü�� �Լ��� ���� ���� "������ Ÿ��"�� ���� �� �� �ִٴ� �ǹ�
///   ���� ��� ǥ����(Integral Constant Expression)�� �䱸�Ǵ� ���ƿ��� ����� �� �ִ�
///   ��ü�� ���ǿ� constexpr�� ���� �ȴٸ�, �ش� ��ü�� ��� ����Ŀ��� ���� �� ����
/// 
/// ��� ǥ����, ���� �����
///   1. �迭�� �����ϴ� ���
///   2. ���ø� Ÿ�� ����
///   3. enum���� ���� ����
/// 
/// constexpr �Լ�
///   constexpr�� �Լ��� ���� �� �ִٸ� ���̴� ���� ����
///   �ֳ��ϸ� constexpró�� �������� ���Ѵٸ� �׳� �Ϲ� �Լ� ó�� �۵��ϰ�,
///   ������ Ÿ�� ����� ������ �� �ִ� ��Ȳ�̶�� ������ �̿��� �� �ֱ� ����
/// 
/// constexpr ������(C++14)
///   C++14���� constexpr �����ڸ� ���������ν�,
///   ������� ���ͷ� Ÿ�Ե��� ���� ���� �� �ְ� �Ǿ���
///   ���ͷ� Ÿ���� ���� �����ϸ� �����Ϸ��� ������ Ÿ�ӿ� ������ �� �ִ� Ÿ���� �ǹ�
///     constexpr �Լ��� �ݵ�� ���ͷ� Ÿ�Ե��� �ް� ������� �Ѵ�
///     constexpr �����ڴ� �ݵ�� ���ͷ� Ÿ���̿��߸� �ϰ�,
///     �ش� Ŭ������ �ٸ� Ŭ������ ���� ��� ���� �� ����
/// 
/// if constexpr
///   ������ Ÿ�ӿ� ��� ǥ������ boolean(true/false)�� ���Ѵ�
///   if constexpr�� ������ �ݵ�� bool�� Ÿ�� ��ȯ�� �� �־�� �ϴ� ������ Ÿ�� ������̾�߸� �Ѵ�
///   ���ø� Ư��ȭ ���� ���� �ʰ� �б� ó���� ���� ǥ�� ��������
/// 
/// </summary>

int get_int()
{
	return 1;
}

class A
{
public:
	// v ���� ��ȭ�� ���� ���� const�� ������
	void SetVector(const vector<int>& v) {}
	// v ���� ��ȭ�� ���� ���� const�� ������
	void PrintVec() const {}
	const string& GetNameRef() { return name; }
private:
	string name;
	vector<int> m_v;
};

template<int N>
struct  AA
{
	int operator()() { return N; }
};

constexpr int Factorial(int n)
{
	int total = 1;
	for (int i = 1; i <=n; i++)
	{
		total *= i;
	}
	return total;
}

/// constexpr ������(C++14)
class Vector
{
public:
	constexpr Vector(int x, int y) : x_(x), y_(y) {}
	constexpr int x() const { return x_; }
	constexpr int y() const { return y_; }

private:
	int x_;
	int y_;
};

/// constexpr ������(C++14)
constexpr Vector AddVec(const Vector& v1, const Vector& v2)
{
	return { v1.x() + v2.x(), v1.y() + v2.y() };
}

/// if constexpr
#include <type_traits>
template <typename T>
void show_value(T t)
{
	if constexpr (is_pointer<T>::value)
	{
		cout << "�������̴�" << endl;
	}
	else
	{
		cout << "�����Ͱ� �ƴϴ�" << endl;
	}

}

// if constexpr�� ������ �Ʒ��� ���� �ۼ��ؾ� ��
// Ÿ�� ������ �����ϸ� ���� �߻��� �ƴ϶� ��ŵ�Ǳ� ������ �ǻ� if������ ����ߴ�
template<typename T, enable_if_t < is_pointer<T>{} > * = nullptr >
auto get_value(T t)
{
	return *t;
}
template<typename T, enable_if_t < !is_pointer<T>{} > * = nullptr >
auto get_value(T t)
{
	return t;
}

int main(void)
{
	// �����Ϸ��� ����ȭ
	const int a = 0;
	// ���� �Ҵ� ����, ���� ������ Ÿ�ӿ� �������ٴ� ���� ����
	const int b = a;

	// ������ Ÿ�ӿ� ����� �����Ǵ� ���� �ƴ϶�
	// ��Ÿ������ �޾ƿ� ���� ������ ���̶�� �� �� �ִ�
	// ���� ���ø����� ����� �� ����
	const int c = get_int();			// ������

	// constexpr ������ Ÿ�ӿ��� ����� �� �� Ȯ���� ���� ����
	constexpr int a2 = 0;
	constexpr int b2 = a2;
	// get_int()�� ��Ÿ�ӿ� Ȯ���ǹǷ� constexpr�� ������ ������ �߻��Ѵ�
	//constexpr int c2 = get_int();		// ������ ����


	// ==================== const vs constexpr ====================
	// 1. �迭�� �����ϴ� ���
	int sz = 10;
	const auto arraySize1 = sz;
	//array<int, arraySize1> data1;	// ������ ����

	constexpr auto arraySize2 = 10;	// OK, 10�� Ȯ���� ������ �������� ���
	array<int, arraySize2> data2;

	// 2. ���ø� Ÿ�� ����
	constexpr auto N = 10;
	AA<N> a_ex;

	// ==================== constexpr �Լ� ====================
	// Factorial(5)�� constexpr
	AA<Factorial(5)> a3;
	cout << a3() << endl;

	// �Ϲ� �Լ�ó�� ����
	int n;
	cin >> n;
	cout << Factorial(n) << endl;

	// ==================== constexpr ������ ====================
	constexpr Vector v1{ 1, 2 };
	constexpr Vector v2{ 2, 3 };

	// constexpr ��ü�� constexpr ��� �Լ��� ���� constexpr!
	AA<v1.x()> aa1;
	cout << aa1() << endl;

	// AddVec ���� constexpr�� �����Ѵ�
	AA<AddVec(v1, v2).x()> AAb1;
	cout << AAb1() << endl;


	// ==================== if constexpr ====================
	cout << endl;
	cout << "if constexpr" << endl;
	int x = 3;
	show_value(x);
	int* p = &x;
	show_value(p);


	return 0;
}