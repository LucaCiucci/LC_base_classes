#[[LC_NOTICE_BEGIN
LC_NOTICE_END]]

add_executable(unit_test)
# ??? unit_test:add_dependencies(unit_test_dependencies)

target_sources(
	unit_test
	PRIVATE
		"Polymorphic.cpp"
		"NonCopyable.cpp"
		"NonMovable.cpp"
		"ScopeGuard.cpp"
)

target_link_libraries(unit_test PRIVATE LC_base_classes)

# C++20
set_target_properties(unit_test PROPERTIES CXX_STANDARD 20)

# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#top
find_package(Catch2 3 REQUIRED)
target_link_libraries(unit_test PRIVATE Catch2::Catch2WithMain)

add_test(NAME TestName COMMAND unit_test)