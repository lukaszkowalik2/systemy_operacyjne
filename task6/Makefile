OUTPUT_DIR = output
INCLUDE_DIR = include
SRC_DIR = src

CFLAGS = -Wall -pedantic -O
LFLAGS = -Wall -pedantic -O
LDLIBS = -lpthread

CC = gcc
LD = ${CC}

DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie6.tar.gz

SOURCES = multiplier.c critical_section.c $(SRC_DIR)/semaphores.c
HEADERS = $(INCLUDE_DIR)/semaphores.h
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/multiplier: multiplier.c  $(SRC_DIR)/semaphores.c  $(INCLUDE_DIR)/semaphores.h
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) multiplier.c  $(SRC_DIR)/semaphores.c -o $@ $(LDLIBS)

$(OUTPUT_DIR)/critical_section: critical_section.c  $(SRC_DIR)/semaphores.c  $(INCLUDE_DIR)/semaphores.h
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) critical_section.c  $(SRC_DIR)/semaphores.c -o $@ $(LDLIBS)

run: $(OUTPUT_DIR)/multiplier $(OUTPUT_DIR)/critical_section
	./$(OUTPUT_DIR)/multiplier ./$(OUTPUT_DIR)/critical_section 5 5

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR) $(DIR))
