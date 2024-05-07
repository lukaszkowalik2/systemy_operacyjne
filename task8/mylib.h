#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef _MYLIB_H_
#define _MYLIB_H_

#define QUEUE_NAME "./output/MQ"
#define MAX_SIZE sizeof(int)
#define MSG_STOP "exit"

#endif