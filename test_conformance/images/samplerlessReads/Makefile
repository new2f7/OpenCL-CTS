ifdef BUILD_WITH_ATF
ATF = -framework ATF
USE_ATF = -DUSE_ATF
endif

SRCS = main.cpp \
		test_iterations.cpp \
		test_loops.cpp \
        test_read_1D.cpp \
        test_read_1D_buffer.cpp \
        test_read_1D_array.cpp \
        test_read_2D_array.cpp \
		test_read_3D.cpp \
		../image_helpers.cpp  \
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

TARGET = test_samplerless_reads

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
