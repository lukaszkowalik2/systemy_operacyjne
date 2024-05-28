#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS 5
#define ITERATIONS 3
#define XMAX 45
#define YMAX 20

pthread_mutex_t mutex;

int counter = 0;

void gotoxy(unsigned x, unsigned y) {
  printf("\033[%d;%dH\033[2K", y, x);
}

void* thread_function(void* arg) {
  int thread_id = *((int*)arg);

  for (int i = 0; i < ITERATIONS; i++) {
    gotoxy(1, thread_id + 1);
    printf("Wątek %d: sekcja prywatna\n", thread_id + 1);
    sleep(1);

    int lock_result = pthread_mutex_lock(&mutex);
    if (lock_result != 0) {
      fprintf(stderr, "Błąd przy próbie zablokowania muteksu: %s\n", strerror(lock_result));
      pthread_exit(NULL);
    }

    gotoxy(XMAX, thread_id + 1);
    printf("Wątek %d: sekcja krytyczna\n", thread_id + 1);
    counter++;
    sleep(1);

    int unlock_result = pthread_mutex_unlock(&mutex);
    if (unlock_result != 0) {
      fprintf(stderr, "Błąd przy próbie odblokowania muteksu: %s\n", strerror(unlock_result));
      pthread_exit(NULL);
    }
    gotoxy(1, thread_id + 1);
    printf("Wątek %d: sekcja prywatna\n", thread_id + 1);
    sleep(1);
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[NUM_THREADS];
  int thread_ids[NUM_THREADS];

  int init_result = pthread_mutex_init(&mutex, NULL);
  if (init_result != 0) {
    fprintf(stderr, "Nie udało się zainicjować muteksu: %s\n", strerror(init_result));
    exit(EXIT_FAILURE);
  }

  system("clear");
  for (int i = 0; i < NUM_THREADS; i++) {
    thread_ids[i] = i;
    int create_result = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    if (create_result != 0) {
      fprintf(stderr, "Nie udało się utworzyć wątku: %s\n", strerror(create_result));
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    int join_result = pthread_join(threads[i], NULL);
    if (join_result != 0) {
      fprintf(stderr, "Nie udało się dołączyć wątku: %s\n", strerror(join_result));
      exit(EXIT_FAILURE);
    }
  }

  printf("\nWartość wspólnego licznika: %d\n", counter);
  if (counter == NUM_THREADS * ITERATIONS) {
    printf("Wartość jest poprawna.\n");
  } else {
    printf("Wartość jest niepoprawna.\n");
  }

  int destroy_result = pthread_mutex_destroy(&mutex);
  if (destroy_result != 0) {
    fprintf(stderr, "Nie udało się zniszczyć muteksu: %s\n", strerror(destroy_result));
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
