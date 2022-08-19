/*LC_NOTICE_BEGIN
LC_NOTICE_END*/

#pragma once

#include <functional>

#include <LC/utils/NonCopyable.hpp>

namespace lc
{
	class ScopeGuard : LCNonCopyable
	{
	public:

		template<class Func>
		ScopeGuard(Func const& cleanup) : m_cleanup(cleanup) {};

		ScopeGuard(std::function<void(void)> cleanup = {}) : m_cleanup(cleanup) {};

		~ScopeGuard() {
			if (m_cleanup)
				m_cleanup();
		}

		void dismiss() { m_cleanup = {}; };
		
		template<class Func>
		void reset(Func const& cleanup) { m_cleanup = cleanup; };

		void reset(void) { this->dismiss(); };

		bool enabled(void) const { return (bool)m_cleanup; }

	private:
		std::function<void(void)> m_cleanup;
	};
}

#define __SCOPE_GUARD_NAME(line) _hidden_scope_guard_line_##line
#define SCOPE_GUARD(function) ::lc::ScopeGuard __SCOPE_GUARD_NAME(__LINE__)(function);


// see also:
// https://stackoverflow.com/questions/31365013/what-is-scopeguard-in-c