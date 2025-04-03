# include "../inc/even_odd.h"

int main(int argc, char **argv)
{
    mode execution_mode = check_args(argc, argv);
    if (execution_mode == ERROR)
        return EXIT_FAILURE;
    if (execution_mode == HELP)
    {
        printf("Usage: %s path/to/file.txt\n", argv[0]);
        return EXIT_SUCCESS;
    }
    printf("Valido!\n");
    return EXIT_SUCCESS;
}