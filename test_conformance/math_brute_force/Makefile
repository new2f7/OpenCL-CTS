SRCS = binary.c binary_i.c binaryOperator.c binary_two_results_i.c \
			FunctionList.c i_unary.c macro_binary.c macro_unary.c mad.c main.c \
			reference_math.c Sleep.c ternary.c unary.c unary_two_results.c \
			unary_two_results_i.c unary_u.c Utility.c \
			../../test_common/harness/mt19937.c \
			../../test_common/harness/rounding_mode.c \
			../../test_common/harness/ThreadPool.c 

ifdef LINUX

DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = bruteforce

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

CC = cc
CFLAGS = -g -Wall -Wshorten-64-to-32 $(COMPILERFLAGS) ${RC_CFLAGS} ${USE_ATF}
LIBRARIES = -framework OpenCL -framework ApplicationServices -framework IOKit -I/System/Library/Frameworks/OpenCL.framework/Headers ${RC_CFLAGS} ${ATF}

release:
	echo "Build Release"
	$(CC) $(SRCS) -Os $(CFLAGS) -o bruteforce $(LIBRARIES)

debug:
	echo "Build Debug"
	$(CC) $(SRCS) -O0 $(CFLAGS) -D_DEBUG=1 -o bruteforce_debug  $(LIBRARIES)

test:	release
	arch -i386 ./bruteforce -c > cpu.log	&
	arch -i386 ./bruteforce -g > gpu.log	&
	echo "Testing 32-bit mode in progress. This may take up to 1 day to complete. See cpu.log and gpu.log for results."

test64:	release
	arch -x86_64 ./bruteforce -c > cpu64.log	&
	arch -x86_64 ./bruteforce -g > gpu64.log	&
	echo "Testing 64-bit mode in progress. This may take up to 1 day to complete. See cpu64.log and gpu64.log for results."

clean:
	rm -f ./bruteforce_debug
	rm -f ./bruteforce

all:	release 

endif