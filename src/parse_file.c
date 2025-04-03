# include "../inc/even_odd.h"

static bool check_value(char *line)
{
    if (line == NULL)
        return false;

    int i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (!isdigit(line[i]) && !isspace(line[i]))
            return false;
        i++;
    }
    return true;
}

static bool parse_line(char *line, Program *program)
{
    char *key;
    char *value;

    key = strtok(line, "=");
    value = strtok(NULL, "=");
    if (key == NULL || value == NULL)
    {
        fprintf(stderr, "Error: Occurred while parsing file\n");
        return false;
    }
    
    if (strcmp(key, "numbers_per_thread") == 0 || strcmp(key, "numbers_per_thread ") == 0)
    {
        if (check_value(value) == true)
        {
            program->numbers_per_thread = atoi(value);
            return true;
        }
    }
    if (strcmp(key, "thread_num") == 0 || strcmp(key, "thread_num ") == 0)
    {
        if (check_value(value) == true)
        {
            program->thread_num = atoi(value);
            return true;
        }
    }
    printf("%s\n", line);
    fprintf(stderr, "Error: Invalid line found in config file.\n");
    return false;
}

bool parse_file(char *pathfile, Program *program)
{
    FILE *file = fopen(pathfile, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: While opening config file.\n");
        return false;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t readed;

    readed = getline(&line, &len, file);
    while (readed != -1)
    {
        if (parse_line(line, program) == false)
        {
            free(line);
            fclose(file);
            return false;
        }
        readed = getline(&line, &len, file);
    }

    free(line);
    fclose(file);
    return true;
}