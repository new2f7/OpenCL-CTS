# We do not use dependencies in this Makefile

SRCS = Sleep.c \
			basic_test_conversions.c \
			 test_conversions.c \
			 ../../test_common/harness/mt19937.c \
			 ../../test_common/harness/ThreadPool.c \
			 ../../test_common/harness/rounding_mode.c

SOURCES = $(abspath $(SRCS))

DEFINES = 

COMPILERFLAGS = -std=c99

INCLUDE =  -I../../test_common/harness

include ../../common.mk

ifdef LINUX

TARGET = test_conversions

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

else

release:
	echo "Build Release"
	$(CC) -c basic_test_conversions.c -Os $(CFLAGS) -o basic_test_conversions.o
	$(CC) $(SRCFILES) -Os $(CFLAGS) basic_test_conversions.o -o test_conversions $(INCLUDES) $(LIBRARIES)

debug:
	echo "Build Debug"
	$(CC) -c basic_test_conversions.c -O0 $(CFLAGS) -o basic_test_conversions.o
	$(CC) test_conversions.c -c -O0 -g  $(CFLAGS) $(INCLUDES)  -o test_conversions.o 
	$(CC) Sleep.c -c -O0 -g  $(CFLAGS) $(INCLUDES)  -o Sleep.o 
	$(CC) ../../test_common/harness/mt19937.c -c -O0 -g  $(INCLUDES) $(CFLAGS)  -o mt19937.o 
	$(CC) ../../test_common/harness/ThreadPool.c -c -O0 -g  $(INCLUDES) $(CFLAGS)  -o ThreadPool.o 
	$(CC) ../../test_common/harness/rounding_mode.c -c -O0 -g $(INCLUDES) $(CFLAGS)  -o rounding_mode.o 
	$(CC) *.o -g -O0 -o test_conversions_debug $(LIBRARIES) -arch i386 -arch x86_64

clean:
	rm -f test_conversions
	rm -f *.o
	rm -f test_conversions_debug

test:	release
	arch -i386 ./test_conversions -c > cpu.out	&
	arch -i386 ./test_conversions -g > gpu.out	&
	echo "Testing 32-bit mode conversions for CPU and GPU, which takes a day or three.  Results may be found in cpu.out and gpu.out\n"

test64:	release
	arch -x86_64 ./test_conversions_64 -c > cpu64.out	&
	arch -x86_64 ./test_conversions_64 -g > gpu64.out	&
	echo "Testing 64-bit mode conversions for CPU and GPU, which takes a day or three.  Results may be found in cpu64.out and gpu64.out\n"

all: release

endif
