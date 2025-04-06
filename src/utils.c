# include "../inc/even_odd.h"

void destroy_mutexes(Program *program)
{
    if (pthread_mutex_destroy(&(program->even_mutex)) != 0)
        fprintf(stderr, "Error: Failed to destroy even_mutex.\n");

    if (pthread_mutex_destroy(&(program->odd_mutex)) != 0)
        fprintf(stderr, "Error: Failed to destroy odd_mutex.\n");
}

void free_aux(Program *program)
{
    if (program->even)
    {
        if (*program->even)
            free_list(*program->even);
        free(program->even);
    }

    if (program->odd)
    {
        if (*program->odd)
            free_list(*program->odd);
        free(program->odd);
    }

    if (program->threads)
    {
        for (int i = 0; i < program->thread_num; i++)
        {
            if (program->threads[i].numbers_received)
                free(program->threads[i].numbers_received);
        }
        free(program->threads);
    }
}

void    free_exit(Program *program)
{
    free_aux(program);
    destroy_mutexes(program);
    exit(EXIT_FAILURE);
}