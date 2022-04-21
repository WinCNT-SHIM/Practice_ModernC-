#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/// <summary>
/// shared_ptr
///   참조 횟수로 관리하는 스마트 포인터
/// 
/// 특징
///     std::shared_ptr은 일반 포인터의 2배 크기를 갖게 된다
///     - 내부적으로 자원에 대한 포인터와 해당 포인터의 정보를 담은 곳을 가르키는 포인터로 관리
///       해당 포인터의 정보를 담은 곳을 Control Block이라고 부른다
/// 
/// Control Block
///   실제로는 레퍼런스 카운트 외의 여러가지 shared_ptr을 관리하기 위한 정보를 보관하는 곳
///   Control Block를 따로 할당해서 그곳을 가리키는 포인터를 가지고 있는 방식으로 구성된다
/// 
///   Control Block를 생성할지 말지는 아래의 규칙을 따른다
///   1. make_shared는 항상 컨트롤 블록을 생성한다
///   2. unique_ptr로 shared_ptr을 생성할 경우
///   3. shared_ptr의 생성자가 raw pointer를 인자로 호출됐을 경우
///       같은 raw pointer로 두 개의 shared_ptr을 만들 경우, 중복 해제 문제가 발생한다
///       다른 변수에 저장해서 넘기는 방법은 피하고, new로 바로 넘기는 방식으로 초기화하면
///       같은 객체에 두 개 이상의 Control Block이 생기는 경우를 방지할 수 있다
/// 
/// 참조 횟수(Reference Count)
///   이렇게 참조하고 있는 스마트 포인터의 개수를 참조 횟수라고 한다
///   참조 횟수는 특정 객체에 새로운 shared_ptr이 추가될 때마다 1씩 증가하며,
///   소멸될 때마다 1씩 감소한다
///   따라서 마지막 shared_ptr의 수명이 다하여 참조 횟수가 0이 되면,
///   delete 키워드를 사용하여 메모리를 자동으로 해제한다
/// 
/// 스마트 포인터와 가비지 컬렉터의 차이
///   가비지 컬렉터는 언제 삭제되는지 모르지만 스마트 포인터는 컨트롤 할 수 있다
///   성능적인 측면에서는 스마트 포인터가 더욱 좋다
/// 
/// shared_ptr과 Custom Deleter
///   unique_ptr은 custom deleter가 타입에 영향을 미치지만
/// 
/// 주의점
///   순환 참조(A가 B를 참조하고 B가 A를 참조하는 등)인 경우,
///   참조 횟수가 0이 되지 않아 메모리 누수가 생기게 된다
///   이를 방지하기 위해 만들어진 것이 weak_ptr이다
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
void func(shared_ptr<Car> _car) {}		// 참조 횟수가 증가함
void func(shared_ptr<Car>& _car) {}		// 참조 횟수가 증가하지 않음

int main(void)
{
	shared_ptr<int> ptr1(new int(5));
	cout << "Reference Count: " << ptr1.use_count() << endl;

	auto ptr2(ptr1);
	cout << "Reference Count: " << ptr1.use_count() << endl;

	{
		auto ptr3 = ptr2;
		cout << "Reference Count: " << ptr1.use_count() << endl;
		cout << "ptr3의 Reference Count: " << ptr1.use_count() << endl;
	}
	cout << "ptr1의 Reference Count: " << ptr1.use_count() << endl;

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


	// ==================== shared point의 캐스팅 ====================
	shared_ptr<Car> pCar(new Truck());
	shared_ptr<Truck> pTruck = static_pointer_cast<Truck>(pCar);

	// ==================== shared point의 배열 ====================
	// C++17 이전 배열 형태를 shared_ptr로 사용하고자 할 때는 지우는 방법을 정의해야 한다

	// 

	// 

	// 정리하자면
	shared_ptr<A> array(new A[10]);			// delete 문제
	shared_ptr<A> array2(new A[10]);
	shared_ptr<A> array14(new A[10]);
	shared_ptr<A[]> array17(new A[10]);		// C++17

	return 0;
}