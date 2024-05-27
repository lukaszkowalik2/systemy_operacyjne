#include "pthread.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

#define THREAD_COUNT 5
#define ITERATIONS 3
#define XMAX 45
#define YMAX 20

volatile int tickets[THREAD_COUNT];
volatile int choosing[THREAD_COUNT];

int shared_counter = 0;

void gotoxy(unsigned x, unsigned y) {
  printf("\033[%d;%dH\033[2K", y, x);
}

int max_number() {
  int max = 0;
  for (int i = 0; i < THREAD_COUNT; i++) {
    if (tickets[i] > max) {
      max = tickets[i];
    }
  }
  return max;
}

void* thread_body(void* arg) {
  long thread = (long)arg + 1;
  long index = thread - 1;  // Subtract 1 to get zero-based index
  for (int i = 0; i < ITERATIONS; i++) {
    gotoxy(1, thread);
    printf("Wątek %d: sekcja prywatna\n", thread);
    sleep(1);
    choosing[index] = 1;
    tickets[index] = max_number() + 1;
    choosing[index] = 0;

    for (int other = 0; other < THREAD_COUNT; ++other) {
      while (choosing[other]);
      while (tickets[other] != 0 && (tickets[other] < tickets[index] || (tickets[other] == tickets[index] && other < index)));
    }
    gotoxy(XMAX, thread);
    printf("Wątek %d: sekcja krytyczna\n", thread);
    shared_counter++;
    sleep(1);
    tickets[index] = 0;
    gotoxy(1, thread);
    printf("Wątek %d: sekcja prywatna\n", thread);
    sleep(1);
  }
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t threads[THREAD_COUNT];
  system("clear");
  for (int i = 0; i < THREAD_COUNT; ++i) {
    pthread_create(&threads[i], NULL, thread_body,
                   (void*)((long)i));
  }

  for (int i = 0; i < THREAD_COUNT; ++i) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
