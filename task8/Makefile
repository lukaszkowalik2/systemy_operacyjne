OUTPUT_DIR = output
INCLUDE_DIR = include
SRC_DIR = src

CFLAGS = -Wall -pedantic -O
LDLIBS = -lrt -lm

CC = gcc
LD = ${CC}

DIR = $(notdir $(CURDIR))
OUTPUT_TAR = Zadanie8.tar.gz

SOURCES = server.c $(SRC_DIR)/message_queue.c
HEADERS = $(INCLUDE_DIR)/message_queue.h

SERVER_EXECUTABLE = $(OUTPUT_DIR)/server
CLIENT_EXECUTABLE = $(OUTPUT_DIR)/client

all: $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE)

$(SERVER_EXECUTABLE): $(SOURCES) $(HEADERS)
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(SOURCES) -o $@ $(LDLIBS)

$(CLIENT_EXECUTABLE): client.c $(SRC_DIR)/message_queue.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(LDLIBS)

run: $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE)
	xterm -hold -title SERWER -bg aqua -fg black -e ./$(SERVER_EXECUTABLE) &
	xterm -hold -title KLIENT1 -bg green -fg black -e ./$(CLIENT_EXECUTABLE) &
	xterm -hold -title KLIENT2 -bg green -fg black -e ./$(CLIENT_EXECUTABLE) &

.PHONY: all clean tar

clean:
	rm -rf $(OUTPUT_DIR)

tar: clean
	(cd ../; tar -cvzf $(OUTPUT_TAR)  $(DIR) )