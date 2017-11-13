SRCS = conversions.c \
	errorHelpers.c \
	genericThread.cpp \
	imageHelpers.cpp \
	kernelHelpers.c \
	mt19937.c \
	rounding_mode.c \
	testHarness.c \
	testHarness.cpp \
	ThreadPool.c \
	threadTesting.c \
	typeWrappers.cpp
		  
DEFINES = DONT_TEST_GARBAGE_POINTERS

SOURCES = $(abspath $(SRCS))

include ../../common.mk

OBJECTS := ${SOURCES:.c=.o}
OBJECTS := ${OBJECTS:.cpp=.o}

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)

.DEFAULT:
	@echo The target \"$@\" does not exist in Makefile.
