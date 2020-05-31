#find all the source files
#add save them to the variable DIR_LIB_SRCS

aux_source_directory(. DIR_LIB_MATH_FUNC_SRCS)

#gen the lib
add_library(MathFunc ${DIR_LIB_MATH_FUNC_SRCS})

#specify the MathFunc lib installation path
install(TARGETS MathFunc DESTINATION bin)
install(FILES mathFunc.h DESTINATION include)
