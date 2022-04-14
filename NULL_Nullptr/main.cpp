#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>

using namespace std;

/// <summary>
/// nullptr
///   nullptr�� std::nullptr_t Ÿ���̴�
/// </summary>

void func(int) { cout << "int ȣ��" << endl; }
void func(int*) { cout << "int* ȣ��" << endl; }

void f(int) { cout << "int ȣ��" << endl; }
void f(bool) { cout << "bool ȣ��" << endl; }
void f(void*) { cout << "void* ȣ��" << endl; }

int main()
{
	int* p1 = 0;
	int* p2 = NULL;
	int* p3 = nullptr;

	// ������, ���� ������ ū �ڵ�...
	if (p2 == p3) { cout << "NULL == nullptr" << endl; };

	func(0);			// int ȣ��
	func(NULL);			// int ȣ��
	func(nullptr);		// int* ȣ��
	func((int*)0);		// int* ȣ��
	func((int*)NULL);	// int* ȣ��


	// C++11�� ��Ī ����(Alias Declaration) ����
	//std::unique_ptr < std::unordered_map<std::string, std::string> >;
	// ������ typedef
	typedef std::unique_ptr < std::unordered_map<std::string, std::string> > UPtrMapSS;

	// ��Ī ����(Alias Declaration)
	// ��Ī ������ ���ø����� Ȱ���� �� �ִ�(��Ī ���ø�)
	// C++14���� type_traits�� ���� ��Ī ���ø��� �����ߴ�
	using UPtrMapSS = std::unique_ptr < std::unordered_map<std::string, std::string> >;

	remove_const<int>::type;
	std::remove_const_t<int>; // using remove_const_t = typename remove_const<int>::type;

	return 0;
}