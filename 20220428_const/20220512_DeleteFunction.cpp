#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>

using namespace std;

/// <summary>
/// ������ �Լ�(Delete Function)
/// 
/// ���ǵ��� ���� ����� �Լ����� ������ �Լ��� ��ȣ�϶�
/// 
/// � �Լ��� ����� ���� ������
/// 1. �Լ��� private���� �����ϰ� �Լ��� ���Ǹ� ������ �ʴ� ���	// C++98 priavate
/// 2. ����� ���� �Լ��� ���� ���� "= delete"�� ���̴� ��			// C++11 delete
/// 
/// ����� ���Ƶ� �Լ��� ����Ϸ��� ���� ���, 
///   C++98�� ��ũ ������ ������ �߰ߵ�����
///   C++11�� ������ �Լ��� ������ �������� �߰��� �� �ִ�
/// </summary>

class A
{
public:
	A() = delete;
	void Func() = delete;
};

template<class charT, class traits = char_traits<charT>>
class basic_ios : public ios_base
{
	basic_ios(const basic_ios&) = delete;
	basic_ios& operator=(const basic_ios&) = delete;
};

bool isLucky(int number) { return true; }
// �Ϲ��� ����ȯ�� ����(��ü�� explicit�� ���)
bool isLucky(char) = delete;
bool isLucky(bool) = delete;
bool isLucky(double) = delete;

template<typename T>
void processPointer(T* ptr) {}
// ������ ���� ���ø� �ν��Ͻ�ȭ ����
template<>
void processPointer(char*) = delete;		// char* Ÿ���� �����ͷ� ȣ�� �Ұ�
template<>
void processPointer(const char*) = delete;	// const char* Ÿ���� �����ͷ� ȣ�� �Ұ�

int main()
{
	if (isLucky(7))	{}
	//if (isLucky('a')) {}		// �Ϲ��� ����ȯ ����
	//if (isLucky(true)) {}		// �Ϲ��� ����ȯ ����
	//if (isLucky(3.5)) {}		// �Ϲ��� ����ȯ ����

	return 0;
}