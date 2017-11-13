ifdef BUILD_WITH_ATF
ATF = -framework ATF
USE_ATF = -DUSE_ATF
endif

ifdef LINUX
COMPILERFLAGS = -c -Wall -g -fPIC -Wno-narrowing -fpermissive
LIBRARIES = -lOpenCL -lm -pthread
else
LIBPATH += -L.
COMPILERFLAGS = -c -Wall -g -Wshorten-64-to-32 -Os -Wno-deprecated-declarations -Wno-unknown-pragmas
LIBRARIES = -framework OpenCL -framework OpenGL -framework GLUT -framework AppKit ${ATF}
endif

CC = $(CXX)
HEADERS =
INCLUDE += -I../../test_common/harness
CFLAGS = $(COMPILERFLAGS) ${RC_CFLAGS} ${USE_ATF} $(DEFINES:%=-D%) $(INCLUDE)
CXXFLAGS = $(COMPILERFLAGS) ${RC_CFLAGS} ${USE_ATF} $(DEFINES:%=-D%) $(INCLUDE)
