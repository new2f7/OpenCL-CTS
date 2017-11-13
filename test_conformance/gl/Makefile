SRCS = main.cpp \
		  helpers.cpp \
		  test_buffers.cpp \
		  test_fence_sync.cpp \
		  test_images_1D.cpp \
		  test_images_1Darray.cpp \
		  test_images_2Darray.cpp \
		  test_images_2D.cpp \
		  test_images_3D.cpp \
		  test_images_getinfo_common.cpp \
		  test_images_read_common.cpp \
		  test_images_write_common.cpp \
		  test_renderbuffer.cpp \
		  test_renderbuffer_info.cpp \
		  ../images/image_helpers.cpp \
		  ../../test_common/gl/helpers.cpp \
		  ../../test_common/harness/conversions.c \
		  ../../test_common/harness/errorHelpers.c \
		  ../../test_common/harness/genericThread.cpp \
		  ../../test_common/harness/imageHelpers.cpp \
		  ../../test_common/harness/kernelHelpers.c \
		  ../../test_common/harness/mt19937.c \
		  ../../test_common/harness/testHarness.c \
		  ../../test_common/harness/threadTesting.c

ifdef LINUX
SRCS +=		  ../../test_common/gl/setup_x11.cpp
else
SRCS +=		  ../../test_common/gl/setup_osx.cpp
endif

DEFINES =

SOURCES = $(abspath $(SRCS))

INCLUDE = -I.

include ../../common.mk

ifdef LINUX
LIBRARIES +=  -lGLEW -lglut -lGLU -lGL
endif

TARGET = test_gl

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
