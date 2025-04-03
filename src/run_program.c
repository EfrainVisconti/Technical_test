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
        free_exit(program);
        
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
        program->numbers_received[i] = generate_random_list(program);
        i++;
    }
}

void    run_program(Program *program)
{
    init_mutexes(program);
    init_threads(program);
    init_numbers_received(program);
    


}