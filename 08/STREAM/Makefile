

CC = icc
#CFLAGS = -Wall -pedantic -Werror -qopenmp -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20 -qopt-streaming-stores always --no-relax -O3 -xHOST
CFLAGS = -Wall -pedantic -Werror -qopenmp -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20 -qopt-streaming-stores always -xHOST -O3



# Source files
SRC_DIR = ./
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, build/%.o, $(SOURCES))

# Output binary
TARGET = STREAM_BENCH

# Targets
all: $(TARGET)

$(TARGET): build $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)



build:
	mkdir -p build

build/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf build $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
