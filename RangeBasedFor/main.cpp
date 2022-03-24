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

	// �Ϲ� for��
	for (size_t i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}

	// ���� ��� for��
	for (int elem : arr)
	{
		cout << elem << endl;
	}

	// auto�� �̿��� ���� ��� for��
	for (auto elem : arr)
	{
		cout << elem << endl;
	}

	// arr�� �������� �ʰ� ���ٸ� �ϴ� for��
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

	
	// ==================== �Ǻ���ġ ====================
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


	// ==================== �����Ϳ� ���� ��� for�� ====================
	// �迭�� ũ�⸦ �� �� �����Ƿ� �����Ϳ� ��� �Ұ�
	//int* buff = new int[10];
	//for (auto x : buff) x = 0;

	// ���� ��� �迭�� ���� ��� for���� ����ϰ� ���� ���� vector�� ����
	vector<int> buff(10);
	for (auto x : buff) x = 0;
}