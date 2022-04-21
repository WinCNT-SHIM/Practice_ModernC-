#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/// <summary>
/// unique_ptr: ��Ÿ�� ������ ������ �ִ� ����Ʈ ������
///   �ϳ��� ����Ʈ �����͸��� Ư�� ��ü�� ������ �� �ֵ���, ��ü�� �������� ������ ����Ʈ ������
///   �Ϲ� �����Ϳʹ� �޸� ����� ���� �Ŀ� delete Ű���带 ����Ͽ� �޸𸮸� ������ �ʿ䰡 ����
/// 
///   ������ ����
///     unique_ptr �ν��Ͻ��� move() ��� �Լ��� ���� �������� ������ ���� ������, ����� �� �� ����
///     �������� �����Ǹ�, ���� u �ν��Ͻ��� �� �̻� �ش� ��ü�� �������� �ʰ� �缳���ȴ�
///     ��, unique_ptr������ =(������)�� �� ī�ǰ� �Ͼ�� �ʴ´�, �̵��� �����ϴ�(������ ����)
///       B = A �Ұ���
///       B = move(A) ����
/// 
/// ���� unique_ptr�� ����ϸ� ������? - ���ÿ� �������� ���� ��
///   1. Ŭ������ ���� �Ҵ��ϴ� ��� ������ ���� ��, �Ҹ��ڰ� ȣ��Ǹ� �˾Ƽ� �����Ǳ� ������ ���Ѵ�
///   2. ���� ������ ���� ��, �������� �Ǽ��� �ٿ��� �� �ִ�
///   3. STL ���Ϳ� �����͸� ������ ��, ���͸� clear�ϸ�, uni�� �ڵ������� �����͸� ��������
/// 
/// 
/// 
/// </summary>

/// <summary>
/// unique_ptr ���� ����
/// ���� �����ڸ� �����ؼ� �� ���簡 �Ͼ�� �ʵ��� �Ѵ�
/// </summary>
class A
{
	int a = 0;
public:
	A() {}
	A(int a) : a(a) {};
	A(const A& a) = delete;		// ���� ������ ����
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
		cout << "Person ������ ȣ��" << endl;
	}
	~Person()
	{
		cout << "Person �Ҹ��� ȣ��" << endl;
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
	// ==================== unique_ptr�� ���� ====================
	unique_ptr<int> ptr1(new int(5));
	// �� ������ ���(�̰� ����!)
	// new�� �������� ���ܰ� �߻����� ���� ������ ������ �� �ִ�
	unique_ptr<int> p = make_unique<int>(5);
	auto p2 = make_unique<int>(5);

	// ==================== unique_ptr�� �Ϲ����� ���� ====================
	cout << *ptr1 << endl;

	// ==================== Ư���� ��Ȳ�� ���� ���� ====================
	// ������ �����ϴ� ���
	// ���� ���� �����Ϳ� ������ ������ Ư�� �Լ��θ� �����ؾ� �Ѵ�
	int* _tmpPtr = ptr1.get();		// ptr1->�� �ƴ�

	// ���ο� �����ͷ� ���Ҵ�
	ptr1.reset(new int(3));


	unique_ptr<int> ptr2;
	// (�ּ�)�� ī�Ǵ� �Ұ���
	//ptr2 = ptr1;	// ������ ����

	// �̵��� ����
	ptr2 = move(ptr1);
	ptr1.reset();	// ptr1 = nullptr�� ����

	// unique_ptr�� �����ϰ� ���� �����ͷ� �ٲ� ���� release()�� ���
	// release()�� ���� ���� ���� ������
	auto ptr3 = ptr2.release();


	// ==================== unique_ptr�� ��� �� ====================
	cout << endl;
	cout << "==================== unique_ptr�� ��� �� ====================" << endl;
	//unique_ptr<Person> p1(new Person("�¼�", 30));
	//unique_ptr<Person> p1 = make_unique<Person>("�¼�", 30);
	auto p1 = make_unique<Person>("�¼�", 17);
	p1->Show();

	cout << endl;
	cout << "�Լ��� �Ķ���Ϳ� unique_ptr �����ϱ�" << endl;
	// �Լ� �Ķ���ʹ� �� ���簡 �Ͼ�Ƿ� �Ұ���
	//Do_Something(p1);
	// ������ ���ϴ� ���� ������ get()���� �Ѱ��� �� ����
	Do_Something(p1.get());

	Player* player = new Player("");

	cout << endl;
	cout << endl;

	// C++ 14 ����
	//unique_ptr<Player> player2(new Player("A"));
	//unique_ptr<Player[]> players2(new Player[20]);

	// C++ 14
	//unique_ptr<Player>  player2 = make_unique<Player>("A");
	//unique_ptr<Player[]> players2 = make_unique<Player[]>(20);	// �迭

	// ������ ������ �迭 ��� ���͸� �����
	vector<unique_ptr<Player>> _players;
	_players.push_back(make_unique<Player>("A"));
	_players.push_back(make_unique<Player>("B"));
	// emplace_back�� ��ü ������ ���Ϳ� �ñ��
	// ���� push_back�� ���� ������� �� �� ȿ�����̴�
	_players.emplace_back(new Player("emplace_back"));

	// ���� �ܺο��� ���� unique_ptr�� ���� ���
	unique_ptr<Player> _player1 = make_unique<Player>("_player1");
	//_players.push_back(_player1);		// ������ ����, �� ���簡 �Ͼ
	_players.push_back(move(_player1));
	_player1.reset();

	// const unique_ptr�� ������ ������ �Ұ�����
	//const unique_ptr<Player> _player2 = make_unique<Player>("_player2");
	//_players.push_back(move(_player2));	// ������ ����

	for (const auto& e : _players)
	{
		cout << "Player Name: " << e->name << endl;
	}

	// ���ٽ��� �̿��� custom deleter ����
	unique_ptr<Player, decltype(myDeleter)> _player3(new Player, myDeleter);

	return 0;
}