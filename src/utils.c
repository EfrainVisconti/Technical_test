# include "../inc/even_odd.h"

void    free_exit(Program *program)
{
    free(program->threads);
    pthread_mutex_destroy(&(program->even_mutex));
    pthread_mutex_destroy(&(program->odd_mutex));
    exit(EXIT_FAILURE);
}