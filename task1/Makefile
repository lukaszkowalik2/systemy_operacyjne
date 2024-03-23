OUTPUT_DIR = output
CC = gcc

SOURCE = 1.c 2.c 3.c 4.c

all: 1.o 2.o 3.o
	
1.o: 1.c output_dir
	$(CC) -c 1.c -o $(OUTPUT_DIR)/1.o

2.o: 2.c output_dir
	$(CC) -c 2.c -o $(OUTPUT_DIR)/2.o

3.o: 3.c output_dir
	$(CC) -c 3.c -o $(OUTPUT_DIR)/3.o

4.o: 4.c output_dir
	$(CC) -c 4.c -o $(OUTPUT_DIR)/4.o

5.o: 5.c output_dir
	$(CC) -c 5.c -o $(OUTPUT_DIR)/5.o

run_1: 1.o
	$(CC) $(OUTPUT_DIR)/1.o -o $(OUTPUT_DIR)/1
	clear
	$(OUTPUT_DIR)/1	

run_2: 2.o
	$(CC) $(OUTPUT_DIR)/2.o -o $(OUTPUT_DIR)/2
	clear
	$(OUTPUT_DIR)/2

run_3: 3.o
	$(CC) $(OUTPUT_DIR)/3.o -o $(OUTPUT_DIR)/3
	clear
	$(OUTPUT_DIR)/3

run_4: 4.o
	$(CC) $(OUTPUT_DIR)/4.o -o $(OUTPUT_DIR)/4
	clear
	$(OUTPUT_DIR)/4

run_5: 5.o
	$(CC) $(OUTPUT_DIR)/5.o -o $(OUTPUT_DIR)/5
	clear
	$(OUTPUT_DIR)/5

output_dir:
	mkdir -p $(OUTPUT_DIR)

clean: 
	rm -rf $(OUTPUT_DIR)