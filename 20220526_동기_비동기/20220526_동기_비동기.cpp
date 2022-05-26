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
#include <condition_variable>
#include <future>
using std::thread;

using namespace std;

/// <summary>
/// 생산자(Producer)와 소비자(Consumer) 패턴
/// 
/// 
/// 
/// 결국 동기와 비동기의 태스크 쓰레드의 형태로 발전했다
/// 
/// 동기(Synchronous)와 비동기(Asynchronous) 실행
///   프로그램의 실행이, 한 번에 하나씩 순차적으로 실행되는 작업을 동기적으로 실행된다고 하고
///   한 갈래가 아니라 여러 갈래로 갈라져서 동시에 진행되는 것을 비동기적 실행이라 한다
/// C++11 표준 라이브러리를 통해 매우 간단히 비동기적 실행을 할 수 있게 해주는 도구를 제공한다
/// 
/// std::promise와 std::future
///   결국 비동기적 실행으로 하고 싶은 일은
/// 
/// packaged_task를 사용하게 된다면
///   쓰레드에 굳이 promise를 전달하지 않아도
///   packaged_task가 알아서  함수의 리턴값을 처리해줘서 매우 편리하다
/// 
/// 
/// async 키워드
///    std::async에 어떤 함수를 전달한다면
///    아예 쓰레드를 알아서 만들어서 해당 함수를 비동기적으로 실행하고,
///    그 결과값을 future에 전달
/// 
/// 
/// ==================== 비동기적 실행 ====================
/// std::thread만 사용하는 스레드 기반 비동기적 실행
///   어떤 쓰레드가 끝나기를 기다리려면 join 함수를 통해 대기해야 한다
/// 
/// std::async
///   알아서 future 객체를 리턴하므로 쓰레드처럼 promise를 사용할 필요가 ㅇ벗다
///   소멸자가 끝나는 것을 알아서 대기해준다
///   따로 명시하지 않아도 future 객체를 사용하기 전까지는 대기한다
/// 
/// </summary>

void worker(std::promise<string>* p)
{
	// 약속을 이행하는 모습, 해당 결과는 future에 들어간다
	p->set_value("some data");
}

int do_work(int x)
{
	cout << "Thread Start! Thread ID : " << this_thread::get_id() << endl;
	std::this_thread::sleep_for(std::chrono::seconds(x));
	cout << "Thread End! Thread ID : " << this_thread::get_id() << endl;
	return x;
}

// 동기
void do_work_sequential()
{
	do_work(3);
	do_work(3);
	do_work(3);
}

// 비동기
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
	std::future<string> f = p.get_future();	// 미래에 string 데이터를 돌려 주겠다는 약속

	std::thread t(worker, &p);

	f.wait();	// 미래에 약손된 데이터를 받을 때까지 기다린다

	// wait이 리턴했다는 뜻이 future에 데이터가 준비되었다는 의미
	// 참고로 wait 없이 그냥 get해도 wait한 것과 같다
	cout << "결과값: " << f.get() << endl;

	t.join();

	auto fut = async(fun);
	auto fut2 = async(launch::async, fun);		// 바로 쓰레드를 생성해서 함수를 실행
	auto fut3 = async(launch::deferred, fun);	// future의 get 함수가 호출되었을 때 실행

	auto fut4 = async(fun2, 'c');



}