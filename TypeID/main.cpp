#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T1, typename T2>
void ex_func(T1 lvar, T2 rvar)
{
	// ��� 1: auto
	auto prod1 = lvar * rvar;	// Ÿ�� T1, T2�� ���� �Ŀ� �����ǹǷ� auto�� ���߿� �߷�

	// ��� 2: typedef
	typedef decltype(lvar* rvar) product_type;	// not ���! only �߷�!
	product_type prod2 = lvar * rvar;

	// ��� 3: decltype
	decltype(lvar * rvar) prod3 = lvar * rvar;	// ������ �ܰ迡�� decltype �߷�
}

struct A
{
	double d;
};

int main()
{
	int ex_a = 0;
	int& ex_b = a;
	const int& ex_c = 0;

	// auto�� ���������� const, �������� �����Ѵ�
	cout << typeid(ex_a).name() << endl;	// int
	cout << typeid(ex_b).name() << endl;	// int
	cout << typeid(ex_c).name() << endl;	// int

	// ���� ���� ������ �ذ��ϱ� ���� Ű���尡 decltype
	// ������ �ܰ迡�� Ÿ���� �����Ѵ�
	// ���� ������ �ܰ迡�� Ÿ���� �����Ǵ� ���ø� ���ο��� �ַ� ���ȴ�
	const int& ex_d = 0;
	decltype(ex_d) e1 = ex_d;	// e1�� const int&, d�� ������ �״�� �����´�




	// decltype(ǥ����)���� ǥ������ ���������� ��Ȯ���� ��������
	int a = 3;
	decltype(a) b = 2;		// int

	// &: lvalue ������
	int& ra = a;
	decltype(ra) rb = b;		// int&

	// &&: rvalue ������
	// lvalue���� ����, rvalue���� ����/����� �´�
	// rvalue�� ��� ������ �� �ִ�
	int&& x = 3;
	decltype(x) y = 2;			// int&&
	
	A* aA;
	decltype(aA->d) dd = 0.1;	// double

	int a1 = 3;
	int a2 = 3;
	int c = a1 + a2;
	// ǥ������ lvalue�� ���� �ְ�, rvalue�� ���� �ִ�
	// a1 + a2�� ���� ��� ���� ����̹Ƿ� rvalue�̴�
	decltype(a1 + a2) c1 = 2;
	// ������ ���� ���� �˱� ����
	decltype(c) c1_1 = 2;

	// (c): c�� ����Ű�� �ִ� �����ڷ� ���Ѵ�(...)
	//decltype(  (c)  ) c2 = 2; // lvalue�� �����ؾ� ��

//�����Ϸ��� ���� ��Ģ�� ����Ͽ� �� �Ű� ������ ������ Ȯ���մϴ�.
//	�� �Ű� ������
//		�ĺ��� �Ǵ� Ŭ���� ��� �׼����� ���: ������ ���� ����Ƽ�� ����
//		�Լ� �Ǵ� �����ε�� ������ �Լ��� ���� ȣ���� ���: �Լ��� ��ȯ ����(�����ε�� �����ڸ� ���� ��ȣ�� ����)
//		rvalue�̸� ���� ����
//		lvalue�̸� �� ���Ŀ� ���� lvalue ����


// 1. ��ȣ�� �ѷ������� ���� �ĺ��� ǥ����
// 	   ������ �̸�, �Լ��� �̸�, enum �̸�, Ŭ���� ��� ���� �� �̸��� �ִ� ��
// 	   ��� ���굵 ���� �ʰ� �ܼ��� ��ü �ϳ����� ����Ű�� ��
// 
// 2. �ĺ��� ǥ������ �ƴ� ���� �����ϸ�
// 	   ���� ���� �� ������ prvalue��� decltype�� T		ex) int
// 	   ���� ���� �� ������ lvalue��� decltype�� T&		ex) int&
// 	   ���� ���� �� ������ xvalue��� decltype�� T&&	ex) int&&
// 
// 	   (c)�� ()�� ���� �ĺ��ڰ� �ƴ� ǥ�����̴�
//
}