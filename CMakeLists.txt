

cmake_minimum_required(VERSION 3.20)

project(
	LC_base_classes
	VERSION 0.0.0
	DESCRIPTION "provides soma very basic classes such as `NonCopiable`, `Abstract` etc."
	LANGUAGES CXX
)

include(CTest)

add_library(LC_base_classes INTERFACE)

target_include_directories(LC_base_classes INTERFACE "lib/include")

# see https://cliutils.gitlab.io/modern-cmake/chapters/install/installing.html

install(
	TARGETS LC_base_classes
	EXPORT LC_base_classes_Targets
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

add_subdirectory(tests)