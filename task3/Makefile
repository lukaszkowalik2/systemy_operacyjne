OUTPUT_DIR = output
CC = gcc
CFLAGS = -Wall -pedantic -O 
DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie3.tar.gz

SOURCES = 1.c 2.c 3.c 4.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

run_1: $(OUTPUT_DIR)/1
	./$<

run_2: $(OUTPUT_DIR)/1 $(OUTPUT_DIR)/2
	./$(OUTPUT_DIR)/2 $(OUTPUT_DIR)/1

run_3: $(OUTPUT_DIR)/3 $(OUTPUT_DIR)/4 $(OUTPUT_DIR)/1
	./$(OUTPUT_DIR)/3 $(OUTPUT_DIR)/4

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
