include_directories( "${CMAKE_SOURCE_DIR}/../test_common/harness")

add_executable(contractions
        contractions.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/mt19937.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/msvc9.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/mingw_compat.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/errorHelpers.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/rounding_mode.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/kernelHelpers.c
)
set_source_files_properties(
        contractions.c
        COMPILE_FLAGS -msse)
if(WIN32)
set_source_files_properties(
        contractions.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/msvc9.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/mingw_compat.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/errorHelpers.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/rounding_mode.c
        ${CMAKE_SOURCE_DIR}/../test_common/harness/kernelHelpers.c
        PROPERTIES LANGUAGE CXX)
endif(WIN32)

TARGET_LINK_LIBRARIES(contractions
        ${CLConform_LIBRARIES})
