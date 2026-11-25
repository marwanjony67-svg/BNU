CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -Wpedantic
TARGET := build/bnu
SOURCES := src/main.cpp src/system.cpp

.PHONY: all clean run budgieosmaker
all: $(TARGET)

$(TARGET): $(SOURCES) src/system.hpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) help

budgieosmaker:
	chmod +x tools/budgieosmaker
	./tools/budgieosmaker BudgieOS-OS

clean:
	rm -rf build
