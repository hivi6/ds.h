EXE := ds

CC := gcc
FLAGS := -Wall -Wextra

CFILES := $(wildcard *.c)
HFILES := $(wildcard *.h)

$(EXE): $(CFILES) $(HFILES)
	$(CC) -o $(EXE) $(FLAGS) $(CFILES)

.PHONY: clean
clean:
	rm -rf $(EXE)
