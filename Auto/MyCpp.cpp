#include <iostream>
#include <vector>

int add(int x, int y) { return x + y; }
auto addRetAuto(int x, int y) { return x + y; } // C++ 18 즈음에 가능해짐

class Cat
{
	std::string name = "";
	int age = 0;
public:
	Cat(std::string s, int n) { name = 5; age = n; }
};

int main()
{
	/// <summary>
	/// C언어는 운영 체제(유닉스)를 만들기 위해 만든 언어
	/// 자료형도 운영 체제 제작 시, 프로그래머의 실수를 알 수 있도록 만들어 진 것
	/// 자료형으로 데이터들을 구분하면, 컴파일 에러 등으로 버그를 미리 파악할 수 있게 되고
	/// 결과적으로 런타임 에러를 줄일 수 있게 된 것이다
	/// 그러므로 프로그래밍할 때의 원칙은 자료형을 명확하게 하는 것이라 할 수 있다
	/// 
	/// 반대로, 타입을 맞출 필요가 없는 경우에는 auto를 사용하여 생산성을 높일 수 있다
	/// 함수의 리턴 값을 auto로 받거나(C++ 18부터는 리턴에 auto 사용이 가능해짐),
	/// 긴 자료형을 축약하거나(std 사용 시 편리함) 등등
	/// </summary>
	/// <returns></returns>
	long a = 0L;
	auto i = 1 + 2;

	auto i2 = 0.123;
	int size = sizeof(i2);
	std::cout << i2 << " " << size << std::endl;

	// auto를 쓰다가 버그가 발생하는 예
	unsigned char x = 1;
	auto xAuto = x;					// 컴파일 타임에 자료형 결정
	xAuto = 1.3;					// unsigned char에 1.3을 지정하고 있음
	printf("%d %f \n", x, xAuto);	// 1 0.0000 --> unsigned char와 %f의 출력 형식이 다르므로 0.000이 출력

	// return 값을 auto로 받을 수 있다
	auto sum = add(3, 5);

	// auto는 포인터나 참조 타입을 붙일 수 있다(코드가 명확해짐)
	Cat* myCat = new Cat("CoCo", 2);
	auto* myCatPtr = myCat;
	auto& myCatRef = myCat;

	// 마찬가지로 auto에는 const 값을 붙일 수 있다(코드가 명확해짐)
	const int b = 1;
	const auto& a1 = b;

	// std 사용 시 auto를 사용하면 편리하다(특히 iterator)
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	//for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {}
	for (auto it = v.begin(); it != v.end(); ++it){ }

	// 템플릿을 사용한 클래스 등에 auto을 사용하면 축약할 수 있다
	// MyArr<int>* a = new MyArr<int>(10);
	// auto* a = new MyArr<int>(10);

	// 함수 포인터
	// 함수 이름을 (*함수명)으로 설명하면 됨
	// int (*funcPtr)(int, int);
	// 함수 포인터의 선언은 복잡하기에 auto를 사용하면 편하다
	auto fp = add;
	auto result = fp(1, 2);
}