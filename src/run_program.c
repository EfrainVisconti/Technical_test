# include "../inc/even_odd.h"

static void    fisher_yates_shuffle(int *array, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1); 
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

static int *generate_random_list(Program *program)
{
    int *list = malloc(program->numbers_per_thread * sizeof(int));
    if (list == NULL)
    {
        fprintf(stderr, "Error: Occurred while generating random numbers.\n");
        free_exit(program);
    }

    int i = 0;
    while (i < program->numbers_per_thread)
    {

        list[i] = i + 1;
        i++;
    }
   
    fisher_yates_shuffle(list, program->numbers_per_thread);

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
        fprintf(stderr, "Error: Memory allocation for threads.\n");
        exit(EXIT_FAILURE);
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
        program->threads[i].index = i + 1;
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
        printf("Position: %d --> Value: %d\n", i, list->number);
        list = list->next;
        i++;
    }
}

void    run_program(Program *program)
{
    srand(time(NULL));
    if (init_mutexes(program) == false)
        exit(EXIT_FAILURE);
    init_threads(program);
    init_numbers_received(program);
    create_threads(program);
    printf("ODD NUMBERS:\n");
    print_list(*program->odd);
    printf("EVEN NUMBERS:\n");
    print_list(*program->even);
}