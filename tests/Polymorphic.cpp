
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include <LC/utils/Polymorphic.hpp>


namespace {
	template <class T>
	concept is_abstract = std::is_abstract_v<T>;
	
	template <class T>
	concept has_virtual_destructor = std::has_virtual_destructor_v<T>;

	template <class T>
	concept derived_from_lc_polymorphic = std::is_base_of_v<lc::Polymorphic, T>;

	// https://stackoverflow.com/questions/1107948/test-whether-a-class-is-polymorphic
	template <class T>
	concept is_polymorphic = std::is_polymorphic_v<T>;
}

TEST_CASE("lc::Polymorphic", "[Polymorphic]") {

	using namespace lc;

	REQUIRE(has_virtual_destructor<Polymorphic> == true);
	REQUIRE(is_abstract<Polymorphic> == true);

	class NonPolymorphicClass {};
	class BasicPolymorphicClass { virtual void f() {}; };
	class BasicAbstractClass { virtual void f() = 0; };

	class SomeClass : LCPolymorphic { virtual void f() {}; };
	class SomeVeryDifferentClass : LCPolymorphic {};

	SECTION("derivation from lc::Polymorphic") {
		REQUIRE(derived_from_lc_polymorphic<NonPolymorphicClass> == false);
		REQUIRE(derived_from_lc_polymorphic<BasicPolymorphicClass> == false);
		REQUIRE(derived_from_lc_polymorphic<BasicAbstractClass> == false);

		REQUIRE(derived_from_lc_polymorphic<SomeClass> == true);
		REQUIRE(derived_from_lc_polymorphic<SomeVeryDifferentClass> == true);
	}

	SECTION("polimorphism") {
		REQUIRE(is_polymorphic<NonPolymorphicClass> == false);
		REQUIRE(is_polymorphic<BasicPolymorphicClass> == true);
		REQUIRE(is_polymorphic<BasicAbstractClass> == true);

		REQUIRE(is_polymorphic<SomeClass> == true);
		REQUIRE(is_polymorphic<SomeVeryDifferentClass> == true);
	}

	SECTION("destruct virtuality") {
		REQUIRE(has_virtual_destructor<NonPolymorphicClass> == false);
		REQUIRE(has_virtual_destructor<BasicPolymorphicClass> == false);
		REQUIRE(has_virtual_destructor<BasicAbstractClass> == false);

		REQUIRE(has_virtual_destructor<SomeClass> == true);
		REQUIRE(has_virtual_destructor<SomeVeryDifferentClass> == true);
	}

	SECTION("Abstract") {
		REQUIRE(is_abstract<NonPolymorphicClass> == false);
		REQUIRE(is_abstract<BasicPolymorphicClass> == false);
		REQUIRE(is_abstract<BasicAbstractClass> == true);

		REQUIRE(is_abstract<SomeClass> == false);
		REQUIRE(is_abstract<SomeVeryDifferentClass> == false);
	}

	SECTION("dynamic_cast") {
		auto isSomeVeryDifferentClass = [](lc::Polymorphic* polymorphic) {
			return dynamic_cast<SomeVeryDifferentClass*>(polymorphic) != nullptr;
		};

		lc::Polymorphic* some_pointer = new SomeClass();
		lc::Polymorphic* some_other_pointer = new SomeVeryDifferentClass();

		REQUIRE(isSomeVeryDifferentClass(some_pointer) == false);
		REQUIRE(isSomeVeryDifferentClass(some_other_pointer) == true);	
	}

	SECTION("implicit destructor override") {

		bool destructed = false;

		struct EnsureDestructor {
			bool& destructed;
			EnsureDestructor(bool& destructed) : destructed(destructed) {}
			~EnsureDestructor() { destructed = true; }
		};

		struct SomeClass : LCPolymorphic
		{
			SomeClass(bool& destructed) : destructorChecker(destructed) {}
			EnsureDestructor destructorChecker;
		};
		
		Polymorphic* a = new SomeClass(destructed);
		delete a;
		REQUIRE(destructed);
	}
}