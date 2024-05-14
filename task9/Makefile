OUTPUT_DIR = output
CC = gcc
CFLAGS = -Wall -pedantic -O 
DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie4.tar.gz

SOURCES = 1.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

run: $(OUTPUT_DIR)/1
	./$(OUTPUT_DIR)/1

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
