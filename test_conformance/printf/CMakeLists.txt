add_executable(test_printf
        test_printf.c
        util_printf.c
        ../../test_common/harness/mt19937.c
        ../../test_common/harness/kernelHelpers.c
        ../../test_common/harness/errorHelpers.c
        ../../test_common/harness/msvc9.c
)

set_source_files_properties(
        test_printf.c
        util_printf.c
        ../../test_common/harness/mt19937.c
        ../../test_common/harness/kernelHelpers.c
        ../../test_common/harness/errorHelpers.c
        ../../test_common/harness/msvc9.c
        PROPERTIES LANGUAGE CXX)

TARGET_LINK_LIBRARIES(test_printf
        ${CLConform_LIBRARIES})
