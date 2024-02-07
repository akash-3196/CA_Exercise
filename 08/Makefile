


CC = nvcc
CFLAGS = -Isrc/include -DSTREAM_ARRAY_SIZE=1000000000
#CFLAGS = -I./src/include -DSTREAM_ARRAY_SIZE=4096

SRC_DIR = src
BUILD_DIR = build

SRCS := $(wildcard $(SRC_DIR)/*.cu $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.cu,$(BUILD_DIR)/%.o,$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)))

TARGET = cuda_stream

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cu
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): build $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

build:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: build clean