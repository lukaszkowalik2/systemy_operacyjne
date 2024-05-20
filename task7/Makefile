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

LIB_DIR = lib
LIB_NAME = libshared_memory.so

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB_DIR)/$(LIB_NAME): src/shared_memory.c $(LIB_DIR)
	$(CC) -shared -fPIC $(CFLAGS) src/shared_memory.c -o $@ $(LDLIBS)

all: $(OUTPUT_DIR)/main $(OUTPUT_DIR)/write_to_shm $(OUTPUT_DIR)/read_from_shm

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/main: main.c src/semaphores.c $(LIB_DIR)/$(LIB_NAME) $(OUTPUT_DIR)
	$(CC) $(CFLAGS) main.c src/semaphores.c -L$(LIB_DIR) -lshared_memory -o $@ $(LDLIBS)

$(OUTPUT_DIR)/write_to_shm: write_to_shm.c src/semaphores.c $(LIB_DIR)/$(LIB_NAME) $(OUTPUT_DIR)
	$(CC) $(CFLAGS) write_to_shm.c src/semaphores.c -L$(LIB_DIR) -lshared_memory -o $@ $(LDLIBS)

$(OUTPUT_DIR)/read_from_shm: read_from_shm.c src/semaphores.c $(LIB_DIR)/$(LIB_NAME) $(OUTPUT_DIR)
	$(CC) $(CFLAGS) read_from_shm.c src/semaphores.c -L$(LIB_DIR) -lshared_memory -o $@ $(LDLIBS)

run: $(OUTPUT_DIR)/main $(OUTPUT_DIR)/write_to_shm $(OUTPUT_DIR)/read_from_shm
	export LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH; \
	./$(OUTPUT_DIR)/main
	diff -s ./input.txt ./output.txt

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)
	rm -rf $(LIB_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR) $(DIR))