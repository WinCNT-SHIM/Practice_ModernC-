#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>

#include <functional>

using namespace std;

/// <summary>
/// ========== 람다 함수 Lambda ==========
///   익명 함수(Anoymous Function), 함수를 보다 단순하게 표현하는 방법
///   코드를 데이터처럼 사용한다(함수 포인터 대신에 매개 변수로 전달, 리턴)
///   장점: 코드의 간결함(define을 보기 위해 볼 필요 없음),
///         지연 연산을 통한 퍼포먼스 향상
///         이터레이션 관련 코드를 구현하는 데 있어서 불필요한 부분을 제거할 수 있다
///   단점: 셀프 난독화 가능
///         디버깅 시 콜스택 추적이 어렵다
///         (그래서 보통 복잡한 함수를 람다로 만들지 않음)
/// 
/// 람다 함수 표현식(expression)
///   일반적인 표현식
///     [capture list] (받는 인자) -> 리턴 타입 { 함수 본체 }
/// 
///   리턴 타입을 생략할 경우
///     [capture list] (받는 인자) { 함수 본체 }
/// 
///   사용 예제
///     [capture list] (받는 인자) { 함수 본체 } (실행 인자)
/// 
/// []  lambda capture 영역, 외부 변수를 참조함
/// ()  parameter list 영역
///    + mutable : 캡처 리스트로 넘어오는 값이 변경됨을 알림
/// {}  body 영역
/// ()  lambda 함수를 명시적으로 호출할 때
/// 
/// 
/// ========== [] 캡처 블록 ==========
/// 외부 변수를 상용(캡처)한다, 명시적으로 표시하기 때문에 알기 쉬워진다
/// [x]  : 값 복사로 가져옴
/// [&x] : 값 참조로 가져옴
/// [=]  : {body 영역}의 모든 변수들을 값 복사로 캡처한다
/// [&]  : {body 영역}의 모든 변수들을 값 참조로 캡처한다
/// 
/// 예제) 섞어서 쓸 수도 있다
/// [=, &x, &y]
/// [&, y]
/// [&, &y] : 구문 오류
/// [this]  : 객체를 접근하는 것으로, "this->"가 없어도 동작한다
/// 
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
///   순수 함수(Pure Function), 불변성(Immutable), 참조 투명성(Referential Transparency), 게으른 평가(Lazy Evaluation) 등이 특징
/// 
///   함수를 변수나 객체처럼 데이터로 다루는 방법(C++11에서는 람다를 지원)
/// 
/// 최근 언어들은 캡슐화나 상속같은 기능을 모두 지원
/// 
/// </summary>

void func		// 함수 이름
(int a)			// 함수 입력부
{ cout << a; }	// 함수 구현부

// 람다 함수 표현식
//[]					// 함수 이름을 없애고 캡쳐부를 사용
//(int a)				// 함수 입력부
//void { cout << a; }	// 리턴 타입과 함수 구현부

/// <summary>
/// 람다 표현이 있기 전까지는 클래스로 만들었다
/// (클로저라고 함)
/// 하지만 역시 부피가 커지기 때문에 람다 표현식이 나왔다
/// </summary>
class Plus
{
	int localVar;
public:
	explicit Plus(int a) : localVar{ a } {}
	int operator()(int x) const
	{
		return localVar + x;
	}
};

void Print() { cout << "Hello World" << endl; };
void PrintNum(int x) { cout << x << endl; };
int Abs(int x) { if (x < 0) return -x; return x; };
bool isEven(int x) { return x % 2; };
int Add(int x, int y) { return x + y; };
int Add2(int x, int y) { return x + y; };
// 위 함수를 람다 표현으로 변환하면 다음과 같다
// []() { cout << "Hello World" << endl; };
// [](int x) { cout << x << endl; };
// [](int x) { if (x < 0) return -x; return x; };
// [](int x) { return x % 2; };
// [](int x, int y) { return x + y; };

int globalVar1 = 1;

function<void()> FunctionReturn();
template<typename TFunc>
void TemplateFunc(TFunc func);

