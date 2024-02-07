



CC = nvcc
#CFLAGS = -Isrc/include -DGRID_SIZE=1048576
CFLAGS = -Isrc/include -DGRID_SIZE=3000000000

ROOT_PATH  := .
SRC_DIR   := $(ROOT_PATH)/src
BUILD_DIR := $(ROOT_PATH)/build


SRCS := $(wildcard $(SRC_DIR)/*.cu $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.cu,$(BUILD_DIR)/%.o,$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)))

TARGET = cuda_jacobi

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