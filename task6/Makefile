OUTPUT_DIR = output

CFLAGS = -Wall -pedantic -O 
LFLAGS = -Wall -pedentic -O
LDLIBS = -lm

CC = gcc
LD = ${CC}

DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie6.tar.gz

SOURCES = 1.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

run: $(OUTPUT_DIR)/1
	./$< 

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
