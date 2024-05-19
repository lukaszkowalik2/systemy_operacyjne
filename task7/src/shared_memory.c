#include "shared_memory.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int create_shared_memory(const char* name, size_t size) {
  int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open (create)");
    return -1;
  }

  if (ftruncate(shm_fd, size) == -1) {
    perror("ftruncate");
    close(shm_fd);
    return -1;
  }
  return shm_fd;
}

int open_shared_memory(const char* name, size_t size) {
  int shm_fd = shm_open(name, O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open (open)");
    return -1;
  }
  return shm_fd;
}

void* map_shared_memory(int shm_fd, size_t size) {
  void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (addr == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }
  return addr;
}

void unmap_shared_memory(void* addr, size_t size) {
  if (munmap(addr, size) == -1) {
    perror("munmap");
  }
}

void close_shared_memory(int shm_fd) {
  if (close(shm_fd) == -1) {
    perror("close");
  }
}

void unlink_shared_memory(const char* name) {
  if (shm_unlink(name) == -1) {
    perror("shm_unlink");
  }
}
