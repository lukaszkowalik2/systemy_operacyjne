OUTPUT_DIR = output

CFLAGS = -Wall -pedantic -O
LFLAGS = -Wall -pedentic -O
LDLIBS = -lm

CC = gcc
LD = ${CC}

DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie8.tar.gz

SOURCES = server.c client.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -lrt $< -o $@

run: $(OUTPUT_DIR)/server $(OUTPUT_DIR)/client
	./$(OUTPUT_DIR)/server
	./$(OUTPUT_DIR)/client

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
