SRCS = main.c \
		  test_build_helpers.c \
		  test_compile.c \
		  test_compiler_defines_for_extensions.cpp \
		  test_async_build.c \
		  test_build_options.cpp \
		  test_preprocessor.c \
          test_image_macro.c \
		  ../../test_common/harness/errorHelpers.c \
		  ../../test_common/harness/threadTesting.c \
		  ../../test_common/harness/testHarness.c \
		  ../../test_common/harness/kernelHelpers.c \
		  ../../test_common/harness/typeWrappers.cpp \
                  ../../test_common/harness/mt19937.c \
		  ../../test_common/harness/conversions.c
		  
DEFINES = DONT_TEST_GARBAGE_POINTERS

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_compiler

OBJECTS := ${SOURCES:.c=.o}
OBJECTS := ${OBJECTS:.cpp=.o}

TARGETOBJECT =
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(RC_CFLAGS) $(OBJECTS) -o $@ $(LIBPATH) $(LIBRARIES)

clean:
	rm -f $(TARGET) $(OBJECTS)

.DEFAULT:
	@echo The target \"$@\" does not exist in Makefile.
