# Build simples, sem CMake. Funciona com g++/MinGW no Windows e com g++ no
# Linux. Se preferir CMake, veja o CMakeLists.txt.

CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Isrc

ifeq ($(OS),Windows_NT)
    EXE := .exe
    RM := rm -f
else
    EXE :=
    RM := rm -f
endif

BUILD_DIR := build
APP := $(BUILD_DIR)/biblioteca$(EXE)
TEST_APP := $(BUILD_DIR)/testes$(EXE)

LIB_SOURCES := \
    src/cli/command.cpp \
    src/cli/console.cpp \
    src/data/library.cpp \
    src/model/date.cpp \
    src/service/library_service.cpp

LIB_OBJECTS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(LIB_SOURCES))

.PHONY: all run test clean

all: $(APP)

$(APP): $(BUILD_DIR)/main.o $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_APP): $(BUILD_DIR)/tests/command_test.o $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/tests/%.o: tests/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -Itests -c $< -o $@

run: $(APP)
	./$(APP)

test: $(TEST_APP)
	./$(TEST_APP)

clean:
	$(RM) -r $(BUILD_DIR)
