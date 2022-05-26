#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>
#include <algorithm> //for_each

#include <functional>

// ������
#include <thread>
#include <mutex>
using std::thread;

using namespace std;

/// <summary>
/// ���ÿ� �����Ű��
/// 
/// ���μ���
///   ���μ����� �ü������ ����Ǵ� ���α׷��� �ּ� ����
///   1���� ���α׷��� ����ų �� ���� 1���� ���μ����� �ǹ��Ѵ�
///   CPU�� ��� 1���� �ھ�, �� CPU�� �� ���� �� ���� ������ �����Ѵ�
/// 
/// ���ؽ�Ʈ ����Ī(Context Switching): ���� ���� ���� ó���� �� ���ؽ�Ʈ ���� ��ȯ�� �̷������
///   � ���α׷��� �����Ű��, �� ���� �����Ű��
///   �� ������ ���� ���α׷����� ����Ī���� ���� �ü���� �����ٷ��� �˾Ƽ� �����Ѵ�
/// 
/// ������
///   ���μ��� �ȿ��� ���� �Լ��� �񵿱������� ���ÿ� �����Ű�� ��
/// 
///   CPU �ھ�� ���ư��� ���α׷� ������ ������(Thread)��� �Ѵ�
///   CPU�� �ھ� �ϳ������� �� ���� �� ���� �������� ����� ����
///     �ٷ� ���� CPU�� ���� ������ �ھ� �ϳ��� ���� �ӵ��� ���̱� ���ٴ�,
///     CPU�� ������ �ھ� ������ �÷����� ������ ����
/// 
///   �� ���� ���μ����� �ּ� �� ���� ������� �̷���� ������, ���� ���� ������� ������ �� �ִ�
///   ���� ���� ������� ������ ���α׷��� ��Ƽ ������(Multi-Thread) ���α׷��̶�� �Ѵ�
/// 
///   ���μ����� ������ ���̴� �ڿ�(�޸�)�� ���� ����!!!
///   �� ���μ��� �ȿ� ������ 1�� ������ 2�� �ִٸ�, ���� ���� �޸𸮸� �����Ѵ�
/// 
/// � ��쿡 ���α׷��� ��Ƽ ������� ����� ���� �����ұ�?
///   ���� ����(Parallelizable)�� �۾���
///     --> ���� ���� ��� ��
///   ��� �ð��� �� �۾���
///     --> �ܺ� ����Ʈ�� ������ �ҷ��� ��� ��
/// 
/// C++ 11�������� ǥ�ؿ� �����尡 �߰��Ǿ���
///   �� �������� ���� �����带 �������(...)
/// 
/// ���̽� ����� �ذ� ���
/// 1. �� ���� �ϳ��� �����ϵ��� �����Ѵ�
///    �̹� �۾� ���̰ų� �۾��� �ϴٰ� �������� �ٸ� ��������� �� �ǵ帮�� ��ŵд�
///    mutex�� lock, unlock
/// 2. CPU ���� ó���� �� ���� �� ó���ϵ��� ����д�
///    �ɰ��� �� ���� ����ó�� �޸𸮰� �����Ǵ� ������ atomic Ÿ������ �����ϸ� �ȴ�
///    std::atomic
/// 
/// </summary>

void func1()
{

}
void func2()
{

}
void func3()
{

}

void worker(vector<int>::iterator start, vector<int>::iterator end, int* res)
{
	for (auto i = start; i != end; i++)
	{
		*res += *i;
	}
}

int main()
{
	std::thread t1(func1);
	std::thread t2(func2);
	std::thread t3(func3);

	// ȣ�� ��ü�� ����� ���� �����尡 �Ϸ�� ������ ����
	t1.join();
	t2.join();
	t3.join();

	vector<int> data(10000);
	for (int i = 0; i < 10000; i++) data[i] = i;

	int sumRes = 0;
	int SeperSumRes[4] = { 0, };

	vector<thread> workers;
	for (int i = 0; i < 4; i++)
	{
		workers.push_back(
			thread(
				worker,
				data.begin() + i * 2500,
				data.begin() + (i + 1) * 2500,
				&SeperSumRes[i]
			)
		);
	}

	for (int i = 0; i < 4; i++)
	{
		workers[i].join();
		sumRes += SeperSumRes[i];
	}
	cout << sumRes << endl;

	std::cout << "���� �Լ� ����\n";
	return 0;
}