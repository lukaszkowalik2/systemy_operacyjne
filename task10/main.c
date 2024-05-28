#include <stdlib.h>
#include <stdio.h>

#define THREAD_COUNT 5
#define ITERATIONS 3
#define XMAX 45
#define YMAX 20

volatile int tickets[THREAD_COUNT];
volatile int choosing[THREAD_COUNT];

int counter = 0;

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

void* thread_function(void* arg) {
  int thread = *((int*)arg) ;
  for (int i = 0; i < ITERATIONS; i++) {
    gotoxy(1, thread + 1);
    printf("Wątek %d: sekcja prywatna\n", thread +1);
    sleep(1);
    
    choosing[thread] = 1;
    tickets[thread] = max_number() + 1;
    choosing[thread] = 0;

    for (int other = 0; other < THREAD_COUNT; ++other) {
      while (choosing[other]);
      while (tickets[other] != 0 && (tickets[other] < tickets[index] || (tickets[other] == tickets[index] && other < index)));
    }

    gotoxy(XMAX, thread + 1);
    printf("Wątek %d: sekcja krytyczna\n", thread + 1);

    counter++;
    sleep(1);
    tickets[thread] = 0;

    gotoxy(1, thread + 1);
    printf("Wątek %d: sekcja prywatna\n", thread + 1);

    sleep(1);
  }
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t threads[THREAD_COUNT];
  int thread_ids[THREAD_COUNT];  
  system("clear");
  for (int i = 0; i < THREAD_COUNT; ++i) {
    thread_ids[i] = i;
    int create_result = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    if (create_result != 0) {
      fprintf(stderr, "Nie udało się utworzyć wątku: %s\n", strerror(create_result));
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < THREAD_COUNT; ++i) {
    int join_result = pthread_join(threads[i], NULL);
    if (join_result != 0) {
      fprintf(stderr, "Nie udało się dołączyć wątku: %s\n", strerror(join_result));
      exit(EXIT_FAILURE);
    }  
  }

  printf("\nWartość wspólnego licznika: %d\n", counter);
  if (counter == THREAD_COUNT * ITERATIONS) {
    printf("Wartość jest poprawna.\n");
  } else {
    printf("Wartość jest niepoprawna.\n");
  }

  for (int i = 0; i < THREAD_COUNT; ++i) {
    thread_ids[i] = i;
    int exit_result = pthread_exit(threads[i]);
    if (exit_result != 0) {
      fprintf(stderr, "Nie udało się usunąć wątku: %s\n", strerror(exit_result));
      exit(EXIT_FAILURE);
    }
  }

  return 0;
}
