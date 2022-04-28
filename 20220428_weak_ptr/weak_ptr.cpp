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
			cout << "����: " << this->name << " --> " << o->name << endl;
		}
		else
		{
			cout << "�̹� �Ҹ��" << endl;
		}
	}
};

int main(void)
{
	//std::weak_ptr<Player> _player( new Player("A"));	// ������ ����

	// weak_ptr ���� ���
	std::shared_ptr<Player> _owner = make_shared<Player>("p");
	std::weak_ptr<Player> weakOwner = _owner;
	cout << _owner.use_count() << endl;		// 1

	//_owner.get();
	//weakOwner.get();	// get() �Լ� ��� �Ұ���

	// ���� ������ Ȯ���ϱ�
	auto ptr = weakOwner.lock();	// shared_ptr ��ȯ
	if (ptr != nullptr)
	{
		// weak_ptr�� get()���� ������ ������ �� ������
		// lock()���� shared_ptr�� ������ �� �ִ�
	}

	//_owner = nullptr;
	// expired()�� shared_ptr�� nullptr�̸� false ��ȯ
	if (weakOwner.expired())
		cout << "shared_ptr�� null�� �ƴ�" << endl;
	else
		cout << "shared_ptr�� null" << endl;

	// ==================== ��� �� ====================
	vector<shared_ptr<Player>> vec;
	vec.push_back(make_shared<Player>("Player1"));
	vec.push_back(make_shared<Player>("Player2"));

	vec[0]->set_other(vec[1]);
	vec[1]->set_other(vec[0]);

	// Player1�� Player2�� ���� ī��Ʈ�� �״���̴�
	cout << "vec[0]�� ref count: " << vec[0].use_count() << endl;
	cout << "vec[1]�� ref count: " << vec[1].use_count() << endl;

	// weak_ptr�� �ش� ��ü �����ϱ�
	vec[0]->access_other();

	vec.pop_back();
	// weak_ptr�� �Ҹ�� ��ü�� ����
	vec[0]->access_other();

	return 0;
}