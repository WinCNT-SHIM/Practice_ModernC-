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
#include <condition_variable>
#include <future>
using std::thread;

using namespace std;

/// <summary>
/// ������(Producer)�� �Һ���(Consumer) ����
/// 
/// 
/// 
/// �ᱹ ����� �񵿱��� �½�ũ �������� ���·� �����ߴ�
/// 
/// ����(Synchronous)�� �񵿱�(Asynchronous) ����
///   ���α׷��� ������, �� ���� �ϳ��� ���������� ����Ǵ� �۾��� ���������� ����ȴٰ� �ϰ�
///   �� ������ �ƴ϶� ���� ������ �������� ���ÿ� ����Ǵ� ���� �񵿱��� �����̶� �Ѵ�
/// C++11 ǥ�� ���̺귯���� ���� �ſ� ������ �񵿱��� ������ �� �� �ְ� ���ִ� ������ �����Ѵ�
/// 
/// std::promise�� std::future
///   �ᱹ �񵿱��� �������� �ϰ� ���� ����
/// 
/// packaged_task�� ����ϰ� �ȴٸ�
///   �����忡 ���� promise�� �������� �ʾƵ�
///   packaged_task�� �˾Ƽ�  �Լ��� ���ϰ��� ó�����༭ �ſ� ���ϴ�
/// 
/// 
/// async Ű����
///    std::async�� � �Լ��� �����Ѵٸ�
///    �ƿ� �����带 �˾Ƽ� ���� �ش� �Լ��� �񵿱������� �����ϰ�,
///    �� ������� future�� ����
/// 
/// 
/// ==================== �񵿱��� ���� ====================
/// std::thread�� ����ϴ� ������ ��� �񵿱��� ����
///   � �����尡 �����⸦ ��ٸ����� join �Լ��� ���� ����ؾ� �Ѵ�
/// 
/// std::async
///   �˾Ƽ� future ��ü�� �����ϹǷ� ������ó�� promise�� ����� �ʿ䰡 ������
///   �Ҹ��ڰ� ������ ���� �˾Ƽ� ������ش�
///   ���� ������� �ʾƵ� future ��ü�� ����ϱ� �������� ����Ѵ�
/// 
/// </summary>

void worker(std::promise<string>* p)
{
	// ����� �����ϴ� ���, �ش� ����� future�� ����
	p->set_value("some data");
}

int do_work(int x)
{
	cout << "Thread Start! Thread ID : " << this_thread::get_id() << endl;
	std::this_thread::sleep_for(std::chrono::seconds(x));
	cout << "Thread End! Thread ID : " << this_thread::get_id() << endl;
	return x;
}

// ����
void do_work_sequential()
{
	do_work(3);
	do_work(3);
	do_work(3);
}

// �񵿱�
void do_work_parallel()
{
	auto f1 = std::async([]() { do_work(3); });
	auto f2 = std::async([]() { do_work(3); });
	do_work(3);
	do_work(3);

	f1.get();
	f2.get();
}

int fun()
{
	for (int i = 1; i <= 10; i++) { cout << "fun[" << i << "]" << endl; }
	return 200;
}

int fun2(char c)
{
	for (int i = 1; i <= 10; i++) { cout << "fun[" << i << "]" << endl; }
	return 200;
}

int main()
{
	do_work_parallel();

	std::promise<string> p;
	std::future<string> f = p.get_future();	// �̷��� string �����͸� ���� �ְڴٴ� ���

	std::thread t(worker, &p);

	f.wait();	// �̷��� ��յ� �����͸� ���� ������ ��ٸ���

	// wait�� �����ߴٴ� ���� future�� �����Ͱ� �غ�Ǿ��ٴ� �ǹ�
	// ����� wait ���� �׳� get�ص� wait�� �Ͱ� ����
	cout << "�����: " << f.get() << endl;

	t.join();

	auto fut = async(fun);
	auto fut2 = async(launch::async, fun);		// �ٷ� �����带 �����ؼ� �Լ��� ����
	auto fut3 = async(launch::deferred, fun);	// future�� get �Լ��� ȣ��Ǿ��� �� ����

	auto fut4 = async(fun2, 'c');



}