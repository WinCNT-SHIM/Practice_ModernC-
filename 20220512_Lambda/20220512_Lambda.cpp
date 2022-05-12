#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>

using namespace std;

/// <summary>
/// ========== 람다 함수 Lambda ==========
///   익명 함수(Anoymous Function), 함수를 보다 단순하게 표현하는 방법
///   코드를 데이터처럼 사용한다(함수 포인터 대신에 매개 변수로 전달, 리턴)
///   장점: 코드의 간결함(define을 보기 위해 볼 필요 없음), 지연 연산을 통한 퍼포먼스 향상
///         이터레이션 관련 코드를 구현하는 데 있어서 불필요한 부분을 제거할 수 있다
///   단점: 디버그가 힘들다
/// 
/// 람다 함수 표현식(expression)
///   일반적인 표현식
///     [capture list] (받는 인자) -> 리턴 타입 { 함수 본체 }
/// 
///   리턴 타입을 생략할 경우
///     [capture list] (받는 인자) { 함수 본체 }
/// 
/// 데이터도 함수(코드)도 어차피 바이너리로 메모리 영역에 적재된다
/// 그럼 함수 자체를 데이터로 취급하면 어떨까?
/// 
/// ========== 함수형 프로그래밍(Functional Programming) ==========
/// 프로그래밍 패러다임
///   명령형 프로그래밍 : 무엇(What)를 할지 나타내기보다 어떻게(How) 할지 설명하는 방식
///     절차 지향 프로그래밍 : 수행되어야 할 순차적인 처리 과정을 포함하는 방식
///     객체 지향 프로그래밍 : 객체들의 집합으로 프로그램의 상호 작용을 표현
///   
///   선언형 프로그래밍 : 어떻게 할건지(How)를 나타내기보다 무엇(What)을 할 건지를 설명하는 방식
///     함수형 프로그래밍 : 순수 함수를 조합하고 소프트웨어를 만드는 방식(클로저, 하스켈, 리스프)
/// 
/// 객체 지향 프로그래밍 - OOP
///   프로그래밍에서 필요한 데이터를 추상화시켜 상태와 행위를 가진 객체를 만들고
///   그 객체들 간의 유기적인 상호 작용을 통해 로직을 구정
///     추상화, 캡슐화, 정보 은닉, 상속성, 다형성 등이 특징
/// 
/// 함수형 프로그래밍 - Functional Programing
///   자료 처리를 수학적 함수의 계산으로 취급하고 상태와 가변 데이터를 멀리하는 프로그래밍 패러다임
///   순수 함수를 조합하고, 공유 상태나 변경 가능한 데이터 및 부작용을 피하여
///   순수 함수, 불변성, 참조 투명성, 게으른 평가 등이 특징
/// 
///   함수를 변수나 객체처럼 데이터로 다루는 방법(C++11에서는 람다로 지원)
/// </summary>

void func		// 함수 이름
(int a)			// 함수 입력부
{ cout << a; }	// 함수 구현부

// 람다 함수 표현식
//[]					// 함수 이름을 없애고 캡쳐부를 사용
//(int a)				// 함수 입력부
//void { cout << a; }	// 리턴 타입과 함수 구현부

int main()
{
	int a = 0;	// 데이터
	func(a);	// 코드(기능), 함수(데이터를 가공하는 코드를 운영함)

	// 코드 --> 데이터
	auto Lambda1 = [](int a) -> void { cout << a; };
	// Lambda1는 함수를 담고 있음...즉 함수처럼 사용하면 된다
	Lambda1(a);
}