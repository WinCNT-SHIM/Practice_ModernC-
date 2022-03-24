#include <iostream>
#include <string>
#include <vector>

using namespace std;

//int sumArray(int array[]) // int array[] == int* array
int sumArray(vector<int> array)
{
	int sum = 0;
	//for (const auto& num : array) // error
	for (const auto& num : array) // error
		sum += num;
	return sum;
}

int main()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };

	// 일반 for문
	for (size_t i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}

	// 범위 기반 for문
	for (int elem : arr)
	{
		cout << elem << endl;
	}

	// auto를 이용한 범위 기반 for문
	for (auto elem : arr)
	{
		cout << elem << endl;
	}

	// arr을 복사하지 않고 접근만 하는 for문
	for (const auto& elem : arr)
	{
		cout << elem << endl;
	}

	const int num = 5;
	int scores[num] = { 84, 92, 76, 81, 56 };

	int maxScore = 0;
	//for (int i = 0; i < num; ++i)
	//	if (scores[i] > maxScore)
	//		maxScore = scores[i];
	for (const auto& elem : scores)
		if (elem > maxScore)
			maxScore = elem;
	cout << "The best score was " << maxScore << endl;

	
	// ==================== 피보나치 ====================
	//vector<int> fibo = {};
	//for (const auto&n : fibo)

	// ==================== iter ====================
	vector<int> v = { 1,2,3,4,5,6,7,8,9 };
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		*iter += 10;
	}
	for (int elem : v) cout << elem << " ";
	cout << endl;

	for (auto& elem : v)
	{
		elem += 100;
	}
	for (int elem : v) cout << elem << " ";


	// ==================== 포인터와 범위 기반 for문 ====================
	// 배열의 크기를 알 수 없으므로 포인터에 사용 불가
	//int* buff = new int[10];
	//for (auto x : buff) x = 0;

	// 동적 기반 배열에 범위 기반 for문을 사용하고 싶을 경우는 vector를 쓰자
	vector<int> buff(10);
	for (auto x : buff) x = 0;
}