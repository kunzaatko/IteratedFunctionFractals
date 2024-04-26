CC := gcc
CFLAGS := -std=c99 -Wall  -I ./include/ -lm -fPIE
LDFLAGS := -pthread -L ./lib
LDLIBS := -lm -lSDL2 -ldl

BUILD_DIR := build
SOURCE_DIR := src
BIN := program

HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: $(BIN)
$(BIN): $(BUILD_DIR)/$(BIN)

.PRECIOUS: $(BUILD_DIR)/. $(BUILD_DIR)%/.

$(BUILD_DIR)/.:
	mkdir -p $@

$(BUILD_DIR)%/.:
	mkdir -p $@

.SECONDEXPANSION:

$(OBJECTS): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS) | $$(@D)/.
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BUILD_DIR)/$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	ln -rs $(BUILD_DIR)/$(BIN) $(BIN)

clean:
	-rm -rf $(BUILD_DIR)
	-rm -f $(BIN)
