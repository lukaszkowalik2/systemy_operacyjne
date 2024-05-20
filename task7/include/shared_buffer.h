#ifndef SHARED_BUFFER_H
#define SHARED_BUFFER_H

#include <semaphore.h>

#define NELE 20
#define NBUF 5

typedef struct {
  char bufor[NBUF][NELE];
  int wstaw, wyjmij;
} SegmentPD;

#define SEM_WRITE_TO_SHM "/SEM_WRITE_TO_SHM"
#define SEM_READ_FROM_SHM "/SEM_READ_FROM_SHM"

#define SHM_NAME "/shared_buffer"

#endif
