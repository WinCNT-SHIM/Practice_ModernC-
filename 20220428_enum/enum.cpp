#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

/// <summary>
/// enum
/// 범위 없는 enum보다 범위 있는 enum을 사용하자
///   범위 없는(unscoped) enum - C++98 스타일의 enum
///   범위 있는(scoped) enum - C++11의 새로운 열거형, enum class라는 구문으로 선언함
/// </summary>

// 최신 버전은 enum class의 전방 선언이 가능
// (타입도 지정 가능)
enum class Status : std::uint8_t;

using UserInfo = tuple<string, string, size_t>;
enum UserInfoFields { uiName, uiEmail, uiReputation };

int main(void)
{
	//enum Color { black, white, red };
	// 필요 표현량이 적으므로 컴파일러는 Color를 char로 취급한다

	enum class Color { black, white, red };
	//auto white = false;		// white는 enum? 지역 변수?
	// enum class를 사용하면 확실해진다
	auto white = false;
	Color::white;

	Color c1 = Color::white;
	auto c1 = Color::white;

	//Color c = red;		// 컴파일 오류

	// ==================== 범위 없는 enum의 활용 예 ====================
	// pair의 확장형, n개의 묶음 가능
	tuple<int, double> my_tp = make_tuple(1, 1.2);

	auto v1 = get<0>(my_tp);	// 1
	auto v2 = get<1>(my_tp);	// 1.2

	UserInfo uInfo;
	auto val1 = get<1>(uInfo);
	auto val2 = get<uiEmail>(uInfo);	// 코드를 알기 쉽게 하기 위한 기법

	// enum class의 경우는 너무 복잡해진다
	enum class UserInfoFields { uiName, uiEmail, uiReputation };
	auto val2 = get<static_cast<size_t>(UserInfoFields::uiReputation)>(uInfo);

	// C++17부터는 가능?
	//auto [a, b] = make_tuple(2, 0.5);

	return 0;
}