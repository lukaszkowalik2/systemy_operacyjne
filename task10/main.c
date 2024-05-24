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
  for (int i = 0; i < ITERATIONS; i++) {
    gotoxy(1, thread);
    printf("Wątek %d: sekcja prywatna\n", thread);
    sleep(1);
    choosing[thread] = 1;
    tickets[thread] = max_number() + 1;
    choosing[thread] = 0;

    for (int other = 0; other < THREAD_COUNT; ++other) {
      while (choosing[other]);
      while (tickets[other] != 0 && (tickets[other] < tickets[thread] || (tickets[other] == tickets[thread] && other < thread)));
    }
    gotoxy(XMAX, thread);
    printf("Wątek %d: sekcja krytyczna\n", thread);
    shared_counter++;
    sleep(1);
    tickets[thread] = 0;
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

// void* thread_function(void* arg) {
//   int thread_id = *((int*)arg);
//   int private_counter = 0;

//   for (int i = 0; i < ITERATIONS; i++) {
//     gotoxy(1, thread_id + 1);
//     printf("Wątek %d: sekcja prywatna\n", thread_id + 1);
//     sleep(1);
//     choosing[thread_id] = true;
//     number[thread_id] = max_number() + 1;
//     choosing[thread_id] = false;

//     for (int j = 0; j < NUM_THREADS; j++) {
//       while (choosing[j]);
//       while (number[j] != 0 && (number[j], j) < (number[i], i));
//     }

//     int lock_result = pthread_mutex_lock(&mutex);
//     if (lock_result != 0) {
//       fprintf(stderr, "Błąd przy próbie zablokowania muteksu: %s\n", strerror(lock_result));
//       pthread_exit(NULL);
//     }

//     gotoxy(XMAX, thread_id + 1);
//     printf("Wątek %d: sekcja krytyczna\n", thread_id + 1);
//     private_counter = shared_counter;
//     private_counter++;
//     sleep(1);
//     shared_counter = private_counter;

//     int unlock_result = pthread_mutex_unlock(&mutex);
//     if (unlock_result != 0) {
//       fprintf(stderr, "Błąd przy próbie odblokowania muteksu: %s\n", strerror(unlock_result));
//       pthread_exit(NULL);
//     }
//     number[thread_id] = 0;

//     gotoxy(1, thread_id + 1);
//     printf("Wątek %d: sekcja prywatna\n", thread_id + 1);
//     sleep(1);
//   }
//   pthread_exit(NULL);
// }

// int main() {
//   pthread_t threads[NUM_THREADS];
//   int thread_ids[NUM_THREADS];

//   int init_result = pthread_mutex_init(&mutex, NULL);
//   if (init_result != 0) {
//     fprintf(stderr, "Nie udało się zainicjować muteksu: %s\n", strerror(init_result));
//     exit(EXIT_FAILURE);
//   }

//   system("clear");
//   for (int i = 0; i < NUM_THREADS; i++) {
//     thread_ids[i] = i;
//     int create_result = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
//     if (create_result != 0) {
//       fprintf(stderr, "Nie udało się utworzyć wątku: %s\n", strerror(create_result));
//       exit(EXIT_FAILURE);
//     }
//   }

//   for (int i = 0; i < NUM_THREADS; i++) {
//     int join_result = pthread_join(threads[i], NULL);
//     if (join_result != 0) {
//       fprintf(stderr, "Nie udało się dołączyć wątku: %s\n", strerror(join_result));
//       exit(EXIT_FAILURE);
//     }
//   }

//   printf("\nWartość wspólnego licznika: %d\n", shared_counter);
//   if (shared_counter == NUM_THREADS * ITERATIONS) {
//     printf("Wartość jest poprawna.\n");
//   } else {
//     printf("Wartość jest niepoprawna.\n");
//   }

//   int destroy_result = pthread_mutex_destroy(&mutex);
//   if (destroy_result != 0) {
//     fprintf(stderr, "Nie udało się zniszczyć muteksu: %s\n", strerror(destroy_result));
//     exit(EXIT_FAILURE);
//   }

//   exit(EXIT_SUCCESS);
// }