int main()
{
	int a = 0;	// 데이터
	func(a);	// 코드(기능), 함수(데이터를 가공하는 코드를 운영함)

	// 코드 --> 데이터
	auto Lambda1 = [](int a) -> void { cout << a; };
	// Lambda1는 함수를 담고 있음...즉 함수처럼 사용하면 된다
	Lambda1(a);

	auto Lambda2 = [](int a) { cout << a; };

	// 람다 표현이 있기 전
	// 특정 수를 더하는 기능을 클래스로 만들었다
	Plus plus3{ 3 };	// 주어진 수에 3를 더하는 기능을 구현한 클래스
	Plus plus5{ 5 };	// 주어진 수에 5를 더하는 기능을 구현한 클래스
	// plus3, plus5가 데이터처럼 굳어졌다, 즉 변수처럼 사용할 수 있음
	// 이러한 것을 클로저라고 한다
	cout << plus3(5) << endl;
	cout << plus5(5) << endl;

	// 람다 사용 예제
	int a1 = Add(1, 2);
	int a2 = [](int x, int y) { return x + y; }(1, 2);
	cout << "a2: " << a2 << endl;

	bool b1 = isEven(1);
	bool b2 = [](int x) { return x % 2; }(1);
	cout << "b2: " << b2 << endl;

	// ========== 비슷한 표현식 3가지 ==========
	
	// 람다식으로 변수처럼 정의해서 사용
	// 함수 객체보다 간결하게 사용할 수 있다, 속도도 빠르다
	// (함수 객체는 미리 정의해서 사용)
	auto f1 = [](int x, int y) { return x + y; };
	cout << "f1: " << f1(1, 2) << endl;

	// 3. 함수 객체(Function Object) 특정 형식의 코드를 정의
	// #include <functional> 필요
	// function<    > 형식
	// C++에서는 람다식도 클래스도 구현되어 있기 때문에 사실 거의 같다
	// 일반적으로 미리 정의해서 사용할 수 있다
	function<int(int, int)> f2 = Add;
	// 함수 객체에 람다를 담을 수도 있다(...)
	function<int(int, int)> f2_2 = [](int x, int y) { return x + y; };
	cout << "f2: " << f2(1, 2) << endl;
	cout << "f2_2: " << f2_2(1, 2) << endl;

	// 참고 - 함수 객체는 함수 포인터와는 다른 것
	// 함수 객체 쪽이 더 정보를 담을 수 있고(클래스이기 때문)
	// 확장성이 훨씬 좋다
	int (*f3)(int x, int y) = Add;
	cout << "f3: " << f3(1, 2) << endl;


	/// ========== [] 캡처 블록 ==========
	auto a_0519 = 1;

	//[a_0519]()
	//{
	//	a_0519++;	// mutable이 없으면 a_0519가 상수로 들어와서 에러가 발생한다
	//	cout << a_0519 << endl;
	//};
	
	// 함수형 프로그래밍 자체가 데이터처럼 고정시키려는 것이 기본 개념이기 때문에 상수화시키는 것
	// 따라서 다음과 같이 전역 변수를 캡처하려고 하면 컴파일 에러가 발생한다
	//[globalVar1]()
	//{
	//	cout << globalVar1 << endl;
	//};

	[a_0519]() mutable
	{
		a_0519++;	// mutable를 쓰면 a_0519를 상수화하지 않으므로 에러 발생 안 함
		cout << a_0519 << endl;
	};

	// 람다 예제
	[]() -> void {cout << "Hello World!" << endl; }();
	cout << []() -> string {return "Hello World!!"; }();
	cout << endl;
	cout << [&a_0519](auto i) { a_0519 = i; return a_0519; }(11);
	cout << endl;

	// level이 10보타 크면 "yes", 작으면 "no"를 출력하는 람다식
	int level = 1;
	cout << [level]() -> string {
		if (level > 10) return "yes";
		else return "no";
	}() << endl;


	vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//for_each(begin(v), end(v), [&](const int& i) {cout <<  i; }); cout << endl;
	//for_each(begin(v), end(v), [&](const int& i) { if(i % 2 == 0) cout << i; }); cout << endl;
	//for_each(begin(v), end(v), [&](int& i) {cout << i; });
	//for_each(v.begin(), v.end(), [&](auto n) { cout << n; });

	// 함수를 보관(...)하는 벡터 예제
	vector< function<const char* ()> > v_func;
	// 함수를 람다식으로 저장
	v_func.push_back([] { return "대한민국 "; });
	v_func.push_back([] { return "Korea "; });
	printf("%s %s\n", v_func[0](), v_func[1]());
	
	auto funcRet = FunctionReturn();
	funcRet();

	// ========== 템플릿과 람다 ==========
	auto funcTemplate = [] {cout << "Hello World!!!" << endl; };
	TemplateFunc(funcTemplate);

	// sort
	

	return 0;
}

function<void()> FunctionReturn()
{
	return []() { cout << "FunctionReturn!!" << endl; };
}

template<typename TFunc>
void TemplateFunc(TFunc func)
{
	func();
}

//자바스크립트 예제
//
//	//------------------------------------------------------------------------
//	function outerFunc() {
//	  var x = 10;
//	  var innerFunc = function () { console.log(x); };
//	  return innerFunc;
//	}
//	outerFunc(); // 10
//
//	//  함수 outerFunc를 호출하면 내부 함수 innerFunc가 반환된다.
//	//  그리고 함수 outerFunc의 실행 컨텍스트는 소멸한다.
//
//	function outerFunc() {
//	  var x = 10;
//	  var innerFunc = function () { console.log(x); };
//	  return innerFunc;
//	}
//	var inner = outerFunc();
//	inner(); // 10
//
//	이처럼 자신을 포함하고 있는 외부함수보다 내부함수가 더 오래 유지되는 경우, 외부 함수 밖에서 내부함수가 호출되더라도 외부함수의 지역 변수에 접근할 수 있는데 
//	이러한 함수를 클로저(Closure)라고 부른다.
//	즉, 클로저는 자신이 생성될 때의 환경(Lexical environment)을 기억하는 함수다
//
//	클로저의 활용
//		현재 상태를 기억하고 변경된 최신 상태를 유지
//		전역 변수의 사용 억제
//		정보의 은닉
//
//	고차함수란?
//	고차함수란 매개변수로 함수를 갖는 함수입니다. 
//		고차함수를 사용하게 되면 함수의 내부 코드를 건드리지 않고도 외부에서 실행 흐름을 추가할 수 있어 
//		함수의 재활용성, 재사용성 의 이점을 얻을 수 있습니다.
