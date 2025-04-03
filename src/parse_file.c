# include "../inc/even_odd.h"

static bool check_value(char *line)
{
    if (line == NULL || line[0] == '\0')
        return false;

    int i = 0;
    while (line[i] != '\0')
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

    while (isspace(*value))
        value++;
    char *end = value + strlen(value) - 1;
    while (end > value && isspace(*end)) end--;
    *(end + 1) = '\0';

    if (strcmp(key, "numbers_per_thread") == 0 || strcmp(key, "numbers_per_thread ") == 0)
    {
        if (check_value(value) == true)
        {
            char *aux;
            program->numbers_per_thread = strtol(value, &aux, 10);
            if (*aux != '\0' || program->numbers_per_thread > MAX_NUM_PER_THREAD)
            {
                fprintf(stderr, "Error: Invalid number for numbers_per_thread.\n");
                return false;
            }
            return true;
        }
    }

    if (strcmp(key, "thread_num") == 0 || strcmp(key, "thread_num ") == 0)
    {
        if (check_value(value) == true)
        {
            char *aux;
            program->thread_num = strtol(value, &aux, 10);
            if (*aux != '\0' || program->thread_num > MAX_THREAD_NUM)
            {
                fprintf(stderr, "Error: Invalid number for thread_num.\n");
                return false;
            }
            return true;
        }
    }

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
    bool empty_flag = false;

    readed = getline(&line, &len, file);
    while (readed != -1)
    {
        empty_flag = true;
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

    if (empty_flag == false)
    {
        fprintf(stderr, "Error: Config file is empty.\n");
        return false;
    }
    return true;
}