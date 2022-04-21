#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/// <summary>
/// unique_ptr: 배타적 소유권 개념이 있는 스마트 소유권
///   하나의 스마트 포인터만이 특정 객체를 소유할 수 있도록, 객체에 소유권을 도입한 스마트 포인터
///   일반 포인터와는 달리 사용이 끝난 후에 delete 키워드를 사용하여 메모리를 해제할 필요가 없다
/// 
///   소유권 이전
///     unique_ptr 인스턴스는 move() 멤버 함수를 통해 소유권을 이전할 수는 있지만, 복사는 할 수 없다
///     소유권이 이전되면, 이전 u 인스턴스는 더 이상 해당 객체를 소유하지 않게 재설정된다
///     즉, unique_ptr에서는 =(연산자)로 값 카피가 일어나지 않는다, 이동은 가능하다(소유권 이전)
///       B = A 불가능
///       B = move(A) 가능
/// 
/// 언제 unique_ptr를 사용하면 좋을까? - 동시에 참조하지 않을 때
///   1. 클래스에 동적 할당하는 멤버 변수가 있을 때, 소멸자가 호출되면 알아서 해제되기 때문에 편리한다
///   2. 지역 변수로 사용될 때, 개발자의 실수를 줄여줄 수 있다
///   3. STL 벡터에 포인터를 저장할 때, 벡터를 clear하면, uni는 자동적으로 포인터를 지워진다
/// 
/// 
/// 
/// </summary>

/// <summary>
/// unique_ptr 구현 예상
/// 복사 생성자를 삭제해서 값 복사가 일어나지 않도록 한다
/// </summary>
class A
{
	int a = 0;
public:
	A() {}
	A(int a) : a(a) {};
	A(const A& a) = delete;		// 복사 생성자 삭제
};

class Person
{
private:
	string _name;
	int _age;
public:
	Person(const string& name, int age)
	{
		_name = name;
		_age = age;
		cout << "Person 생성자 호출" << endl;
	}
	~Person()
	{
		cout << "Person 소멸자 호출" << endl;
	}
	void Show();
};

void Person::Show()
{
	cout << _name << " " << _age << endl;
}

void Do_Something(Person* ptr)
{
	ptr->Show();
}

class Player
{
public:
	Player() : name("") {}
	Player(string n) : name(n) {}
	~Player() {}
	string name;
};

auto myDeleter = [](Player* pPlayer)
{
	cout << "myDeleter" << endl;
	delete pPlayer;
};

int main(void)
{
	// ==================== unique_ptr의 생성 ====================
	unique_ptr<int> ptr1(new int(5));
	// 더 안전한 방법(이걸 쓰자!)
	// new의 내부적인 예외가 발생했을 때의 위험을 방지할 수 있다
	unique_ptr<int> p = make_unique<int>(5);
	auto p2 = make_unique<int>(5);

	// ==================== unique_ptr의 일반적인 사용법 ====================
	cout << *ptr1 << endl;

	// ==================== 특별한 상황에 대한 사용법 ====================
	// 원본에 접근하는 방식
	// 직접 원본 포인터에 접근할 때에는 특정 함수로만 접근해야 한다
	int* _tmpPtr = ptr1.get();		// ptr1->가 아님

	// 새로운 포인터로 재할당
	ptr1.reset(new int(3));


	unique_ptr<int> ptr2;
	// (주소)값 카피는 불가능
	//ptr2 = ptr1;	// 컴파일 에러

	// 이동은 가능
	ptr2 = move(ptr1);
	ptr1.reset();	// ptr1 = nullptr과 같다

	// unique_ptr를 해제하고 원본 포인터로 바꿀 때는 release()를 사용
	// release()의 리턴 값이 원본 포인터
	auto ptr3 = ptr2.release();


	// ==================== unique_ptr의 사용 예 ====================
	cout << endl;
	cout << "==================== unique_ptr의 사용 예 ====================" << endl;
	//unique_ptr<Person> p1(new Person("승수", 30));
	//unique_ptr<Person> p1 = make_unique<Person>("승수", 30);
	auto p1 = make_unique<Person>("승수", 17);
	p1->Show();

	cout << endl;
	cout << "함수의 파라미터에 unique_ptr 대입하기" << endl;
	// 함수 파라미터는 값 복사가 일어나므로 불가능
	//Do_Something(p1);
	// 가능한 피하는 것이 좋지만 get()으로 넘겨줄 순 있음
	Do_Something(p1.get());

	Player* player = new Player("");

	cout << endl;
	cout << endl;

	// C++ 14 이전
	//unique_ptr<Player> player2(new Player("A"));
	//unique_ptr<Player[]> players2(new Player[20]);

	// C++ 14
	//unique_ptr<Player>  player2 = make_unique<Player>("A");
	//unique_ptr<Player[]> players2 = make_unique<Player[]>(20);	// 배열

	// 하지만 보통은 배열 대신 벡터를 사용함
	vector<unique_ptr<Player>> _players;
	_players.push_back(make_unique<Player>("A"));
	_players.push_back(make_unique<Player>("B"));
	// emplace_back은 객체 생성을 벡터에 맡긴다
	// 위의 push_back과 같은 결과지만 좀 더 효율적이다
	_players.emplace_back(new Player("emplace_back"));

	// 벡터 외부에서 만든 unique_ptr를 넣을 경우
	unique_ptr<Player> _player1 = make_unique<Player>("_player1");
	//_players.push_back(_player1);		// 컴파일 에러, 값 복사가 일어남
	_players.push_back(move(_player1));
	_player1.reset();

	// const unique_ptr는 소유권 이전도 불가능함
	//const unique_ptr<Player> _player2 = make_unique<Player>("_player2");
	//_players.push_back(move(_player2));	// 컴파일 에러

	for (const auto& e : _players)
	{
		cout << "Player Name: " << e->name << endl;
	}

	// 람다식을 이용한 custom deleter 예제
	unique_ptr<Player, decltype(myDeleter)> _player3(new Player, myDeleter);

	return 0;
}