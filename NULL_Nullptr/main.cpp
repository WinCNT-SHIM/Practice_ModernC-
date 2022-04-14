#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>

using namespace std;

/// <summary>
/// nullptr
///   nullptr는 std::nullptr_t 타입이다
/// </summary>

void func(int) { cout << "int 호출" << endl; }
void func(int*) { cout << "int* 호출" << endl; }

void f(int) { cout << "int 호출" << endl; }
void f(bool) { cout << "bool 호출" << endl; }
void f(void*) { cout << "void* 호출" << endl; }

int main()
{
	int* p1 = 0;
	int* p2 = NULL;
	int* p3 = nullptr;

	// 가독성, 문제 소지가 큰 코드...
	if (p2 == p3) { cout << "NULL == nullptr" << endl; };

	func(0);			// int 호출
	func(NULL);			// int 호출
	func(nullptr);		// int* 호출
	func((int*)0);		// int* 호출
	func((int*)NULL);	// int* 호출


	// C++11은 별칭 선언(Alias Declaration) 제공
	//std::unique_ptr < std::unordered_map<std::string, std::string> >;
	// 기존의 typedef
	typedef std::unique_ptr < std::unordered_map<std::string, std::string> > UPtrMapSS;

	// 별칭 선언(Alias Declaration)
	// 별칭 선언은 템플릿에도 활용할 수 있다(별칭 템플릿)
	// C++14에서 type_traits에 많은 별칭 템플릿을 구현했다
	using UPtrMapSS = std::unique_ptr < std::unordered_map<std::string, std::string> >;

	remove_const<int>::type;
	std::remove_const_t<int>; // using remove_const_t = typename remove_const<int>::type;

	return 0;
}