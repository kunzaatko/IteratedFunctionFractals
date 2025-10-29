CC := gcc
CFLAGS := -std=c99 -Wall  -I ./include/ -lm -fPIE
LDFLAGS := -pthread -L ./lib
LDLIBS := -lm -lSDL2 -ldl

BUILD_DIR := build
SOURCE_DIR := src
TEST_DIR := test
BIN := program
TEST_BIN := test

HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.c)
TEST_SOURCES += $(wildcard $(TEST_DIR)/vendor/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.o, $(TEST_SOURCES))
TEST_HEADERS := $(wildcard $(TEST_DIR)/*.h)
TEST_HEARDERS += $(wildcard $(TEST_DIR)/vendor/*.h)
TEST_VENDOR_OBJECTS := $(wildcard $(TEST_DIR)/vendor/*.o)

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

.PHONY: test
test: $(BUILD_DIR)/$(TEST_BIN)

$(BUILD_DIR)/$(TEST_BIN): $(TEST_DIR)/vendor/*.c $(TEST_DIR)/*.c  $(filter-out $(SOURCE_DIR)/main.c, $(SOURCES)) | $$(@D)/.
	$(CC) $(LDFLAGS) $^ -o $(BUILD_DIR)/$(TEST_BIN) $(LDLIBS)
	./$(BUILD_DIR)/$(TEST_BIN)

clean:
	-rm -rf $(BUILD_DIR)
	-rm -f $(BIN)
