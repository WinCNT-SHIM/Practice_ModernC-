#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <map>
#include <algorithm> //for_each

#include <functional>

using namespace std;

/// <summary>
/// ========== ���� �Լ� Lambda ==========
///   �͸� �Լ�(Anoymous Function), �Լ��� ���� �ܼ��ϰ� ǥ���ϴ� ���
///   �ڵ带 ������ó�� ����Ѵ�(�Լ� ������ ��ſ� �Ű� ������ ����, ����)
///   ����: �ڵ��� ������(define�� ���� ���� �� �ʿ� ����),
///         ���� ������ ���� �����ս� ���
///         ���ͷ��̼� ���� �ڵ带 �����ϴ� �� �־ ���ʿ��� �κ��� ������ �� �ִ�
///   ����: ���� ����ȭ ����
///         ����� �� �ݽ��� ������ ��ƴ�
///         (�׷��� ���� ������ �Լ��� ���ٷ� ������ ����)
/// 
/// ���� �Լ� ǥ����(expression)
///   �Ϲ����� ǥ����
///     [capture list] (�޴� ����) -> ���� Ÿ�� { �Լ� ��ü }
/// 
///   ���� Ÿ���� ������ ���
///     [capture list] (�޴� ����) { �Լ� ��ü }
/// 
///   ��� ����
///     [capture list] (�޴� ����) { �Լ� ��ü } (���� ����)
/// 
/// []  lambda capture ����, �ܺ� ������ ������
/// ()  parameter list ����
///    + mutable : ĸó ����Ʈ�� �Ѿ���� ���� ������� �˸�
/// {}  body ����
/// ()  lambda �Լ��� ��������� ȣ���� ��
/// 
/// 
/// ========== [] ĸó ��� ==========
/// �ܺ� ������ ���(ĸó)�Ѵ�, ��������� ǥ���ϱ� ������ �˱� ��������
/// [x]  : �� ����� ������
/// [&x] : �� ������ ������
/// [=]  : {body ����}�� ��� �������� �� ����� ĸó�Ѵ�
/// [&]  : {body ����}�� ��� �������� �� ������ ĸó�Ѵ�
/// 
/// ����) ��� �� ���� �ִ�
/// [=, &x, &y]
/// [&, y]
/// [&, &y] : ���� ����
/// [this]  : ��ü�� �����ϴ� ������, "this->"�� ��� �����Ѵ�
/// 
/// 
/// �����͵� �Լ�(�ڵ�)�� ������ ���̳ʸ��� �޸� ������ ����ȴ�
/// �׷� �Լ� ��ü�� �����ͷ� ����ϸ� ���?
/// 
/// ========== �Լ��� ���α׷���(Functional Programming) ==========
/// ���α׷��� �з�����
///   ����� ���α׷��� : ����(What)�� ���� ��Ÿ���⺸�� ���(How) ���� �����ϴ� ���
///     ���� ���� ���α׷��� : ����Ǿ�� �� �������� ó�� ������ �����ϴ� ���
///     ��ü ���� ���α׷��� : ��ü���� �������� ���α׷��� ��ȣ �ۿ��� ǥ��
///   
///   ������ ���α׷��� : ��� �Ұ���(How)�� ��Ÿ���⺸�� ����(What)�� �� ������ �����ϴ� ���
///     �Լ��� ���α׷��� : ���� �Լ��� �����ϰ� ����Ʈ��� ����� ���(Ŭ����, �Ͻ���, ������)
/// 
/// ��ü ���� ���α׷��� - OOP
///   ���α׷��ֿ��� �ʿ��� �����͸� �߻�ȭ���� ���¿� ������ ���� ��ü�� �����
///   �� ��ü�� ���� �������� ��ȣ �ۿ��� ���� ������ ����
///     �߻�ȭ, ĸ��ȭ, ���� ����, ��Ӽ�, ������ ���� Ư¡
/// 
/// �Լ��� ���α׷��� - Functional Programing
///   �ڷ� ó���� ������ �Լ��� ������� ����ϰ� ���¿� ���� �����͸� �ָ��ϴ� ���α׷��� �з�����
///   ���� �Լ��� �����ϰ�, ���� ���³� ���� ������ ������ �� ���ۿ��� ���Ͽ�
///   ���� �Լ�(Pure Function), �Һ���(Immutable), ���� ����(Referential Transparency), ������ ��(Lazy Evaluation) ���� Ư¡
/// 
///   �Լ��� ������ ��üó�� �����ͷ� �ٷ�� ���(C++11������ ���ٸ� ����)
/// 
/// �ֱ� ������ ĸ��ȭ�� ��Ӱ��� ����� ��� ����
/// 
/// </summary>

