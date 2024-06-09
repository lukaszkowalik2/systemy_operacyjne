#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int get_max_ticket() {
  int max_ticket = 0;

  for (int i = 0; i < THREAD_COUNT; i++) {
    if (tickets[i] > max_ticket) {
      max_ticket = tickets[i];
    }
  }

  return max_ticket;
}

void* thread_function(void* arg) {
  int thread_id = *((int*)arg);
  for (int i = 0; i < ITERATIONS; i++) {
    gotoxy(1, thread_id + 1);
    printf("Wątek %d: sekcja prywatna\n", thread_id + 1);
    sleep(1);

    choosing[thread_id] = 1;
    tickets[thread_id] = get_max_ticket() + 1;
    choosing[thread_id] = 0;

    for (int other_thread = 0; other_thread < THREAD_COUNT; ++other_thread) {
      while (choosing[other_thread]);
      while (tickets[other_thread] != 0 &&
             (tickets[other_thread] < tickets[thread_id] ||
              (tickets[other_thread] == tickets[thread_id] && other_thread < thread_id)));
    }

    gotoxy(XMAX, thread_id + 1);
    printf("Wątek %d: sekcja krytyczna\n", thread_id + 1);

    shared_counter++;
    sleep(1);
    tickets[thread_id] = 0;

    gotoxy(1, thread_id + 1);
    printf("Wątek %d: sekcja prywatna\n", thread_id + 1);

    sleep(1);
  }

  pthread_exit(NULL);
}

int main(int argc, char** argv) {
  pthread_t threads[THREAD_COUNT];
  int thread_ids[THREAD_COUNT];

  int system_result = system("clear");
  if (system_result == -1) {
    perror("systm(\"clear\")");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < THREAD_COUNT; ++i) {
    thread_ids[i] = i;
    int create_result = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    if (create_result != 0) {
      fprintf(stderr, "Nie udało się utworzyć wątku %d: %s\n", i, strerror(create_result));
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < THREAD_COUNT; ++i) {
    int join_result = pthread_join(threads[i], NULL);
    if (join_result != 0) {
      fprintf(stderr, "Nie udało się dołączyć wątku %d: %s\n", i, strerror(join_result));
      exit(EXIT_FAILURE);
    }
  }

  printf("\nWartość wspólnego licznika: %d\n", shared_counter);
  if (shared_counter == THREAD_COUNT * ITERATIONS) {
    printf("Wartość jest poprawna.\n");
  } else {
    printf("Wartość jest niepoprawna.\n");
  }

  return 0;
}
