#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 64
#define MAX_SLEEP_TIME 2

void read_from_pipe(char *fifo_path, char *filename);
void write_to_pipe(char *fifo_path, char *filename);
void remove_fifo();

int main(int argc, char *argv[]) {
  srand(time(NULL));
  if (argc != 3) {
    printf("Użycie: %s <input_file> <output_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  atexit(remove_fifo);
  char *fifo_path = "./output/fifo";
  int fifo = mkfifo(fifo_path, 0777);

  if (fifo == -1) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }

  if (fifo == 0) {
    printf("Utworzono potok nazwany\n");
  }

  int pid = fork();

  switch (pid) {
    case -1: {
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    }
    case 0: {
      // proces potomny
      write_to_pipe(fifo_path, argv[1]);
      break;
    }
    default: {
      // proces macierzysty
      read_from_pipe(fifo_path, argv[2]);
      wait(NULL);
      break;
    }
  }
  exit(EXIT_SUCCESS);
}

void write_to_pipe(char *fifo_path, char *filename) {
  char buf[BUF_SIZE];
  size_t bytes_read;

  int read_file = open(filename, O_RDONLY);
  if (read_file == -1) {
    perror("open read_file");
    exit(EXIT_FAILURE);
  }

  int fifo = open(fifo_path, O_WRONLY);
  if (fifo == -1) {
    perror("open fifo");
    exit(EXIT_FAILURE);
  }

  while ((bytes_read = read(read_file, buf, sizeof(buf))) > 0) {
    ssize_t bytes_written = write(fifo, buf, bytes_read);
    printf("Wysłano do potoku: %s\n", buf);
    if (bytes_written == -1) {
      perror("write input_file\n");
      close(read_file);
      close(fifo);
      exit(EXIT_FAILURE);
    }
    sleep(rand() % MAX_SLEEP_TIME);
  }
  close(read_file);
  close(fifo);
}

void read_from_pipe(char *fifo_path, char *filename) {
  char buf[BUF_SIZE];
  size_t bytes_read;

  int output_file = open(filename, O_WRONLY | O_TRUNC);
  if (output_file == -1) {
    perror("open output_file");
    exit(EXIT_FAILURE);
  }

  int fifo = open(fifo_path, O_RDONLY);
  if (fifo == -1) {
    perror("open fifo");
    exit(EXIT_FAILURE);
  }

  while ((bytes_read = read(fifo, buf, sizeof(buf))) > 0) {
    ssize_t bytes_written = write(output_file, buf, bytes_read);
    printf("Odczytano z potoku: %s\n", buf);
    if (bytes_written == -1) {
      perror("write output_file\n");
      close(output_file);
      close(fifo);
      exit(EXIT_FAILURE);
    }
    sleep(rand() % MAX_SLEEP_TIME);
  }
  close(output_file);
  close(fifo);
}

void remove_fifo() {
  char *fifo_path = "./output/fifo";
  unlink(fifo_path);
}