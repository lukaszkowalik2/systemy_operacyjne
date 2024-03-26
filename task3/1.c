#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int);

int main() {
  int pid = getpid();
  printf("---------------------------------------------------");
  printf("PID: %d", pid);
  printf("---------------------------------------------------");
  signal(SIGINT, handler);
  while (true) {
    pause();
  }
  exit(EXIT_SUCCESS);
}

void handler(int sig) {
  char c;

  signal(sig, SIG_IGN);
  printf("\n Do you really want to quit? [y/n]");
  c = getchar();
  if (c == 'y' || c == 'Y') {
    exit(EXIT_SUCCESS);
  } else {
    signal(SIGINT, handler);
  }
  getchar();
}
