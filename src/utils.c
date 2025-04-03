# include "../inc/even_odd.h"

void free_aux(Program *program)
{
    if (program->even)
    {
        free_list(*program->even);
        free(program->even);
    }

    if (program->odd)
    {
        free_list(*program->odd);
        free(program->odd);
    }

    if (program->threads)
    {
        for (int i = 0; i < program->thread_num; i++)
            free(program->threads[i].numbers_received);
        free(program->threads);
    }
}

void    free_exit(Program *program)
{
    free_aux(program);
    pthread_mutex_destroy(&(program->even_mutex));
    pthread_mutex_destroy(&(program->odd_mutex));
    exit(EXIT_FAILURE);
}