#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>

using namespace std;

/// <summary>
/// noexcept
/// 예외를 방출하지 않을 함수는 noexcept를 사용하는 것이 좋다
/// 
/// C+11부터 throw()가 deprecated되고, noexcept 키워드가 추가되었다
/// noexcept 키워드는 연산자의 형태와 한정자의 형태로 제공된다
/// </summary>

/// <summary>
/// 예외가 발생할 것인지 아닌지가 중요하지
/// 어떤 타입으로 예외가 발생할 것인지는 중요하지 않다
/// C++11에서는 그래서 noexcept라는 키워드가 생겼다
/// </summary>
int f(int x) throw(int, double);	// f함수는 예외를 방출하지 않음(C++98)
// noexcept 한정자
int f_noexcept(int x) noexcept;				// f는 예외를 방출하지 않음(C++11)

/// <summary>
/// C++11 제정 과정에서, 함수의 예외 방출 행동에 관한 정말로 의미 있는
/// 함수가 예외를 하나라도 던질지, 아니면 절대로 던지지 않는지의
/// 그 함수가 예외를 방출하지 않을 것임을 명시할 때에는 noexcept라는
/// </summary>
int f2(int x) noexcept(true);	// 예외 던질 가능성 없음, int f(int x) noexcept와 같다
int f3(int x) noexcept(false);	// 예외 던질 가능성 있음

/// <summary>
/// noexcept는 예외가 발생하지 않을 것이라고 명시적으로 보여줄 뿐
/// 실제로 예외 발생을 방지해주지는 않는다(...)
/// (따라서 예외가 발생하지 않을 것이라 픽스된 곳에만 사용하는 것이 좋다)
/// 
/// 그럼 왜 사용하는 것일까?
/// 
/// 
/// </summary>
void f() noexcept {}

/// <summary>
/// noexcept 연산자
/// 함수가 noexcept인지 아닌지를 판단하는 연산자
/// 
/// 예외가 발생하는 함수로 데이터 이동을 하면
/// 예외 발생 시 데이터 복구가 불가능하다
/// 그 때는 noexcept로 판단하고 이동할지 복사할지 정할 수 있다
/// </summary>
void f5() {}
void g5() noexcept {}

// 예외를 던지지 않는다
void bar() noexcept {}
// 예외를 던지지 않는다고 명시해놓고 예외를 던짐
void baz() noexcept { throw 55; }

/// <summary>
/// 템플릿에서 noexcept(noexcept(T))와 같이 쓰면
/// T() 생성자가 예외를 던지느냐에 따라 noexcept(true), noexcept(false)로 나뉜다
///   기본 throw로는 불가능한 처리
/// 안쪽의 noexcept(T)는 operator, 바깥쪽의 noexcept는 specifier로 사용되었다
/// </summary>
template<typename T>
void foo() noexcept(noexcept(T)) {}

/// <summary>
/// 컴파일러 최적화와 관련해서....
/// 
/// noexcept 함수에서 컴파일러의 최적화기(optimizer)는
/// 예외가 함수 바깥으로 전파될 수 있다고 해도 실행 시점 스택을 풀기 가능 상태로 유지할 필요가 없다
/// 또한, 예외가 noexcept 함수를 벗어난다고 해도 
/// noexcept 
/// </summary>

/// <summary>
/// noexcept 함수에서 예외를 던지면 std::terminate
/// </summary>

/// <summary>
/// noexcept가 자주 사용되는 곳
/// 1. 이동 연산
///   C++11의 이동 연산을 통해 최적화를 하면 push_back은 강력한 예외 안전성을 보장할 수 없게 된다.
///   이동 연산이 예외를 방출하지 않음이 확실한 경우에는 복사를 이동으로 대체해도 안전하다
///   std::vector::push_back 같은 함수는 std::move_if_noexcept로 구현되어 있다
///   즉, 이동 연산의 이점을 얻으려면 noexcept를 지원한다
/// 
/// 2. Swap 함수들
///   Swap 함수들은 noexcept를 통해서 최적화할 가치가 크다
///   표준 라이브러리에 있는 swap들의 noexcept 여부는
///   사용자 정의 swap들의 noexcept 여부에 어느 정도 의존한다
///   
/// 3. 메모리 해제 함수들
///   noexcept로 선언하는 것이 아주 중요한 일부 함수들은 기본적으로 noexcept로 선언된다
///   기본적으로 모든 메모리 해제 함수(delete와 delete[] 연산자)와 모든 소멸자는 암묵적으로 noexcept이다
/// </summary>

// Swap 함수들
template<class T, size_t N>
void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b)));

template<class T1, class T2>
struct pair
{
	void swap(pair& p) noexcept(noexcept(swap(first, p.first)) && noexcept(swap(second, p.second)));
};

/// <summary>
/// strong exception guarantee
/// </summary>

struct foo5
{
	int value;

	explicit foo5(int value) : value(value)
	{
		cout << "foo5(" << value << ")" << endl;
	}

	foo5(foo5 const& other) : value(other.value)
	{
		cout << "foo5(foo5(" << value << "))" << endl;
	}

	foo5(foo5&& other) noexcept : value(move(other.value))
	{
		cout << "foo5(move(foo5(" << value << ")))" << endl;
	}

	~foo5()
	{
		if (value != -1)
			cout << "~foo5(" << value << ")" << endl;
	}

};

int main()
{
	// noexcept 연산자
	cout << noexcept(f5()) << endl;	// false
	cout << noexcept(g5()) << endl;	// true

	bar();		// OK
	//baz();	// 컴파일은 문제 없으나, 런타임에 std::terminate가 호출

	// noexcept(noexcept(T))가 noexcept(true)로 된다
	foo<int>();

	vector<foo5> foo5s;
	foo5s.emplace_back(1);
	
	// 이때, 벡터의 (사이즈)확장을 위해 reserve가 발생
	// 만약 foo5의 이동 생성자가 noexcept를 보장하지 않으면, 복사 생성자가 발생한다
	// 즉, reallocating 과정에서 이동이 아닌 복사가 발생하여 성능 이득을 얻지 못하게 된다
	foo5s.emplace_back(2);
}