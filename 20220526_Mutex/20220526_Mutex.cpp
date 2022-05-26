#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>
#include <algorithm> //for_each

#include <functional>

// 쓰레드
#include <thread>
#include <mutex>
using std::thread;

using namespace std;

/// <summary>
/// 레이스 컨디션 해결 방법
/// 1. 한 번에 하나씩 접근하도록 제한한다
///    이미 작업 중이거나 작업을 하다가 말았으면 다른 스레드들이 못 건드리게 잠궈둔다
///    mutex의 lock, unlock
/// 
/// 2. CPU 연산 처리를 한 번에 다 처리하도록 묶어둔다
///    쪼개질 수 없는 원자처럼 메모리가 공유되는 변수를 atomic 타입으로 설정하면 된다
///    std::atomic
/// </summary>


int main()
{
	// 1. 한 번에 하나씩 접근하도록 제한한다
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

			// unlock을 자동으로 해줘서 데드락을 방지
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


	// 2. CPU 연산 처리를 한 번에 다 처리하도록 묶어둔다
	atomic<int> shared_memory2(0);

	auto count_func2 = [&]() {
		for (int i = 0; i < 10000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			shared_memory2++;
			// 혹은 shared_memory2.fetch_add(1);
		}
	};
	std::thread t2_1 = std::thread(count_func2);
	std::thread t2_2 = std::thread(count_func2);
	t2_1.join();
	t2_2.join();
	cout << "After" << endl;
	cout << shared_memory2 << endl;


}
