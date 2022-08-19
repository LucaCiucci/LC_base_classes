
#include <concepts>

#include <catch2/catch_test_macros.hpp>

#include <LC/utils/NonCopyable.hpp>

namespace {
	// https://stackoverflow.com/questions/1107948/test-whether-a-class-is-polymorphic
	template <class T>
	concept is_polymorphic = std::is_polymorphic_v<T>;
}


TEST_CASE("lc::NonCopyable", "[non - copyiable]") {

	SECTION("lc::NonCopyable properties") {
		REQUIRE(std::is_constructible_v<lc::NonCopyable> == true);
		REQUIRE(std::is_trivially_constructible_v<lc::NonCopyable> == true);
		//REQUIRE(std::is_assignable_v<lc::NonCopyable> == false);
		//REQUIRE(std::is_trivially_assignable_v<lc::NonCopyable> == false);	

		// see also

		REQUIRE(std::destructible<lc::NonCopyable> == true);
		
		//REQUIRE(std::swappable<lc::NonCopyable> == true);
		
		REQUIRE(std::default_initializable<lc::NonCopyable> == true);

		// NonCopyable objects can be moved by default
		REQUIRE(std::move_constructible<lc::NonCopyable> == true);

		REQUIRE(std::copy_constructible<lc::NonCopyable> == false);

		REQUIRE(std::copyable<lc::NonCopyable> == false);
		
		// TODO see NonMovable
		// REQUIRE(std::movable<lc::NonCopyable> == true);
	}

	SECTION("derivation") {
		class Copyable {};
		class NonCopyable : LCNonCopyable {};

		REQUIRE(std::copyable<Copyable> == true);
		REQUIRE(std::copyable<NonCopyable> == false);
	}
}