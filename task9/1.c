#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void gotoxy(unsigned x, unsigned y) {
  printf("\033[%d;%dH\033[2K", y, x);
}

void *thread_function(void *arg) {
  int thread_id = *(int *)arg;

  gotoxy(0, thread_id);
  printf("%d", thread_id);
  // while (1) {
  pthread_mutex_lock(&mutex);
  //   gotoxy(10, 2);
  //   printf("sdad ");
  //   pthread_mutex_unlock(&mutex);
  //   sleep(1);
  // }
  while (1) {
  }

  return NULL;
}

int main() {
  if (system("clear") == -1) {
    perror("Error in call to system() function");
    exit(EXIT_FAILURE);
  }

  pthread_t thread1, thread2, thread3, thread4, thread5;
  int thread_id1 = 1;
  int thread_id2 = 2;
  int thread_id3 = 3;
  int thread_id4 = 4;
  int thread_id5 = 5;

  pthread_create(&thread1, NULL, thread_function, &thread_id1);
  pthread_create(&thread2, NULL, thread_function, &thread_id2);
  pthread_create(&thread3, NULL, thread_function, &thread_id3);
  pthread_create(&thread4, NULL, thread_function, &thread_id4);
  pthread_create(&thread5, NULL, thread_function, &thread_id5);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);
  pthread_join(thread5, NULL);

  pthread_exit(thread1);
  pthread_exit(thread2);
  pthread_exit(thread3);
  pthread_exit(thread4);
  pthread_exit(thread5);

  return 0;
}
