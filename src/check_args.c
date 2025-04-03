# include "../inc/even_odd.h"

static bool    is_valid_extension(const char *pathfile)
{
    char *extension = strrchr(pathfile, '.');
    if (extension == NULL)
    {
        fprintf(stderr, "Error: No extension found in the filename.\n");
        return false;
    }
    if (strcmp(extension, ".txt") != 0)
    {
        fprintf(stderr, "Error: Invalid extension found in the filename.\n");
        return false;
    }
    return true;
}

static bool    is_valid_file(const char *pathfile)
{
    FILE *file = fopen(pathfile, "r");
    if (file != NULL)
    {
        fclose(file);
        return true;
    }
    fprintf(stderr, "Error: Nonexistent or invalid file.\n");
    return false;
}

mode    check_args(int argc, char **argv)
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
            return HELP;
        else
            fprintf(stderr, "Error: Invalid parameter.\n");
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0)
        {
            if (is_valid_extension(argv[2]) && is_valid_file(argv[2]))
                return RUN;
        }
        else
            fprintf(stderr, "Error: Invalid parameter.\n");
    }
    else
        fprintf(stderr, "Error: Invalid number of parameters.\n");
    return ERROR;
}