OUTPUT_DIR = output

CFLAGS = -Wall -pedantic -O 
LFLAGS = -Wall -pedentic -O
LDLIBS = -lm -lrt

CC = gcc
LD = ${CC}

DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie7.tar.gz

SOURCES = 1.c read_from_shm.c write_to_shm.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) ${LDLIBS} $< -o $@

run: $(OUTPUT_DIR)/1 ${OUTPUT_DIR}/read_from_shm ${OUTPUT_DIR}/write_to_shm
	./$(OUTPUT_DIR)/1

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
