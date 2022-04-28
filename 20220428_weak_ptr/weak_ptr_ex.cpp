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

class User;
class Party;
typedef shared_ptr<User> UserPtr;
typedef shared_ptr<Party> PartyPtr;
typedef weak_ptr<User> UserWeakPtr;
typedef weak_ptr<Party> PartyWeakPtr;

class Party
{
public:
	Party() {}
	~Party() { m_MemberList.clear(); }

public:
	void AddMember(const UserPtr& member)
	{
		m_MemberList.push_back(member);
	}

private:
	typedef vector<UserPtr> MemberList;
	MemberList m_MemberList;
};

class User
{
public:
	void SetParty(const PartyPtr& party)
	{
		m_Party = party;
	}

private:
	PartyPtr m_Party;
};


int main()
{
	PartyPtr party(new Party);

	for (int i = 0; i < 5; i++)
	{
		// 이 user는 이 스코프 안에서 소멸되지만,
		// 아래 party->AddMember로 인해 이 스코프가 종료되어도 user의 refCount = 1
		UserPtr user(new User);

		// shared_ptr을 사용하면 아래 과정에서 순환 참조가 발생한다.
		party->AddMember(user);
		user->SetParty(party);
	}

	// 여기에서 party.reset을 수행해 보지만,
	// 5명의 파티원이 party 객체를 물고 있어 아직 refCount = 5 의 상태
	// 따라서, party가 소멸되지 못하고, party의 vector에 저장된 user 객체들 역시 소멸되지 못한다.
	party.reset();

	return 0;
}