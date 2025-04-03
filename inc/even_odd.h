#ifndef EVEN_ODD_H
# define EVEN_ODD_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>

typedef struct
{
  int numbers_per_thread;
  int thread_num;
} Program;

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

#endif