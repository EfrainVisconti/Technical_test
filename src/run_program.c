# include "../inc/even_odd.h"

//int generate_random()
//{
//    return rand();
//}

void    run_program(Program *program)
{
    //srand(time(NULL));

    init_mutexes(program);
    init_threads(program);
}