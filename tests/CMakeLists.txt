#[[LC_NOTICE_BEGIN
LC_NOTICE_END]]

include(CTest)

add_executable(unit_test)

target_link_libraries(unit_test PRIVATE LC_base_classes)

# C++20
set_target_properties(unit_test PROPERTIES CXX_STANDARD 20)

# Note: we don't need a "main" since Catch2 lib can provide one for us
target_sources(
	unit_test
	PRIVATE
		"Polymorphic.cpp"
		"NonCopyable.cpp"
		"NonMovable.cpp"
		"ScopeGuard.cpp"
)

# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#top
find_package(Catch2 3 REQUIRED)
target_link_libraries(unit_test PRIVATE Catch2::Catch2WithMain)

add_test(NAME UnitTest COMMAND unit_test)