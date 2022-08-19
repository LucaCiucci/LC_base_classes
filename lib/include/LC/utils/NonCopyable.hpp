/*LC_NOTICE_BEGIN
LC_NOTICE_END*/

#pragma once

namespace lc
{
    // Use this as base class for all the classes tha cannot be copyed
	// using the copy constructor, example:
	// ```cpp
	// class SomeComplexClass : public NonCopyable {}; // <- public is usually not necessary
	// ```
	// Note that non-copyable is different from non-movable, see `NonMovable`
    class NonCopyable {
    public:
        NonCopyable() = default;
        NonCopyable(NonCopyable&&) = default; // non copyable could be moved anyway!
        //~NonCopyable() = default;

    private:
        NonCopyable(const NonCopyable&) = delete;
        // NonCopyable(NonCopyable&&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#define LCNonCopyable public ::lc::NonCopyable