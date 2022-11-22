#[[LC_NOTICE_BEGIN
LC_NOTICE_END]]

cmake_minimum_required(VERSION 3.20)


################################
#           PROJECT
################################

project(
	LC_base_classes
	VERSION 0.1.0
	DESCRIPTION "provides soma very basic classes such as `NonCopiable`, `Abstract` etc."
	LANGUAGES CXX
)

set(LC_base_classes_MAIN_PROJECT FALSE)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(LC_base_classes_MAIN_PROJECT TRUE)
endif()

################################
#          LIBRARY
################################

# This is an header only library, so we declate it as INTERFACE
add_library(LC_base_classes INTERFACE)

target_include_directories(
	LC_base_classes
	INTERFACE
		
		# probably useless since this library is not build (INTERFACE)
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib/include>

		# once installed, users will use this path to include this library
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/LC_base_classes>
)

################################
#         INSTALLATION
################################

# see https://cliutils.gitlab.io/modern-cmake/chapters/install/installing.html

install(
	TARGETS
		# targets we are exporting
		LC_base_classes
	EXPORT
		# the export group
		LC_base_classesTargets

	# TODO what are these? are they necessary for this library?
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    LC_base_classesConfigVersion.cmake # TODO this is not used?!?! maybe we have to install() it????
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )


install(
	EXPORT
		# the export group
		LC_base_classesTargets
	FILE
		# the file we are exporting the group to
		LC_base_classesTargets.cmake
	NAMESPACE
		# the namespace we are exporting the group to,
		# targets will be installed in this namespace,
		# users will find the library as "LC::LC_base_classes"
		LC::
	DESTINATION
		# the destination of the file, relative to the install prefix
		lib/cmake/LC_base_classes
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
	DESTINATION "include/LC_base_classes" # see the above "target_include_directories" call
)


################################
#          TESTING
################################

if (LC_base_classes_MAIN_PROJECT)
	# ??? copilot-> enable_testing()
	add_subdirectory(tests)
endif()