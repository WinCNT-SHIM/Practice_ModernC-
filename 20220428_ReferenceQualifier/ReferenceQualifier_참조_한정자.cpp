#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

/// <summary>
/// ��� �Լ� ���� ������ (Reference Qualifier)
///   this �Լ� ���� �����ڸ� �����Ͽ�,
///   �Ͻ��� ��ü �Ű������� L-Value���� R-Value������ ����,
///   ������ ����Լ��� �����ε� �� �� �ִ�
/// </summary>

struct MyStruct
{
	void func()& { cout << "L-Value" << endl; }
	void func() && { cout << "R-Value" << endl; }
	void func() const& { cout << "const L-Value" << endl; }
};

// ������ �����ε������� ��� ����
template <typename T>
class A
{
public:
	A() {}
	~A() {}

	T const& operator*() const& { T _tmp; return _tmp; }
	T& operator*()& { T _tmp; return _tmp; }
	T&& operator*() const&& { T _tmp; return move(_tmp); }
};

int main(void)
{
	MyStruct s;
	s.func();				// L-Value

	MyStruct().func();		// R-Value, �ӽ� ��ü�̹Ƿ� R-Value

	std::move(s).func();	// R-Value, �̵��̹Ƿ� R-Value

	const MyStruct s2;
	s2.func();				// const L-Value


	// ������ �����ε������� ��� ����
	cout << "������ �����ε������� ��� ����" << endl;
	// const&�� �����ε尡 const, non - const �� L-Value ��ü���� ���ȴٴ� ���� �ǹ��Ѵ�
	const A<int> a1 = A<int>();
	*a1;

	// &�� �����ε尡 ����� �ƴ� ��ü���� ���ȴٴ� ���� �ǹ��Ѵ�
	A<int> a2;
	*a2;

	// &&�� R-Value ��ü���� ���ȴٴ� ���� �ǹ��Ѵ�
	*A<int>();

	return 0;
}