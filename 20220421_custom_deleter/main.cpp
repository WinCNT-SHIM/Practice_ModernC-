#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/// <summary>
/// custom_deleter
///   �޸� �Ҵ翡�� �������� �����鼭 �޸��� ������ ����
///   new�� �ƴ϶� malloc�� ���� �ٸ� ���·� �Ҵ��ߴٸ� ������ �߻��� ���̴�
///   �� ���� custom deleter�� ��������� �Ѵ�
/// 
/// std::unique_ptr�� �ڿ� ������ delete�� ���� �̷��������
/// 
/// 
/// default deleter�� ���� ��쿡��
///   unique_ptr�� ũ�Ⱑ ��Ȯ�� raw pointer�� ����
/// 
/// custom deleter�� ���� ��쿡��
///   �Լ� �������� ��쿡�� ����(word) �ϳ� ũ�⿡�� 2�� ũ��� �ø���
/// 
/// 
/// 
/// </summary>

// �Լ� ��ü
struct MyDeleter
{
	MyDeleter() { cout << "MyDeleter()" << endl; }
	~MyDeleter() { cout << "~MyDeleter()" << endl; }
	void operator()(void* x) { free(x); }
};

// �Լ� ������
void my_deleter(void* x)
{
	free(x);
}

auto myDeleter = [](Player* pPlayer)
{
	cout << "myDeleter" << endl;
	delete pPlayer;
};

// ==================== ��� ���迡�� ����ϴ� ���� ====================
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
auto makePlayer(Ts&&... params)		// ���丮 �Լ�
{
	auto myDelter = [](Player* pPlayer)
	{
		delete pPlayer;
	};

	// custom deleter�� �����ؼ� ��ӹ��� ������ Ŭ�������� �Ҹ��ڰ� ȣ��ǵ��� ����
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
	// �Ҹ����� �Լ� �����ͳ� �Լ� ��ü, ���ٸ� �����Ѵ�
	unique_ptr<int, MyDeleter> a((int*) malloc(sizeof(int)));
	unique_ptr<int, void(*)(void*)> a2((int*) malloc(sizeof(int)), my_deleter);

	return 0;
}