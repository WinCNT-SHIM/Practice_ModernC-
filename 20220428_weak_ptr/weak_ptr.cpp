#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

/// <summary>
/// weak_ptr
///   순환 참조 문제를 해결하기 위해 나타난 것이 바로 weak_ptr
///   (서로가 상대방을 가리키는 shared_ptr를 가지는 경우)
/// 
///   weak_ptr은 하나 이상의 shared_ptr 인스턴스가 소유하는 객체에 대한 접근을 제공하지만,
///   소유자의 수에는 포함되지 않는 스마트 포인터이다
/// 
///   waek_ptr은 생성자로 shared_ptr나 다른 weak_ptr를 받는다
///   또한 shared_ptr과는 다르게, 이미 제어 블록이 만들어진 객체만이 의미를 가지기에,
///   평범한 포인터 주소 값으로 weak_ptr를 생성할 수는 없다
/// 
/// weak_ptr은 다음과 같은 경우에 유용하다
///   어떠한 객체를 참조하되, 객체의 수명에 영향을 주고 싶지 않은 경우
///   그리고 매번 특정 객체의 ID로 컬렉션에서 검색하고 싶지 않을 경우
///   그러면서 dangling pointer의 잠재 위험성을 없애고 싶을 때
/// 
///   사실 ID로 관리하면 편하지만 코스트 등으로 사용하고 싶지 않을 수가 있다
///   예를 들어 파티와 파티에 소속된 플레이어를 관리하는 경우,
///   ID를 사용하지 않고 포인터로 관리하려면 파티와 플레이어의 상호 참조가 생길 수 있는데
///   이 때 weak_ptr를 사용하면 편하다
/// 
/// </summary>
class Player
{
public:
	Player() : name("") {  }
	Player(const string& n) : name(n) {  }
	//~Player() {  }
	string name;

	weak_ptr<Player> other;

	void set_other(weak_ptr<Player> o)
	{
		other = o;
	}

	void access_other()
	{
		shared_ptr<Player> o = other.lock();
		if (o)
		{
			cout << "접근: " << this->name << " --> " << o->name << endl;
		}
		else
		{
			cout << "이미 소멸됨" << endl;
		}
	}
};

int main(void)
{
	//std::weak_ptr<Player> _player( new Player("A"));	// 컴파일 에러

	// weak_ptr 생성 방법
	std::shared_ptr<Player> _owner = make_shared<Player>("p");
	std::weak_ptr<Player> weakOwner = _owner;
	cout << _owner.use_count() << endl;		// 1

	//_owner.get();
	//weakOwner.get();	// get() 함수 사용 불가능

	// 공유 포인터 확인하기
	auto ptr = weakOwner.lock();	// shared_ptr 반환
	if (ptr != nullptr)
	{
		// weak_ptr은 get()으로 원본을 가져올 수 없지만
		// lock()으로 shared_ptr를 가져올 수 있다
	}

	//_owner = nullptr;
	// expired()는 shared_ptr이 nullptr이면 false 반환
	if (weakOwner.expired())
		cout << "shared_ptr가 null이 아님" << endl;
	else
		cout << "shared_ptr가 null" << endl;

	// ==================== 사용 예 ====================
	vector<shared_ptr<Player>> vec;
	vec.push_back(make_shared<Player>("Player1"));
	vec.push_back(make_shared<Player>("Player2"));

	vec[0]->set_other(vec[1]);
	vec[1]->set_other(vec[0]);

	// Player1와 Player2의 참조 카운트는 그대로이다
	cout << "vec[0]의 ref count: " << vec[0].use_count() << endl;
	cout << "vec[1]의 ref count: " << vec[1].use_count() << endl;

	// weak_ptr로 해당 객체 접근하기
	vec[0]->access_other();

	vec.pop_back();
	// weak_ptr로 소멸된 객체에 접근
	vec[0]->access_other();

	return 0;
}