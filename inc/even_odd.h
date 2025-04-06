#ifndef EVEN_ODD_H
# define EVEN_ODD_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <ctype.h>
# include <pthread.h>
# include <time.h>

# include "node.h"
# include "program.h"

typedef enum {
    HELP,
    RUN,
    ERROR
} mode;

# define MAX_THREAD_NUM 1000
# define MAX_NUM_PER_THREAD 10000000

//check_args.c
mode    check_args(int argc, char **argv);

//parse_file.c
bool    parse_file(char *pathfile, Program *program);

//run_program.c
void  run_program(Program *program);

//threads.c
bool  init_mutexes(Program *program);
void  create_threads(Program * program);

//utils.c
void  destroy_mutexes(Program *program);
void  free_exit(Program *program);
void  free_aux(Program *program);

#endif