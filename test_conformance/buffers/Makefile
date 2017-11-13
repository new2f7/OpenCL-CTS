ifdef BUILD_WITH_ATF
ATF = -framework ATF
USE_ATF = -DUSE_ATF
endif

SRCS = main.c test_buffer_copy.c test_buffer_read.c test_buffer_write.c \
			test_buffer_mem.c array_info.c test_buffer_map.c \
			test_sub_buffers.cpp test_buffer_fill.c \
			test_buffer_migrate.c test_image_migrate.c \
		  ../../test_common/harness/errorHelpers.c \
		  ../../test_common/harness/threadTesting.c \
		  ../../test_common/harness/testHarness.c \
		  ../../test_common/harness/kernelHelpers.c \
                  ../../test_common/harness/conversions.c \
                  ../../test_common/harness/mt19937.c \
		  ../../test_common/harness/typeWrappers.cpp
		  
		
			
DEFINES = 

SOURCES = $(abspath $(SRCS))

include ../../common.mk

TARGET = test_buffers

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

