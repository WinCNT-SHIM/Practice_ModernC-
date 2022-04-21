#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>

using namespace std;

/// <summary>
/// ����Ʈ �������� ����
///   <memory> ��� ���Ͽ� �����Ѵ�
///   C++������ �޸� �����κ��� ���α׷��� �������� �����ϱ� ���� ����Ʈ �����͸� ����
///   ����Ʈ �����Ͷ� ������ó�� �����ϴ� Ŭ���� ���ø�����
///   ����� ���� �޸𸮸� �ڵ����� �������ش�
/// 
/// C++11���� ������ ���� ����Ʈ �����͸� �����Ѵ�
///   unique_ptr<> : ��Ÿ�� ������
///   shared_ptr<> : ���� �ڿ� ����
///   weak_ptr<>   : shared_ptr�� �����ϱ� ���� ���
///   (���ſ��� auto_ptr�̶� �͵� ��������)
/// 
/// C++���� �ڿ��� �����ϴ� ���
/// RAII(Resource Acquisition Is Initialize) ����
///   �ڿ��� ȹ���� �ʱ�ȭ�̴�
///   ȹ���� ���ÿ� ������ ���ؼ��� Ȯ���ϰ� �����ϱ�
///   ���ÿ� �Ҵ�� �޸𸮴� �ڵ����� �����Ǵ� ���� �̿��� ������ ����
/// 
/// </summary>

class Foo
{
public:
	Foo() { cout << "����\n"; }
	Foo(int) { cout << "����(int)\n"; }
	~Foo() { cout << "�Ҹ�\n"; }
};

/// <summary>
/// RAII ���� ����
/// </summary>
class MyString
{
public:
	char* c = nullptr;
	MyString(size_t len)
	{
		// RAII - �ڿ��� ȹ���� �ʱ�ȭ�̴�
		cout << "MyString �ڿ� ȹ����!\n";
		c = new char[len];
	}
	~MyString()
	{
		// RAII - ���� �ÿ��� �ڿ��� ������ Ȯ���ϰ�!
		cout << "MyString �ڿ� delete!\n";
		delete[] c;
	}

	void func() { cout << c << endl; }
};

class MyString_SPtr
{
	MyString* data;
public:
	MyString_SPtr(MyString* d):data(d) { }
	~MyString_SPtr() { delete data; }

	MyString& operator*() const { return *data; }	// *
	MyString* operator->() const { return data; }	// ->
};

int main()
{
	Foo* ptr = new Foo();
	delete ptr;

	// ���� ������ ��ü�� ����Ʈ �����Ͱ� �����϶�� ����
	unique_ptr<Foo> smartPtr1(new Foo());				// C++11
	// ���� �ڵ带 ������ ��
	unique_ptr<Foo> smartPtr2 = make_unique<Foo>();	// C++14
	auto smartPtr3 = make_unique<Foo>();

	cout << "�߰�ȣ start\n";
	{
		auto smartPtr4 = make_unique<Foo>();
	}
	cout << "�߰�ȣ end\n";

	// ==================== ����Ʈ ������ ���� ���� ====================
	// RAII ���� ����
	cout << "\n�Ϲ� MyString\n";
	{
		MyString* a = new MyString(100);
		strcpy_s(a->c, 14, "Hello, World!");
		//MyString a(100);
		//strcpy_s(a.c, 14, "Hello, World!");
	}
	cout << "\n";

	cout << "\nMyString_SPtr\n";
	{
		MyString_SPtr sp = new MyString(100);	//MyString* sp = new MyString(100);
		strcpy_s(sp->c, 14, "Hello, World!");
		sp->func();
	}
	cout << "\n";

	// ==================== unique_ptr ���� ====================
	cout << "unique_ptr with unique_ptr\n";
	{
		unique_ptr<MyString> pa(new MyString(100));
		strcpy_s(pa->c, 14, "Hello, World!");
		pa->func();
	}
	cout << "\n";

	cout << "unique_ptr with unique_ptr\n";
	{
		unique_ptr<MyString> pa2 = make_unique<MyString>(100);
		strcpy_s(pa2->c, 14, "Hello, World!");
		pa2->func();
	}
	cout << "\n";

	return 0;
}