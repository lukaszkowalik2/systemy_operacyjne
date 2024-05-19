OUTPUT_DIR = output

CFLAGS = -Wall -pedantic -O -Iinclude
LFLAGS = -Wall -pedantic -O
LDLIBS = -lm -lrt -pthread

CC = gcc
LD = $(CC)

DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie7.tar.gz

SOURCES = write_to_shm.c read_from_shm.c main.c src/semaphores.c src/shared_memory.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(OUTPUT_DIR)/main $(OUTPUT_DIR)/write_to_shm $(OUTPUT_DIR)/read_from_shm

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/main: main.c src/semaphores.c src/shared_memory.c | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) main.c src/semaphores.c src/shared_memory.c -o $@ $(LDLIBS)

$(OUTPUT_DIR)/write_to_shm: write_to_shm.c src/semaphores.c src/shared_memory.c | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) write_to_shm.c src/semaphores.c src/shared_memory.c -o $@ $(LDLIBS)

$(OUTPUT_DIR)/read_from_shm: read_from_shm.c src/semaphores.c src/shared_memory.c | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) read_from_shm.c src/semaphores.c src/shared_memory.c -o $@ $(LDLIBS)

run: $(OUTPUT_DIR)/main $(OUTPUT_DIR)/write_to_shm $(OUTPUT_DIR)/read_from_shm
	./$(OUTPUT_DIR)/main
	diff -s ./input.txt ./output.txt

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR) $(DIR))
