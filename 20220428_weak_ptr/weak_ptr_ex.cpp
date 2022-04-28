#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

/// <summary>
/// weak_ptr
///   ��ȯ ���� ������ �ذ��ϱ� ���� ��Ÿ�� ���� �ٷ� weak_ptr
///   (���ΰ� ������ ����Ű�� shared_ptr�� ������ ���)
/// 
///   weak_ptr�� �ϳ� �̻��� shared_ptr �ν��Ͻ��� �����ϴ� ��ü�� ���� ������ ����������,
///   �������� ������ ���Ե��� �ʴ� ����Ʈ �������̴�
/// 
///   waek_ptr�� �����ڷ� shared_ptr�� �ٸ� weak_ptr�� �޴´�
///   ���� shared_ptr���� �ٸ���, �̹� ���� ����� ������� ��ü���� �ǹ̸� �����⿡,
///   ����� ������ �ּ� ������ weak_ptr�� ������ ���� ����
/// 
/// weak_ptr�� ������ ���� ��쿡 �����ϴ�
///   ��� ��ü�� �����ϵ�, ��ü�� ���� ������ �ְ� ���� ���� ���
///   �׸��� �Ź� Ư�� ��ü�� ID�� �÷��ǿ��� �˻��ϰ� ���� ���� ���
///   �׷��鼭 dangling pointer�� ���� ���輺�� ���ְ� ���� ��
/// 
///   ��� ID�� �����ϸ� �������� �ڽ�Ʈ ������ ����ϰ� ���� ���� ���� �ִ�
///   ���� ��� ��Ƽ�� ��Ƽ�� �Ҽӵ� �÷��̾ �����ϴ� ���,
///   ID�� ������� �ʰ� �����ͷ� �����Ϸ��� ��Ƽ�� �÷��̾��� ��ȣ ������ ���� �� �ִµ�
///   �� �� weak_ptr�� ����ϸ� ���ϴ�
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
		// �� user�� �� ������ �ȿ��� �Ҹ������,
		// �Ʒ� party->AddMember�� ���� �� �������� ����Ǿ user�� refCount = 1
		UserPtr user(new User);

		// shared_ptr�� ����ϸ� �Ʒ� �������� ��ȯ ������ �߻��Ѵ�.
		party->AddMember(user);
		user->SetParty(party);
	}

	// ���⿡�� party.reset�� ������ ������,
	// 5���� ��Ƽ���� party ��ü�� ���� �־� ���� refCount = 5 �� ����
	// ����, party�� �Ҹ���� ���ϰ�, party�� vector�� ����� user ��ü�� ���� �Ҹ���� ���Ѵ�.
	party.reset();

	return 0;
}