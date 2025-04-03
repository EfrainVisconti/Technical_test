#ifndef EVEN_ODD_H
# define EVEN_ODD_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

typedef enum {
    HELP,
    RUN,
    ERROR
} mode;

//check_args.c
mode    check_args(int argc, char **argv);

#endif