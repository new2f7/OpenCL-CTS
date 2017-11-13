SRCS = main.cpp \
        test_1D.cpp \
        test_1D_array.cpp \
		test_2D.cpp \
        test_2D_array.cpp \
		../image_helpers.cpp  \
		test_loops.cpp \
		test_3D.cpp \
		  ../../../test_common/harness/errorHelpers.c \
		  ../../../test_common/harness/threadTesting.c \
		  ../../../test_common/harness/kernelHelpers.c \
		  ../../../test_common/harness/imageHelpers.cpp \
		  ../../../test_common/harness/conversions.c \
		  ../../../test_common/harness/testHarness.c \
                  ../../../test_common/harness/mt19937.c \
		  ../../../test_common/harness/typeWrappers.cpp
		  
DEFINES = DONT_TEST_GARBAGE_POINTERS

SOURCES = $(abspath $(SRCS))

include ../../../common.mk

TARGET = test_kernel_image_methods

OBJECTS := ${SOURCES:.c=.o}
OBJECTS := ${OBJECTS:.cpp=.o}

TARGETOBJECT =
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(RC_CFLAGS) $(OBJECTS) -o $@ $(LIBPATH) $(LIBRARIES)

clean:
	rm -f $(TARGET) $(OBJECTS)

.DEFAULT:
	@echo The target \"$@\" does not exist in Makefile.
