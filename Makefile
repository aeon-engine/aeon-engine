AEONDEV=/Users/robindegen/Development/Libraries
CXX=g++
CXXPATHS=-I$(AEONDEV)/include/
CXXFLAGS=-c -Wall -Wfatal-errors -std=c++11 -O2 -g
LDPATHS=-L$(AEONDEV)/lib/
LDFLAGS=\
	-lglfw3 \
	-lGLEW \
	-lpng \
	-framework Cocoa \
	-framework OpenGL \
	-framework IOKit \
	-framework CoreVideo

SRCS=$(wildcard ./src/*.cpp)
OBJS=$(SRCS:.cpp=.o)

EXECUTABLE=bin/aeon_engine

all: $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@echo "Linking..."
	@$(CXX) $(LDPATHS) $(LDFLAGS) -o $@ $(OBJS)
	@echo "Build successful."

.cpp.o:
	@echo ">> $<"
	@$(CXX) $(CXXPATHS) $(CXXFLAGS) $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJS)
	@rm -rf $(EXECUTABLE)

