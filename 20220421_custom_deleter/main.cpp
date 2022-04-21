#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/// <summary>
/// custom_deleter
///   메모리 할당에는 관여하지 않으면서 메모리의 해제를 수행
///   new가 아니라 malloc과 같이 다른 형태로 할당했다면 문제가 발생할 것이다
///   이 때는 custom deleter를 구현해줘야 한다
/// 
/// std::unique_ptr의 자원 해제는 delete를 통해 이루어지지만
/// 
/// 
/// default deleter를 쓰는 경우에는
///   unique_ptr의 크기가 정확히 raw pointer와 같다
/// 
/// custom deleter를 쓰는 경우에는
///   함수 포인터인 경우에는 워드(word) 하나 크기에서 2개 크기로 늘린다
/// 
/// 
/// 
/// </summary>

// 함수 객체
struct MyDeleter
{
	MyDeleter() { cout << "MyDeleter()" << endl; }
	~MyDeleter() { cout << "~MyDeleter()" << endl; }
	void operator()(void* x) { free(x); }
};

// 함수 포인터
void my_deleter(void* x)
{
	free(x);
}

auto myDeleter = [](Player* pPlayer)
{
	cout << "myDeleter" << endl;
	delete pPlayer;
};

// ==================== 상속 관계에서 사용하는 예제 ====================
class Player
{
public:
	Player() : name("") {}
	Player(string n) : name(n) {}
	virtual ~Player() {}
	string name;
};

class Hero : Player
{
	Hero() {};
	~Hero() {};
};
class Enemy : Player
{
	Enemy() {};
	~Enemy() {};
};

template<typename... Ts>
auto makePlayer(Ts&&... params)		// 팩토리 함수
{
	auto myDelter = [](Player* pPlayer)
	{
		delete pPlayer;
	};

	// custom deleter를 설정해서 상속받은 각각의 클래스에서 소멸자가 호출되도록 설정
	unique_ptr<Player, decltype(myDeleter)> pPlayer(nullptr, myDeleter);

	if (1)
	{
		pPlayer.reset(new Hero(forward<Ts>(params)...));
	}
	else if (2)
	{
		pPlayer.reset(new Enemy(forward<Ts>(params)...));
	}
	return pPlayer;
}

int main(void)
{
	// 소멸자의 함수 포인터나 함수 객체, 람다를 전달한다
	unique_ptr<int, MyDeleter> a((int*) malloc(sizeof(int)));
	unique_ptr<int, void(*)(void*)> a2((int*) malloc(sizeof(int)), my_deleter);

	return 0;
}