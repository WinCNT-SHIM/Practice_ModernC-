#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>
#include <algorithm> //for_each

#include <functional>

using namespace std;

/// <summary>
/// Callable�̶�
///   �̸� �״�� ȣ��(Call)�� �� �ִ� ��� ��(�Լ�, �Լ� ��ü, ����)
/// std::function
///   Callable���� ��ü�� ���·� ������ �� �ִ� Ŭ����
///   �Լ��� �Ű������� ���� �ްų� ����, �׸��� ������ �� ��
/// </summary>
/// <returns></returns>

int some_func1(const string& a)
{
	cout << "Func1 ȣ��! " << a << endl;
	return 0;
}

struct S
{
	void operator() (char c) { cout << "Func2 ȣ��!" << endl; }
};

class A
{
	int c;
public:
	A(int c) : c(c) {}
	int some_func()
	{
		cout << "���� �Լ� : " << ++c << endl;
		return c;
	}
	int some_const_func() const
	{
		cout << "��� �Լ� : " << c << endl;
		return c;	//return this->c;
	}
	static void st() {}
};

// �ݸ� --> ȣ���ϴ� ����
int callback_func(function<void(string)> fn);

struct Widget
{
	function<void(string)> fn;

	int ClickYes()
	{
		fn("yes");	// 2. �ݹ� ȣ��
		return 0;
	}
	int ClickNo()
	{
		fn("no");	// 2. �ݹ� ȣ��
		return 0;
	}
};

int main()
{
	// �Լ�
	function<int(const string&)> f1 = some_func1;
	// �Լ� ��ü
	function<void(char)> f2 = S();
	// ����
	function<void()> f3 = []() {cout << "Func3 ȣ��!" << endl; };

	f1("hello");
	f2('c');
	f3();

	A a(5);

	/// <summary>
	/// Ŭ������ ��� �Լ����� ���
	///   �Ͻ��� ��ȯ�� �߻����� �����Ǹ�,
	///   & �����ڸ� ���� ��������� �ּҰ��� ��������� �Ѵ�
	/// </summary>
	function<int(A&)> f_a_1 = &A::some_func;
	function<int(const A&)> f_a_2 = &A::some_const_func;	// const Ÿ��

	f_a_1(a);
	f_a_2(a);

	// �ݷ� --> �Լ��� �����ϴ� ����
	// 1. ���� ����
	//callback_func(
	//	[](string s) -> void
	//	{
	//		if (s == "yes") cout << "yes" << endl;;	// 3. ����� ���� ó��
	//		if (s == "no") cout << "no" << endl;;
	//	}
	//);
	
	Widget widget;
	// �ݷ� --> �Լ��� �����ϴ� ����
	// �̷��� ���� ó���� �̸� ������ ��
	widget.fn = [](string s) -> void
	{
		if (s == "yes") cout << "yes" << endl;;	// 3. ����� ���� ó��
		if (s == "no") cout << "no" << endl;;
	};
	
	cout << "========== �ٸ� ó�� �� ==========" << endl;

	// �̸� �����ص� ó���� �����ؼ� ó����
	widget.ClickYes();
	widget.ClickNo();

	return 0;
}
