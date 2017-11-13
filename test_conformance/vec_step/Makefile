SRCS = 		main.c \
		structs.c \
		test_step.c \
		globals.c \
		type_replacer.c \
		../../test_common/harness/errorHelpers.c \
		../../test_common/harness/threadTesting.c \
		../../test_common/harness/testHarness.c \
		../../test_common/harness/kernelHelpers.c \
		../../test_common/harness/mt19937.c \
		../../test_common/harness/conversions.c 

DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_vecstep

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
