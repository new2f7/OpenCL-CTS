SRCS = test_select.c util_select.c \
			 ../../test_common/harness/mt19937.c \
			 ../../test_common/harness/kernelHelpers.c \
			 ../../test_common/harness/errorHelpers.c
DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

HEADERS = test_select.h

TARGET = test_select

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
