SRCS = main.c \
		  test_events.cpp \
		  test_event_dependencies.cpp \
		  test_userevents.cpp \
		  test_waitlists.cpp \
		  test_callbacks.cpp \
		  action_classes.cpp \
		  test_userevents_multithreaded.cpp \
		  ../../test_common/harness/errorHelpers.c \
		  ../../test_common/harness/threadTesting.c \
		  ../../test_common/harness/testHarness.c \
		  ../../test_common/harness/genericThread.cpp \
		  ../../test_common/harness/kernelHelpers.c \
		  ../../test_common/harness/typeWrappers.cpp \
                  ../../test_common/harness/mt19937.c \
		  ../../test_common/harness/conversions.c \
		  ../../test_common/harness/ThreadPool.c \
		  
DEFINES = DONT_TEST_GARBAGE_POINTERS

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_events

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
