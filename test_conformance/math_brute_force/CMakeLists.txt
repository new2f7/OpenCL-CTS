add_executable(bruteforce
    FunctionList.c
    Sleep.c
    binary.c
    binaryOperator.c
    Utility.c
    binary_i.c 	binary_two_results_i.c 	i_unary.c
    macro_binary.c 	macro_unary.c 	mad.c
    main.c 	 reference_math.c 
    ternary.c 	unary.c 	unary_two_results.c
    unary_two_results_i.c unary_u.c
    
    ../../test_common/harness/rounding_mode.c
    ../../test_common/harness/ThreadPool.c
    ../../test_common/harness/mt19937.c
    ../../test_common/harness/msvc9.c
)


set_source_files_properties(
    FunctionList.c
    Sleep.c
    binary.c
    binaryOperator.c
    Utility.c
    binary_i.c 	binary_two_results_i.c 	i_unary.c
    macro_binary.c 	macro_unary.c 	mad.c
    main.c 	reference_math.c 
    ternary.c 	unary.c 	unary_two_results.c
    unary_two_results_i.c unary_u.c
    COMPILE_FLAGS -msse2)

if (MSVC)
set_source_files_properties(
    FunctionList.c
    Sleep.c
    binary.c
    binaryOperator.c
    Utility.c reference_math_fma.c
    binary_i.c 	binary_two_results_i.c 	i_unary.c
    macro_binary.c 	macro_unary.c 	mad.c
    main.c 	reference_math.c
    ternary.c 	unary.c 	unary_two_results.c
    unary_two_results_i.c unary_u.c
    ../../test_common/harness/rounding_mode.c
    ../../test_common/harness/ThreadPool.c
    ../../test_common/harness/msvc9.c
	PROPERTIES LANGUAGE CXX)
endif(MSVC)

if(CMAKE_COMPILER_IS_GNUCC)
set_source_files_properties(
        reference_math_fma.c
        COMPILE_FLAGS -O0)
endif(CMAKE_COMPILER_IS_GNUCC)

TARGET_LINK_LIBRARIES(bruteforce
    ${CLConform_LIBRARIES})
