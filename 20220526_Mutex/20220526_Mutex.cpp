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
/// ���̽� ����� �ذ� ���
/// 1. �� ���� �ϳ��� �����ϵ��� �����Ѵ�
///    �̹� �۾� ���̰ų� �۾��� �ϴٰ� �������� �ٸ� ��������� �� �ǵ帮�� ��ŵд�
///    mutex�� lock, unlock
/// 
/// 2. CPU ���� ó���� �� ���� �� ó���ϵ��� ����д�
///    �ɰ��� �� ���� ����ó�� �޸𸮰� �����Ǵ� ������ atomic Ÿ������ �����ϸ� �ȴ�
///    std::atomic
/// </summary>


int main()
{
	// 1. �� ���� �ϳ��� �����ϵ��� �����Ѵ�
	int shared_memory(0);
	mutex mtx;

	auto count_func = [&]() {
		for (int i = 0; i < 10000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			mtx.lock();
			shared_memory++;
			mtx.unlock();
		}
	};
	std::thread t1 = std::thread(count_func);
	std::thread t2 = std::thread(count_func);
	t1.join();
	t2.join();
	cout << "After" << endl;
	cout << shared_memory << endl;

	shared_memory = 0;

	auto count_func1_2 = [&]() {
		for (int i = 0; i < 10000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));

			// unlock�� �ڵ����� ���༭ ������� ����
			std::lock_guard<mutex> lock(mtx);
			shared_memory++;
		}
	};
	std::thread t1_2_1 = std::thread(count_func1_2);
	std::thread t1_2_2 = std::thread(count_func1_2);
	t1_2_1.join();
	t1_2_2.join();
	cout << "After" << endl;
	cout << shared_memory << endl;


	// 2. CPU ���� ó���� �� ���� �� ó���ϵ��� ����д�
	atomic<int> shared_memory2(0);

	auto count_func2 = [&]() {
		for (int i = 0; i < 10000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			shared_memory2++;
			// Ȥ�� shared_memory2.fetch_add(1);
		}
	};
	std::thread t2_1 = std::thread(count_func2);
	std::thread t2_2 = std::thread(count_func2);
	t2_1.join();
	t2_2.join();
	cout << "After" << endl;
	cout << shared_memory2 << endl;


}
