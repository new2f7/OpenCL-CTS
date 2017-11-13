SRCS = main.c \
		test_device_partition.cpp \
		../../test_common/harness/errorHelpers.c \
		../../test_common/harness/threadTesting.c \
		../../test_common/harness/testHarness.c \
		../../test_common/harness/kernelHelpers.c \
		../../test_common/harness/genericThread.cpp \
		../../test_common/harness/mt19937.c \
		../../test_common/harness/conversions.c \
		../../test_common/harness/typeWrappers.cpp \
		../../test_common/harness/msvc9.c

DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_device_partition

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
