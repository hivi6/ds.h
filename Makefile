CC := gcc
FLAGS := -Wall -Wextra

DS_H := ds.h
BIN := bin
TEST := test

TEST_FILES := $(wildcard $(TEST)/*.c)
BIN_FILES := $(subst .c,,$(subst $(TEST),$(BIN),$(TEST_FILES)))

all: $(BIN) $(BIN_FILES)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%: $(TEST)/%.c $(DS_H)
	$(CC) -I. -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf $(BIN)
