



CC = nvcc
#CFLAGS = -Isrc/include -DARRAY_SIZE=600
CFLAGS = -Isrc/include -DARRAY_SIZE=8000000000

LDFLAGS := -arch sm_86 -lcublas -lcurand

ROOT_PATH  := .
SRC_DIR   := $(ROOT_PATH)/src
BUILD_DIR := $(ROOT_PATH)/build


SRCS := $(wildcard $(SRC_DIR)/*.cu $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.cu,$(BUILD_DIR)/%.o,$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)))

TARGET = CBLAS_GPU

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cu
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(TARGET): build $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

build:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: build clean