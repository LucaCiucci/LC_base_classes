# LC_base_classes

This is an header only library defining some basic classes that might be of very frequent usage:
- `lc::Polymorphic`
- `lc::NonCopyale`
- `lc::NonMovable`
- `lc::ScopeGuard`

## `lc::Polymorphic`

This can be used as base class for your own classes that requires polymorphism, this ensure your class is polymorphic. For example, consider this class:
```cpp
class SomeClass {
public:
	virtual void f() {};
}
```

This class is polymorphic, we can do operations such as `dynamic_cast` with it, but what happens if, for some reason we decide to drop the `virtual` for `SomeClass::f`? Our code will break if we use `dynamic_cast` or similars with it.  
To solve this problem we could use:
```cpp
class SomeClass {
public:
	virtual ~SomeClass() {};
	// ...
}
```
This ensures that the class correctly has a virtual destructor and it will always be polymorphic, but we could do this in a simpler way:
```cpp
#include <LC/utils/Polymorphic.hpp>

class SomeClass : LCPolymorphic {};
// equivalent to:
class SomeClass : public virtual ::lc::Polymorphic {};
```
This will ensure that the class is polymorphic and that it has a virtual destructor.  
Note that the `LCPolymorphic` macro defines the `lc::Polymorphic` inheritance as "virtual", see [virtual inheritance](https://en.wikipedia.org/wiki/Virtual_inheritance) for a simple explanation (see also [this](https://isocpp.org/wiki/faq/multiple-inheritance) and [this](https://en.cppreference.com/w/cpp/language/derived_class#Virtual_base_classes)).

This patter may have some other usage, for example, you could use `lc::Polymorphic` to store pointers to very different objects, for example:
```cpp
using namespace std;
using namespace lc::Polymorphic;
using AnyVector = vector<shared_ptr<Polymorphic>>;

class Car : LCPolymorphic {};
class Dog : LCPolymorphic {};

AnyVector v;
v.push_back(make_shared<Car>());
v.push_back(make_shared<Dog>());

for (auto& e : v)
{
	if (auto car = dynamic_pointer_cast<Car>(e))
	{
		// ...
	}

	if (auto dog = dynamic_pointer_cast<Dog>(e))
	{
		// ...
	}
}
```

This technique can be used to replace `void*` pointer as "user data" storage method, for example consider:
```cpp
void set_callback_for_some_stuff(void (*fcn)(void* pData), void* pData);
```
in this specific case, we could replace the params with a simple `std::function`, but if we want to mantain this pattern, we could do:
```cpp
using lc::Polymorphic;
using PData = std::shared_ptr<Polymorphic>;
void set_callback_for_some_stuff(void (*fcn)(PData pData), PData);
```
in this way, we can perform runtime checks of <var>pData</var> validity.

### concepts:
The following concepts are defined:
- `lc::lc_polymorphic<T>` to test if the class is derived from `lc::Polymorphic`


## `lc::NonCopyable`
To enforce non-copyability, use:
```cpp
class SomeClass : LCNonCopyable {};
// equivalent to:
class SomeClass : public lc::NonCopyable {};
```

## `lc::NonMovable`
To enforce non-movability, use:
```cpp
class SomeClass : LCNonMovable {};
// equivalent to:
class SomeClass : public lc::NonMovable {};
```

## `lc::ScopeGuard`

This is a very simple class that help you executing some code on scope exit. For example, suppose you are in a context you have to exit after everything:
```cpp
void draw()
{
	begin_draw();

	if (circle)
	{
		draw_circle();
		end_draw();
		return;
	}

	end_draw();
	return;
}
```

Here, we had to explicitly call `end_draw` on every possible exit path, but we could simply do this:
```cpp
void draw()
{
	begin_draw();
	SCOPE_GUARD([]{
		// this code will be executed when the current scope
		// (the current block "{ ... }") is exited
		end_draw();
	});

	// note: this is equivalent to:
	// lc::ScopeGuard guard([](){ ... });

	if (circle)
	{
		draw_circle();
		return;
	}

	return;
}
```
this removes the necessity of explicitly calling `end_draw()` everywere.
