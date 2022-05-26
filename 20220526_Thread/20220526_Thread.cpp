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
/// 동시에 실행시키기
/// 
/// 프로세스
///   프로세스란 운영체제에서 실행되는 프로그램의 최소 단위
///   1개의 프로그램을 가리킬 때 보통 1개의 프로세스를 의미한다
///   CPU의 경우 1개의 코어, 즉 CPU가 한 번에 한 개의 연산을 수행한다
/// 
/// 컨텍스트 스위칭(Context Switching): 여러 개의 일을 처리할 때 컨텍스트 간의 전환이 이루어진다
///   어떤 프로그램을 실행시키고, 얼마 동안 실행시키고
///   또 다음에 무슨 프로그램으로 스위칭할지 등은 운영체제의 스케줄러가 알아서 결정한다
/// 
/// 쓰레드
///   프로세스 안에서 여러 함수를 비동기적으로 동시에 실행시키는 것
/// 
///   CPU 코어에서 돌아가는 프로그램 단위를 쓰레드(Thread)라고 한다
///   CPU의 코어 하나에서는 한 번에 한 개의 쓰레드의 명령을 실행
///     근래 들어서는 CPU의 발전 방향이 코어 하나의 동작 속도를 높이기 보다는,
///     CPU에 장착된 코어 개수를 늘려가는 식으로 발전
/// 
///   한 개의 프로세스는 최소 한 개의 쓰레드로 이루어져 있으며, 여러 개의 쓰레드로 구성될 수 있다
///   여러 개의 쓰레드로 구성된 프로그램을 멀티 쓰레드(Multi-Thread) 프로그램이라고 한다
/// 
///   프로세스와 쓰레드 차이는 자원(메모리)의 공유 여부!!!
///   한 프로세스 안에 쓰레드 1과 쓰레드 2가 있다면, 서로 같은 메모리를 공유한다
/// 
/// 어떤 경우에 프로그램을 멀티 쓰레드로 만드는 것이 유리할까?
///   병렬 가능(Parallelizable)한 작업들
///     --> 서버 같은 경우 등
///   대기 시간이 긴 작업들
///     --> 외부 사이트의 정보를 불러올 경우 등
/// 
/// C++ 11에서부터 표준에 쓰레드가 추가되었다
///   그 전까지는 각각 쓰레드를 만들었다(...)
/// 
/// 레이스 컨디션 해결 방법
/// 1. 한 번에 하나씩 접근하도록 제한한다
///    이미 작업 중이거나 작업을 하다가 말았으면 다른 스레드들이 못 건드리게 잠궈둔다
///    mutex의 lock, unlock
/// 2. CPU 연산 처리를 한 번에 다 처리하도록 묶어둔다
///    쪼개질 수 없는 원자처럼 메모리가 공유되는 변수를 atomic 타입으로 설정하면 된다
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

	// 호출 개체와 연결된 실행 스레드가 완료될 때까지 차단
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

	std::cout << "메인 함수 종료\n";
	return 0;
}