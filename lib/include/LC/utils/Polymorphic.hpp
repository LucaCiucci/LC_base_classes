/*LC_NOTICE_BEGIN
LC_NOTICE_END*/

#pragma once

#if __cpp_concepts
	#include <concepts>
#endif

namespace lc
{
	// A very simple class with a virtual destructor.
	// You can use this calss for your own abstract classes so that
	// all of them can be accessed using an abstrat pointer (`Abstract*`)
	// and then you can use `dynamic_cast` to cast it to the correct type.
	//
	// Example:
	// ```cpp
	// class SomeClass : LCAbstract {};
	// class SomeVeryDifferentClass : LCAbstract {};
	// 
	// auto isSomeVeryDifferentClass = [](lc::Abstract* abstract) {
	//     return dynamic_cast<SomeVeryDifferentClass*>(abstract) != nullptr;
	// };
	// 
	// lc::Abstract* some_pointer = new SomeClass();
	// lc::Abstract* some_other_pointer = new SomeVeryDifferentClass();
	// 
	// std::cout << "Is some_pointer a SomeVeryDifferentClass? " << (isSomeVeryDifferentClass(some_pointer) ? "Yes" : "No") << std::endl;
	// std::cout << "Is some_other_pointer a SomeVeryDifferentClass? " << (isSomeVeryDifferentClass(some_other_pointer) ? "Yes" : "No") << std::endl;
	// ```
	// output:
	// ```
	// Is some_pointer a SomeVeryDifferentClass? No
	// Is some_other_pointer a SomeVeryDifferentClass? Yes
	// ```
	class Polymorphic
	{
	public:

		// https://www.geeksforgeeks.org/pure-virtual-destructor-c/
		virtual ~Polymorphic() = 0;
		
	private:
	};
	Polymorphic::~Polymorphic() // Explicit destructor call
	{
	}

#if __cpp_concepts
	template <class T>
	concept lc_polymorphic = std::derived_from<T, Polymorphic>;
#endif
}

#define LCPolymorphic public virtual ::lc::Polymorphic