# Makefile for my_project

# Compiler settings
#MODULE_LOAD = $(shell module load intel)
CC = icc
CFLAGS = -Wall -pedantic -Werror -std=c99 -O3 -pg -xHost -I./src/include #-I/apps/likwid/5.3.0/include

# Likwid settings
#LIKWID_FLAGS = -DLIKWID_PERFMON
#LIKWID_LIB = -pthread -L/apps/likwid/5.3.0/lib/ -llikwid

# Source files
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, build/%.o, $(SOURCES))

# Output binary
TARGET = task_5

# Targets
all: $(TARGET)

$(TARGET): build $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIKWID_LIB)
#	$(CC) $(CFLAGS) $(LIKWID_FLAGS) -o $@ $(OBJECTS) $(LIKWID_LIB)

build:
	mkdir -p build

build/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
#	$(CC) $(CFLAGS) $(LIKWID_FLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf build $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

#.PHONY: profile
#profile: $(TARGET)
#	likwid-perfctr -C 0 -g CACHE -m ./$(TARGET)
