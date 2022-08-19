

cmake_minimum_required(VERSION 3.20)

project(
	LC_base_classes
	VERSION 0.0.0
	DESCRIPTION "provides soma very basic classes such as `NonCopiable`, `Abstract` etc."
	LANGUAGES CXX
)

include(CTest)

add_library(LC_base_classes INTERFACE)

#target_include_directories(LC_base_classes INTERFACE "lib/include")
target_include_directories(
	LC_base_classes
	INTERFACE
		#$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib/include>
		#$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/LC_base_classes>
)

# see https://cliutils.gitlab.io/modern-cmake/chapters/install/installing.html

install(
	TARGETS LC_base_classes
	EXPORT LC_base_classesTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    LC_base_classesConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

install(EXPORT LC_base_classesTargets
	FILE LC_base_classesTargets.cmake
	NAMESPACE LC::
	DESTINATION lib/cmake/LC_base_classes
)

configure_file(
	cmake/LC_base_classesConfig.cmake.in
	LC_base_classesConfig.cmake
	@ONLY
)
install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/LC_base_classesConfig.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/LC_base_classesConfig.cmake"
	DESTINATION lib/cmake/LC_base_classes
)

install(
	DIRECTORY "${PROJECT_SOURCE_DIR}/lib/include/"
	DESTINATION "include/LC_base_classes"
)

add_subdirectory(tests)