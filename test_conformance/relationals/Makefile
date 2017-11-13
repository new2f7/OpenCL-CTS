SRCS = main.c \
		  test_relationals.cpp \
		  test_shuffles.cpp \
			test_comparisons_double.cpp \
			test_comparisons_float.cpp \
		  ../../test_common/harness/errorHelpers.c \
		  ../../test_common/harness/threadTesting.c \
		  ../../test_common/harness/testHarness.c \
		  ../../test_common/harness/kernelHelpers.c \
                  ../../test_common/harness/mt19937.c \
		  ../../test_common/harness/conversions.c 
		  
DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_relationals

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
