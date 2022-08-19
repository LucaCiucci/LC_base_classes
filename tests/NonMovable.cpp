
#include <concepts>

#include <catch2/catch_test_macros.hpp>

#include <LC/utils/NonMovable.hpp>

namespace {
	template <class T>
	concept copy_constructible_but_not_movable =
		std::constructible_from<T, T&> && std::convertible_to<T&, T> &&
		std::constructible_from<T, const T&> && std::convertible_to<const T&, T>&&
		std::constructible_from<T, const T> && std::convertible_to<const T, T> &&
		!std::constructible_from<T, T&&>;

	template <class T>
	concept copyable_but_not_movable =
		std::assignable_from<T&, T&> &&
		std::assignable_from<T&, const T&> &&
		std::assignable_from<T&, const T> &&
		!std::assignable_from<T&, T&&>;

	// https://stackoverflow.com/questions/1107948/test-whether-a-class-is-polymorphic
	template <class T>
	concept is_polymorphic = std::is_polymorphic_v<T>;
}


TEST_CASE("lc::NonMovable") {

	REQUIRE_FALSE(is_polymorphic<lc::NonMovable>);
	

	SECTION("lc::NonMovable properties") {
		REQUIRE(std::is_constructible_v<lc::NonMovable> == true);
		REQUIRE(std::is_trivially_constructible_v<lc::NonMovable> == true);
		//REQUIRE(std::is_assignable_v<lc::NonCopyable> == false);
		//REQUIRE(std::is_trivially_assignable_v<lc::NonCopyable> == false);	

		// see also

		REQUIRE(std::destructible<lc::NonMovable> == true);

		//REQUIRE(std::swappable<lc::NonMovable> == true);

		REQUIRE(std::default_initializable<lc::NonMovable> == true);

		// NonCopyable objects can be moved by default
		REQUIRE(std::move_constructible<lc::NonMovable> == false);

		// false since it requires move_constructible
		REQUIRE(std::copy_constructible<lc::NonMovable> == false);

		REQUIRE(copy_constructible_but_not_movable<lc::NonMovable> == true);

		// false since it requires movable
		REQUIRE(std::copyable<lc::NonMovable> == false);

		REQUIRE(copyable_but_not_movable<lc::NonMovable> == true);

		REQUIRE(std::movable<lc::NonMovable> == false);
	}
	
}