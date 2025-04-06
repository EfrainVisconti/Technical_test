# include "../inc/even_odd.h"

int main(int argc, char **argv)
{
    Program program = {0};

    mode execution_mode = check_args(argc, argv);
    if (execution_mode == ERROR)
        return EXIT_FAILURE;
    if (execution_mode == HELP)
    {
        printf("Usage:\n");
        printf("  %s -f PATH\n", argv[0]);
        printf("  %s --file PATH\n", argv[0]);
        printf("\nOptions:\n");
        printf("  -f, --file PATH   Path to configuration file, must be .txt\n");
        return EXIT_SUCCESS;
    }

    if (parse_file(argv[2], &program) == false)
        return EXIT_FAILURE;

    printf("NUM_PER_THREAD: %d\nTHREAD_NUM: %d\n", program.numbers_per_thread, program.thread_num);
    run_program(&program);

    free_aux(&program);
    destroy_mutexes(&program);

    return EXIT_SUCCESS;
}