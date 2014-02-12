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
	@echo "Linking..."
	@$(ARPATH) $(ARFLAGS) $(EXECUTABLE).a $(OBJECTS)
	@echo "Build successful."

.cpp.o:
	@echo ">> $<"
	@$(CXX) $(CXXPATHS) $(CXXFLAGS) $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf $(wildcard ./src/*.o)
	@rm -rf *.a
