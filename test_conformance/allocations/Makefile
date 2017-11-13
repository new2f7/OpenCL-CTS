SRCS = main.cpp \
		allocation_functions.cpp \
		allocation_fill.cpp  \
		allocation_utils.cpp \
		allocation_execute.cpp \
		  ../../test_common/harness/errorHelpers.c \
		  ../../test_common/harness/threadTesting.c \
		  ../../test_common/harness/kernelHelpers.c \
		  ../../test_common/harness/testHarness.c \
                  ../../test_common/harness/mt19937.c \
		  ../../test_common/harness/typeWrappers.cpp
		  
DEFINES = DONT_TEST_GARBAGE_POINTERS

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_allocations

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
