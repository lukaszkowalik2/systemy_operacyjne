OUTPUT_DIR = output
CC = gcc
CFLAGS = -Wall -pedantic -O 
DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie3.tar.gz
INPUT = input.txt
OUTPUT = output.txt

SOURCES = 1.c 2.c 3.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

run: clean $(OUTPUT_DIR)/1
	touch ${OUTPUT}
	./$(OUTPUT_DIR)/1 ${INPUT} ${OUTPUT}
	diff -s ${INPUT} ${OUTPUT}

clean:
	rm -rf $(OUTPUT_DIR)
	rm -f ${OUTPUT}

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
