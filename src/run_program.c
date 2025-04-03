# include "../inc/even_odd.h"

static bool handle_duplicate(int *list, int number, int size)
{
    int i = 0;
    while (i < size)
    {
        if (list[i] == number)
            return false;
        i++;
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
    program->threads = malloc(program->thread_num * sizeof(Threads));
    if (program->threads == NULL)
    {
        fprintf(stderr, "Error: malloc().\n");
        free_exit(program);
    }

    program->even = malloc(sizeof(Node *));
    program->odd = malloc(sizeof(Node *));
    if (program->even == NULL || program->odd == NULL)
    {
        fprintf(stderr, "Error: Memory allocation for lists.\n");
        free_exit(program);
    }
    *program->even = NULL;
    *program->odd = NULL;

    int i = 0;
    while (i < program->thread_num)
    {
        program->threads[i].even_mutex = &program->even_mutex;
        program->threads[i].odd_mutex = &program->odd_mutex;
        program->threads[i].even = program->even;
        program->threads[i].odd = program->odd;
        program->threads[i].list_size = program->numbers_per_thread;
        i++;
    }

}

void print_list(Node *list)
{
    int i = 0;
    while (list != NULL)
    {
        printf("Position: %d, --> Value: %d\n", i, list->number);
        list = list->next;
        i++;
    }
}

void    run_program(Program *program)
{
    if (init_mutexes(program) == false)
        free_exit(program);
    init_threads(program);
    init_numbers_received(program);
    create_threads(program);
    printf("ODD NUMBERS:\n");
    print_list(*program->odd);
    printf("EVEN NUMBERS:\n");
    print_list(*program->even);
}