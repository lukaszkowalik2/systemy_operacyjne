OUTPUT_DIR = output
CC = gcc
CFLAGS = -Wall -pedantic -O 
DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie1.tar.gz

SOURCES = 1.c 2.c 3.c 4.c 5.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

run_%: $(OUTPUT_DIR)/%
	./$<

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
