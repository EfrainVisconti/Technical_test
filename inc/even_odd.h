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

# define FILE_BUFFER 1024

//check_args.c
mode    check_args(int argc, char **argv);

//parse_file.c
bool    parse_file(char *pathfile, Program *program);

//run_program.c
void  run_program(Program *program);

//threads.c
bool  init_mutexes(Program *program);
bool  create_threads(Program * program);

//utils.c
void  free_exit(Program *program);
void free_list(Node *list);
Node  *get_last_node(Node *list);
void    add_new_node(Node **list, int number);

#endif