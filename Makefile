TARGET := terranova
CXX := g++
CXXFLAGS := -Wall -g
LIBS := -lglfw -lGL -lGLEW -lpthread -lSOIL

SOURCES := $(shell find src -iname '*.cpp' -type f)
OBJECTS := $(patsubst src%.cpp, build%.o, $(SOURCES))
INCLUDES := -Iinclude

.PHONY: all dir res clean run

all: dir res bin/$(TARGET)

dir:
	@mkdir -p build
	@mkdir -p bin

res:
	-@cp -r res/* bin/

clean:
	@rm -rf build/* bin/*

run: all
#	-@clear
	@cd bin; ./terranova; cd ..

build: all

bin/$(TARGET): $(OBJECTS)
	$(CXX) $(LIBS) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<
