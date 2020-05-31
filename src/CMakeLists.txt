#CMake minimum version
cmake_minimum_required (VERSION 2.8)
#project infomation
PROJECT(Demo)
#add a configuration file
configure_file(
"${PROJECT_SOURCE_DIR}/config.h.in"
"${PROJECT_SOURCE_DIR}/config.h"
    )

option (USE_MYMATH
	"Use my provided math lib" ON)

if (USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/mathFunc")
    #add the sub directory
    add_subdirectory(mathFunc)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunc)
endif (USE_MYMATH)

#find all the source file for current dir
aux_source_directory(. DIR_SRCS)

ADD_SUBDIRECTORY(printLib)

#specify the executable
add_executable(Demo main.cc)

#add the link lib
target_link_libraries(Demo MathFunc)


#specify the install path
install (TARGETS Demo DESTINATION bin)
install (FILES "${PROJECT_SOURCE_DIR}/config.h" DESTINATION include)

