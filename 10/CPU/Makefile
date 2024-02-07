# Directories
ROOT_PATH  := .
SRC_PATH   := $(ROOT_PATH)/src
BUILD_PATH := $(ROOT_PATH)/build
BIN_PATH   := $(ROOT_PATH)/bin

# Include directories
INC_PATH  := $(SRC_PATH)/include
INC_DIRS  := $(sort $(shell find $(INC_PATH) -type d))
INC_FLAGS := $(addprefix -I,$(INC_DIRS))


CC      := icc
CFLAGS  := -Wall -pedantic -Werror -std=c11 -O3 -xHost -DARRAY_SIZE=45000000000

LDFLAGS := -mkl

TARGET = LINPACK_CPU

SRCS := $(wildcard $(SRC_PATH)/*.c)

OBJS := $(patsubst $(SRC_PATH)/%.c,$(BUILD_PATH)/%.o,$(SRCS))

$(shell mkdir -p $(BIN_PATH))
$(shell mkdir -p $(BUILD_PATH))


all: $(BIN_PATH)/$(TARGET)


$(BIN_PATH)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@


$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)