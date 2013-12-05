CXX=g++
CXXPATHS=-I./include/
CXXFLAGS=-c -Wall -Wfatal-errors -std=c++11 -O2
ARPATH=ar
ARFLAGS=crf

SOURCES=$(wildcard ./src/*.cpp)

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=libaeon

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(ARPATH) $(ARFLAGS) $(EXECUTABLE).a $(OBJECTS)

.cpp.o:
	$(CXX) $(CXXPATHS) $(CXXFLAGS) $< -o $@

clean:
	rm -rf ./src/*.o *.a
