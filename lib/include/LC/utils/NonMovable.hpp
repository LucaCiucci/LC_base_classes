/*LC_NOTICE_BEGIN
LC_NOTICE_END*/

#pragma once

namespace lc
{
    // Use this as base class for all the classes tha cannot be moved around in memory for some reasons,
	// for example some raw pointers to them are stored in other places of the program.
	// Example:
	// ```cpp
	// class MyClass : public lc::NonMovable {}; // <- public is usually not necessary
	// ```
    class NonMovable {
    public:
        NonMovable() = default;
        NonMovable(const NonMovable&) = default;

        NonMovable& operator=(const NonMovable&) = default;

    private:
        NonMovable(NonMovable&&) = delete;
        NonMovable& operator=(NonMovable&&) = delete;
    };
}

#define LCNonMovable public ::lc::NonMovable