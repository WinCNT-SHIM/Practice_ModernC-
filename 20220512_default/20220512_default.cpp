#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>

using namespace std;

/// <summary>
/// �⺻ ���� Ȱ��ȭ
/// C++11������ ��������� ����� Ư�� ��� �Լ��� �⺻ �ൿ�� ����ϰڴٴ� �ǻ縦
/// = default�� �̿��ؼ� ��������� ǥ���� �� �ִ�
/// </summary>
class Widget
{
public:
	~Widget(void) {};								// 
	Widget(const Widget&) = default;				// �⺻ ���� ����, �⺻ �ൿ OK
	Widget& operator=(const Widget&) = default;		// �⺻ ���� ����, �⺻ �ൿ OK
};

/// <summary>
/// �Ļ� Ŭ���� ��ü���� �����ϴµ� ���̴� �������̽��� �����ϴ� Ŭ������ ����
/// ��� �� �Ҹ����� ��� �θ� Ŭ������ ������ ��� �ڽĵ� �������� �ڵ� �����ȴ�
/// </summary>
class Base
{
public:
	virtual ~Base(void) = default;	// �Ҹ��ڸ� ��������
	Base(Base&&) = default;
	Base& operator=(Base&&) = default;
	Base(const Base&) = default;
	Base& operator=(const Base&) = default;
};

class StringTable
{
public:
	StringTable(void) {}
	~StringTable(void) {}

private:
	std::map<int, std::string> value;
};

/// <summary>
/// ��� �Լ� ���ø��� �����ϸ� Ư�� ��� �Լ��� �ڵ� �ۼ��� ��Ȱ��ȭ�ȴٴ� ��Ģ�� ����!!
/// 
/// </summary>
class Widget2
{
public:
	template <typename T>
	Widget2(const T& rhs) {}
	template <typename T>
	Widget2(const T&) {};
};