OUTPUT_DIR = output
CC = gcc
CFLAGS = -Wall -pedantic -O 
DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie2.tar.gz

SOURCES = 1.c 2.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

run: $(OUTPUT_DIR)/1 $(OUTPUT_DIR)/2
	./$(OUTPUT_DIR)/1 $(OUTPUT_DIR)/2

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
