SRCS = main.c \
			 ../../test_common/harness/errorHelpers.c \
			 ../../test_common/harness/kernelHelpers.c

SOURCES = $(abspath $(SRCS))

DEFINES = 

INCLUDE = -I./../../OpenCL/cl_headers/public

include ../../common.mk

TARGET = computeinfo

OBJECTS := ${SOURCES:.c=.o}

TARGETOBJECT =
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(RC_CFLAGS) $(OBJECTS) -o $@ $(LIBPATH) $(LIBRARIES)

clean:
	rm -f $(TARGET) $(OBJECTS)

.DEFAULT:
	@echo The target \"$@\" does not exist in Makefile.



