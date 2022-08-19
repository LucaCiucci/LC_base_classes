
#include <catch2/catch_test_macros.hpp>

#include <LC/utils/ScopeGuard.hpp>

TEST_CASE("lc::ScopeGuard") {

	SECTION("functionality") {
		bool cleaned = false;

		{
			SCOPE_GUARD([&]() { cleaned = true; });
			REQUIRE_FALSE(cleaned);
		}

		REQUIRE(cleaned);
	}

	SECTION("dismiss") {
		bool cleaned = false;

		{
			lc::ScopeGuard guard([&] { cleaned = true; });
			guard.dismiss();
			REQUIRE_FALSE(cleaned);
		}

		REQUIRE_FALSE(cleaned);

		cleaned = false;

		{
			lc::ScopeGuard guard([&] { cleaned = true; });
			guard.reset();
			REQUIRE_FALSE(cleaned);
		}

		REQUIRE_FALSE(cleaned);
	}

	SECTION("reset") {
		bool cleaned = false;

		{
			lc::ScopeGuard guard([] {});
			guard.reset([&] { cleaned = true; });
			REQUIRE_FALSE(cleaned);
		}

		REQUIRE(cleaned);
	}
}
