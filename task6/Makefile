OUTPUT_DIR = output

CFLAGS = -Wall -pedantic -O
LFLAGS = -Wall -pedantic -O
LDLIBS = -lpthread

CC = gcc
LD = ${CC}

DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie6.tar.gz

SOURCES = multiplier.c critical_section.c semaphores.c
HEADERS = semaphores.h
EXECUTABLES = $(addprefix $(OUTPUT_DIR)/, multiplier critical_section)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/multiplier: multiplier.c semaphores.c semaphores.h
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) multiplier.c semaphores.c -o $@ $(LDLIBS)

$(OUTPUT_DIR)/critical_section: critical_section.c semaphores.c semaphores.h
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) critical_section.c semaphores.c -o $@ $(LDLIBS)

run: $(OUTPUT_DIR)/multiplier $(OUTPUT_DIR)/critical_section
	./$(OUTPUT_DIR)/multiplier ./$(OUTPUT_DIR)/critical_section 5 10

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR) $(DIR))
