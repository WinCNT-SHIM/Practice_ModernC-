#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/// <summary>
/// shared_ptr
///   ���� Ƚ���� �����ϴ� ����Ʈ ������
/// 
/// Ư¡
///     std::shared_ptr�� �Ϲ� �������� 2�� ũ�⸦ ���� �ȴ�
///     - ���������� �ڿ��� ���� �����Ϳ� �ش� �������� ������ ���� ���� ����Ű�� �����ͷ� ����
///       �ش� �������� ������ ���� ���� Control Block�̶�� �θ���
/// 
/// Control Block
///   �����δ� ���۷��� ī��Ʈ ���� �������� shared_ptr�� �����ϱ� ���� ������ �����ϴ� ��
///   Control Block�� ���� �Ҵ��ؼ� �װ��� ����Ű�� �����͸� ������ �ִ� ������� �����ȴ�
/// 
///   Control Block�� �������� ������ �Ʒ��� ��Ģ�� ������
///   1. make_shared�� �׻� ��Ʈ�� ����� �����Ѵ�
///   2. unique_ptr�� shared_ptr�� ������ ���
///   3. shared_ptr�� �����ڰ� raw pointer�� ���ڷ� ȣ����� ���
///       ���� raw pointer�� �� ���� shared_ptr�� ���� ���, �ߺ� ���� ������ �߻��Ѵ�
///       �ٸ� ������ �����ؼ� �ѱ�� ����� ���ϰ�, new�� �ٷ� �ѱ�� ������� �ʱ�ȭ�ϸ�
///       ���� ��ü�� �� �� �̻��� Control Block�� ����� ��츦 ������ �� �ִ�
/// 
/// ���� Ƚ��(Reference Count)
///   �̷��� �����ϰ� �ִ� ����Ʈ �������� ������ ���� Ƚ����� �Ѵ�
///   ���� Ƚ���� Ư�� ��ü�� ���ο� shared_ptr�� �߰��� ������ 1�� �����ϸ�,
///   �Ҹ�� ������ 1�� �����Ѵ�
///   ���� ������ shared_ptr�� ������ ���Ͽ� ���� Ƚ���� 0�� �Ǹ�,
///   delete Ű���带 ����Ͽ� �޸𸮸� �ڵ����� �����Ѵ�
/// 
/// ����Ʈ �����Ϳ� ������ �÷����� ����
///   ������ �÷��ʹ� ���� �����Ǵ��� ������ ����Ʈ �����ʹ� ��Ʈ�� �� �� �ִ�
///   �������� ���鿡���� ����Ʈ �����Ͱ� ���� ����
/// 
/// shared_ptr�� Custom Deleter
///   unique_ptr�� custom deleter�� Ÿ�Կ� ������ ��ġ����
/// 
/// ������
///   ��ȯ ����(A�� B�� �����ϰ� B�� A�� �����ϴ� ��)�� ���,
///   ���� Ƚ���� 0�� ���� �ʾ� �޸� ������ ����� �ȴ�
///   �̸� �����ϱ� ���� ������� ���� weak_ptr�̴�
/// 
/// </summary>
class A : public std::enable_shared_from_this<A>
{
	int* data;
public:
	A() { data = new int[100]; }
	~A() { delete[] data; }
	void func() {}
	std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); }
};

// Custom Deleter
auto loggingDel = [](A* pw)
{
	delete pw;
};

class Car {};
class Truck : public Car {};
void func(shared_ptr<Car> _car) {}		// ���� Ƚ���� ������
void func(shared_ptr<Car>& _car) {}		// ���� Ƚ���� �������� ����

int main(void)
{
	shared_ptr<int> ptr1(new int(5));
	cout << "Reference Count: " << ptr1.use_count() << endl;

	auto ptr2(ptr1);
	cout << "Reference Count: " << ptr1.use_count() << endl;

	{
		auto ptr3 = ptr2;
		cout << "Reference Count: " << ptr1.use_count() << endl;
		cout << "ptr3�� Reference Count: " << ptr1.use_count() << endl;
	}
	cout << "ptr1�� Reference Count: " << ptr1.use_count() << endl;

	// ==================== ====================
	shared_ptr<A> p = make_shared<A>();
	auto p2 = make_shared<A>();
	auto han = p;

	A* spA = p.get();

	p->func();
	p.get()->func();
	(*spA).func();
	
	vector<shared_ptr<A>> vec;
	//vec.push_back();
	vec.push_back(make_shared<A>());




	han.reset();
	p.reset();


	// ==================== shared point�� ĳ���� ====================
	shared_ptr<Car> pCar(new Truck());
	shared_ptr<Truck> pTruck = static_pointer_cast<Truck>(pCar);

	// ==================== shared point�� �迭 ====================
	// C++17 ���� �迭 ���¸� shared_ptr�� ����ϰ��� �� ���� ����� ����� �����ؾ� �Ѵ�

	// 

	// 

	// �������ڸ�
	shared_ptr<A> array(new A[10]);			// delete ����
	shared_ptr<A> array2(new A[10]);
	shared_ptr<A> array14(new A[10]);
	shared_ptr<A[]> array17(new A[10]);		// C++17

	return 0;
}