# include "../inc/even_odd.h"

static bool handle_duplicate(int *list, int number, int size)
{
    int i = 0;
    while (i < size)
    {
        if (list[i] == number)
            return false;
    }
    return true;
}

static int *generate_random_list(Program *program)
{
    srand(time(NULL));
    int i = 0;
    int *list = malloc(program->numbers_per_thread * sizeof(int));
    if (list == NULL)
    {
        fprintf(stderr, "Error: Occurred while generating random numbers.\n");
        free_exit(program);
    }
   
    while (i < program->numbers_per_thread)
    {
        int number = rand();
        if (handle_duplicate(list, number, i) == false)
            continue;
        list[i] = number;
        i++;
    }

    return list;
}

static void init_numbers_received(Program *program)
{
    int i = 0;

    while (i < program->thread_num)
    {
        program->threads[i].numbers_received = generate_random_list(program);
        i++;
    }
}

static void    init_threads(Program *program)
{
    int i = 0;

    while (i < program->thread_num)
    {
        program->threads[i].even_mutex = program->even_mutex;
        program->threads[i].odd_mutex = program->odd_mutex;
        program->threads[i].even = program->even;
        program->threads[i].odd = program->odd;
        i++;
    }

}

void    run_program(Program *program)
{
    init_mutexes(program);
    init_threads(program);
    init_numbers_received(program);
    create_threads(program);
}