#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

/// <summary>
/// override
/// 
/// ��� �Լ� ���� ������ C++11
///   const : ��� ����� ����ϰڴ�
/// 
/// 
/// </summary>

class Base
{
public:
	Base() {};
	~Base() {};

	virtual void mf1(void) const;
	virtual void mf2(int x);
	virtual void mf3(void)&;		// ��� �Լ� ���� ������
	virtual void mf4(void) const;
};

class Derived : public Base
{
public:
	Derived() {};
	~Derived() {};

	// �Ʒ��� �Լ����� ��� override�� ���� ����
	virtual void mf1(void);				// const ����
	virtual void mf2(unsigned int x);	// unsigned ����
	virtual void mf3(void)&&;			// R-Value
	void mf4(void) const;				// virtual Ű���� ����

	// override�� ���ָ� ������ ������ �߻������ֹǷ� ������
	virtual void mf1(void) const override;
	virtual void mf2(int x) override;
	virtual void mf3(void)& override;
	virtual void mf4(void) const override;

};

int main(void)
{
	

	return 0;
}