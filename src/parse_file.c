# include "../inc/even_odd.h"

static void get_key_value(char *line)
{

}

static void    parse_buffer(char *buffer, Program *program)
{
    char *line = strtok(buffer, "\n");

    while (line != NULL)
    {
        get_key_value(line);
        line = strtok(NULL, "\n");
    }
}

bool    parse_file(char *pathfile, Program *program)
{
    char    buffer[FILE_BUFFER];

    FILE *file = fopen(pathfile, "r");
    if (file == NULL)
        return false;

    size_t readed = fread(buffer, 1, sizeof(buffer), file);
    parse_buffer(buffer, program);

    fclose(file);
}