void func		// �Լ� �̸�
(int a)			// �Լ� �Էº�
{ cout << a; }	// �Լ� ������

// ���� �Լ� ǥ����
//[]					// �Լ� �̸��� ���ְ� ĸ�ĺθ� ���
//(int a)				// �Լ� �Էº�
//void { cout << a; }	// ���� Ÿ�԰� �Լ� ������

/// <summary>
/// ���� ǥ���� �ֱ� �������� Ŭ������ �������
/// (Ŭ������� ��)
/// ������ ���� ���ǰ� Ŀ���� ������ ���� ǥ������ ���Դ�
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
// �� �Լ��� ���� ǥ������ ��ȯ�ϸ� ������ ����
// []() { cout << "Hello World" << endl; };
// [](int x) { cout << x << endl; };
// [](int x) { if (x < 0) return -x; return x; };
// [](int x) { return x % 2; };
// [](int x, int y) { return x + y; };

int globalVar1 = 1;

function<void()> FunctionReturn();
template<typename TFunc>
void TemplateFunc(TFunc func);

auto multipleVal(int x)
{
	return [x] {return 2 * x; };
}

int main()
{
	int a = 0;	// ������
	func(a);	// �ڵ�(���), �Լ�(�����͸� �����ϴ� �ڵ带 ���)

	// �ڵ� --> ������
	auto Lambda1 = [](int a) -> void { cout << a; };
	// Lambda1�� �Լ��� ��� ����...�� �Լ�ó�� ����ϸ� �ȴ�
	Lambda1(a);

	auto Lambda2 = [](int a) { cout << a; };

	// ���� ǥ���� �ֱ� ��
	// Ư�� ���� ���ϴ� ����� Ŭ������ �������
	Plus plus3{ 3 };	// �־��� ���� 3�� ���ϴ� ����� ������ Ŭ����
	Plus plus5{ 5 };	// �־��� ���� 5�� ���ϴ� ����� ������ Ŭ����
	// plus3, plus5�� ������ó�� ��������, �� ����ó�� ����� �� ����
	// �̷��� ���� Ŭ������� �Ѵ�
	cout << plus3(5) << endl;
	cout << plus5(5) << endl;

	// ���� ��� ����
	int a1 = Add(1, 2);
	int a2 = [](int x, int y) { return x + y; }(1, 2);
	cout << "a2: " << a2 << endl;

	bool b1 = isEven(1);
	bool b2 = [](int x) { return x % 2; }(1);
	cout << "b2: " << b2 << endl;

	// ========== ����� ǥ���� 3���� ==========
	
	// ���ٽ����� ����ó�� �����ؼ� ���
	// �Լ� ��ü���� �����ϰ� ����� �� �ִ�, �ӵ��� ������
	// (�Լ� ��ü�� �̸� �����ؼ� ���)
	auto f1 = [](int x, int y) { return x + y; };
	cout << "f1: " << f1(1, 2) << endl;

	// 3. �Լ� ��ü(Function Object) Ư�� ������ �ڵ带 ����
	// #include <functional> �ʿ�
	// function<    > ����
	// C++������ ���ٽĵ� Ŭ������ �����Ǿ� �ֱ� ������ ��� ���� ����
	// �Ϲ������� �̸� �����ؼ� ����� �� �ִ�
	function<int(int, int)> f2 = Add;
	// �Լ� ��ü�� ���ٸ� ���� ���� �ִ�(...)
	function<int(int, int)> f2_2 = [](int x, int y) { return x + y; };
	cout << "f2: " << f2(1, 2) << endl;
	cout << "f2_2: " << f2_2(1, 2) << endl;

	// ���� - �Լ� ��ü�� �Լ� �����Ϳʹ� �ٸ� ��
	// �Լ� ��ü ���� �� ������ ���� �� �ְ�(Ŭ�����̱� ����)
	// Ȯ�强�� �ξ� ����
	int (*f3)(int x, int y) = Add;
	cout << "f3: " << f3(1, 2) << endl;


	/// ========== [] ĸó ��� ==========
	auto a_0519 = 1;

	//[a_0519]()
	//{
	//	a_0519++;	// mutable�� ������ a_0519�� ����� ���ͼ� ������ �߻��Ѵ�
	//	cout << a_0519 << endl;
	//};
	
	// �Լ��� ���α׷��� ��ü�� ������ó�� ������Ű���� ���� �⺻ �����̱� ������ ���ȭ��Ű�� ��
	// ���� ������ ���� ���� ������ ĸó�Ϸ��� �ϸ� ������ ������ �߻��Ѵ�
	//[globalVar1]()
	//{
	//	cout << globalVar1 << endl;
	//};

	[a_0519]() mutable
	{
		a_0519++;	// mutable�� ���� a_0519�� ���ȭ���� �����Ƿ� ���� �߻� �� ��
		cout << a_0519 << endl;
	};

	// ���� ����
	[]() -> void {cout << "Hello World!" << endl; }();
	cout << []() -> string {return "Hello World!!"; }();
	cout << endl;
	cout << [&a_0519](auto i) { a_0519 = i; return a_0519; }(11);
	cout << endl;

	// level�� 10��Ÿ ũ�� "yes", ������ "no"�� ����ϴ� ���ٽ�
	int level = 1;
	cout << [level]() -> string {
		if (level > 10) return "yes";
		else return "no";
	}() << endl;


	vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for_each(begin(v), end(v), [&](const int& i) { cout << i; }); cout << endl;
	for_each(begin(v), end(v), [&](const int& i) { if(i % 2 == 0) cout << i; }); cout << endl;
	for_each(begin(v), end(v), [&](int& i) { cout << i; }); cout << endl;
	for_each(v.begin(), v.end(), [&](auto n) { cout << n; }); cout << endl;

	// �Լ��� ����(...)�ϴ� ���� ����
	vector< function<const char* ()> > v_func;
	// �Լ��� ���ٽ����� ����
	v_func.push_back([] { return "���ѹα� "; });
	v_func.push_back([] { return "Korea "; });
	printf("%s %s\n", v_func[0](), v_func[1]());
	
	auto funcRet = FunctionReturn();
	funcRet();

	// ========== ���ø��� ���� ==========
	auto funcTemplate = [] {cout << "Hello World!!!" << endl; };
	TemplateFunc(funcTemplate);

	// sort
	vector<int> v_int;
	for (int i = 0; i < 1000000; ++i) { v_int.push_back(rand() % 2000); }
	sort(v_int.begin(), v_int.end(), [](int& a, int& b)-> bool {return a > b; });
	cout << endl;

	// ========== ���ٽ��� ���� ���� ==========
	cout << "========== ���ٽ��� ���� ���� ==========" << endl;
	int ex_val = 5;

	auto _LambdaFunc = [ex_val]() mutable { ex_val *= 5; return ex_val; };
	cout << "val: " << ex_val << endl; // 5, ���ٽ��� �������� �ʾұ� ����

	ex_val = 10;
	cout << "val * 5: " << _LambdaFunc() << endl; // 25
	// ĸó�� ���¿����� ���ٽ��� ����(���� ����)�Ǿ��� ����(50 �ƴ�!)
	//auto closureFunc = [a, b](int x) {cout << a * x + b << endl; };

	// ========== ���ٽ� ���� ==========
	// 6.ĸó ���� ����Ʈ�� Const�ε� �̸� �����ϰ� ���� �����ϰ��� �� ��
	// mutable Ű����

	// 7. ĸó �� ���(���۷���)
	int value4 = 40;
	auto lambda7 = [&value4] { value4 += 10; cout << "07: " << value4 << endl; };
	//lambda7();	// ����Ǿ�� �����
	cout << "07: " << value4 << endl;
	// ������ Ư�� ��, ���۷����� ������� �ʵ��� ����!!!�ؾ� �Ѵ�


	// 8. ���׸� ���� ����(C==14, �Ķ���� i�� auto�� ����)
	int value5 = 50;
	auto lambda8 = [](auto i) { return i > 100; };
	cout << "08: " << lambda8(value5) << endl;

	auto Add8 = [](auto a, auto b) { return a + b; };


	// 9-1. ĸó �� �� �ʱ�ȭ(Init Capture) C++14
	int value6 = 60;
	auto lambda9 = [myVal = "My Value: ", value6] { 
		cout << "9 : " << myVal << ", Value : " << myVal << endl;
	};
	lambda9();
	// ������ �ܺ� �������� ���輺�� ���� ���� ���
	auto lambda9_1 = [myVal = value6]{
		cout << "9-1 : " << myVal << ", Value : " << myVal << endl;
	};
	lambda9_1();

	// 9-2. unique_ptr�� value�δ� �⺻������ ���簡 ���� ������...move�δ� ����
	auto valuePrt = make_unique<int>(70);
	auto lambda9_2 = [p = move(valuePrt)]{ cout << "9-2 : " << *p << endl; };
	lambda9_2();
	

	//10. ���� Ÿ�����ν��� ���� ���� --> ���縦 �Լ� ��üó�� ��� ����
	function<int(void)> fn10 = ::multipleVal(10);
	cout << "10: fn10() : " << fn10() << endl;
	auto fn10_2 = ::multipleVal(20);
	cout << "10 : fn10_2() : " << fn10_2() << endl;


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

//�ڹٽ�ũ��Ʈ ����
//
//	//------------------------------------------------------------------------
//	function outerFunc() {
//	  var x = 10;
//	  var innerFunc = function () { console.log(x); };
//	  return innerFunc;
//	}
//	outerFunc(); // 10
//
//	//  �Լ� outerFunc�� ȣ���ϸ� ���� �Լ� innerFunc�� ��ȯ�ȴ�.
//	//  �׸��� �Լ� outerFunc�� ���� ���ؽ�Ʈ�� �Ҹ��Ѵ�.
//
//	function outerFunc() {
//	  var x = 10;
//	  var innerFunc = function () { console.log(x); };
//	  return innerFunc;
//	}
//	var inner = outerFunc();
//	inner(); // 10
//
//	��ó�� �ڽ��� �����ϰ� �ִ� �ܺ��Լ����� �����Լ��� �� ���� �����Ǵ� ���, �ܺ� �Լ� �ۿ��� �����Լ��� ȣ��Ǵ��� �ܺ��Լ��� ���� ������ ������ �� �ִµ� 
//	�̷��� �Լ��� Ŭ����(Closure)��� �θ���.
//	��, Ŭ������ �ڽ��� ������ ���� ȯ��(Lexical environment)�� ����ϴ� �Լ���
//
//	Ŭ������ Ȱ��
//		���� ���¸� ����ϰ� ����� �ֽ� ���¸� ����
//		���� ������ ��� ����
//		������ ����
//
//	�����Լ���?
//	�����Լ��� �Ű������� �Լ��� ���� �Լ��Դϴ�. 
//		�����Լ��� ����ϰ� �Ǹ� �Լ��� ���� �ڵ带 �ǵ帮�� �ʰ� �ܺο��� ���� �帧�� �߰��� �� �־� 
//		�Լ��� ��Ȱ�뼺, ���뼺 �� ������ ���� �� �ֽ��ϴ�.
