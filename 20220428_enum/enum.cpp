#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

/// <summary>
/// enum
/// ���� ���� enum���� ���� �ִ� enum�� �������
///   ���� ����(unscoped) enum - C++98 ��Ÿ���� enum
///   ���� �ִ�(scoped) enum - C++11�� ���ο� ������, enum class��� �������� ������
/// </summary>

// �ֽ� ������ enum class�� ���� ������ ����
// (Ÿ�Ե� ���� ����)
enum class Status : std::uint8_t;

using UserInfo = tuple<string, string, size_t>;
enum UserInfoFields { uiName, uiEmail, uiReputation };

int main(void)
{
	//enum Color { black, white, red };
	// �ʿ� ǥ������ �����Ƿ� �����Ϸ��� Color�� char�� ����Ѵ�

	enum class Color { black, white, red };
	//auto white = false;		// white�� enum? ���� ����?
	// enum class�� ����ϸ� Ȯ��������
	auto white = false;
	Color::white;

	Color c1 = Color::white;
	auto c1 = Color::white;

	//Color c = red;		// ������ ����

	// ==================== ���� ���� enum�� Ȱ�� �� ====================
	// pair�� Ȯ����, n���� ���� ����
	tuple<int, double> my_tp = make_tuple(1, 1.2);

	auto v1 = get<0>(my_tp);	// 1
	auto v2 = get<1>(my_tp);	// 1.2

	UserInfo uInfo;
	auto val1 = get<1>(uInfo);
	auto val2 = get<uiEmail>(uInfo);	// �ڵ带 �˱� ���� �ϱ� ���� ���

	// enum class�� ���� �ʹ� ����������
	enum class UserInfoFields { uiName, uiEmail, uiReputation };
	auto val2 = get<static_cast<size_t>(UserInfoFields::uiReputation)>(uInfo);

	// C++17���ʹ� ����?
	//auto [a, b] = make_tuple(2, 0.5);

	return 0;
}