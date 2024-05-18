OUTPUT_DIR = output
CC = gcc
CFLAGS = -Wall -pedantic -O 
DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie5.tar.gz
INPUT = input.txt
OUTPUT = output.txt

SOURCES = 1.c 2.c write_to_pipe.c read_from_pipe.c
EXECUTABLES = $(SOURCES:%.c=$(OUTPUT_DIR)/%)

all: $(EXECUTABLES)

$(OUTPUT_DIR)/%: %.c
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

run_1: clean $(OUTPUT_DIR)/1
	touch ${OUTPUT}
	./$(OUTPUT_DIR)/1 ${INPUT} ${OUTPUT}
	diff -s ${INPUT} ${OUTPUT}

run_2: clean ${OUTPUT_DIR}/write_to_pipe ${OUTPUT_DIR}/read_from_pipe
	touch ${OUTPUT}
	mkfifo ${OUTPUT_DIR}/fifo
	xterm -title "Producent" -e ./$(OUTPUT_DIR)/write_to_pipe ${INPUT} ./${OUTPUT_DIR}/fifo &
	xterm -title "Konsument" -e ./$(OUTPUT_DIR)/read_from_pipe ${OUTPUT} ./${OUTPUT_DIR}/fifo &

clean:
	rm -rf $(OUTPUT_DIR)
	rm -f ${OUTPUT}

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )
