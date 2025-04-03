# include "../inc/even_odd.h"

int main(int argc, char **argv)
{
    Program program;

    mode execution_mode = check_args(argc, argv);
    if (execution_mode == ERROR)
        return EXIT_FAILURE;
    if (execution_mode == HELP)
    {
        printf("Usage: %s path/to/file.txt\n", argv[0]);
        return EXIT_SUCCESS;
    }

    if (parse_file(argv[2], &program) == false)
        return EXIT_FAILURE;

    printf("NUM_PER_THREAD: %d\nTHREAD_NUM: %d\n", program.numbers_per_thread, program.thread_num);
    //execute();
    return EXIT_SUCCESS;
}