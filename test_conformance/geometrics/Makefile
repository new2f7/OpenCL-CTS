SRCS = main.c \
		  test_geometrics.c \
		  test_geometrics_double.c \
		  ../../test_common/harness/errorHelpers.c \
		  ../../test_common/harness/threadTesting.c \
		  ../../test_common/harness/testHarness.c \
		  ../../test_common/harness/conversions.c \
		  ../../test_common/harness/mt19937.c \
		  ../../test_common/harness/kernelHelpers.c
		  
DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_geometrics

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
