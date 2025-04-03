#ifndef PROGRAM_H
# define PROGRAM_H

typedef struct
{
  int numbers_per_thread;
  int thread_num;
  Node *even;
  Node *odd;
  pthread_mutex_t	even_mutex;
  pthread_mutex_t	odd_mutex;
  pthread_t *threads;
} Program;

#endif