SRCS = test_printf.c \
	util_printf.c \
	../../test_common/harness/mt19937.c \
	../../test_common/harness/kernelHelpers.c \
	../../test_common/harness/errorHelpers.c \
	../../test_common/harness/msvc9.c

DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_printf

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



