CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

#project infomation
PROJECT(Demo)
set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)

message(STATUS "This is BINARY directory" ${PROJECT_BINARY_DIR})
message(STATUS "This is SOURCE directiory" ${PROJECT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_SUBDIRECTORY(src bin)

#enable testing
enable_testing()

add_test(test_run Demo 5 2)

add_test(test_usage Demo)
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

add_test(test_2_10 Demo 2 10)
set_tests_properties(test_2_10 PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")

#define a macro to simply the test case
macro(do_test arg1 arg2 result)
    add_test(test_${arg1}_${arg2} Demo ${arg1} ${arg2})
    set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)


do_test(5 2 "is 25")
do_test(10 5 "is 100000")
do_test(2 10 "is 1024")

INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/demo)
INSTALL(PROGRAMS run-demo.sh DESTINATION bin)
INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/demo)


#support GDB

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#Gen a CPack package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include (CPack)
