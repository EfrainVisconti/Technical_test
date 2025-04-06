# include "../inc/even_odd.h"

static void trim_whitespace(char *str)
{
    char *start = str;
    while (isspace(*start))
        start++;

    char *end = start + strlen(start) - 1;
    while (end > start && isspace(*end))
        end--;

    *(end + 1) = '\0';
    memmove(str, start, end - start + 2);
}

static bool handle_keys(char *key, char *value, Program *program)
{
    if (strcmp(key, "numbers_per_thread") == 0)
    {
        char *aux;
        program->numbers_per_thread = strtol(value, &aux, 10);
        if (*aux != '\0' || program->numbers_per_thread <= 0 || program->numbers_per_thread > MAX_NUM_PER_THREAD)
        {
            fprintf(stderr, "Error: Invalid number for numbers_per_thread.\n");
            return false;
        }
        return true;
    }

    if (strcmp(key, "thread_num") == 0)
    {
        char *aux;
        program->thread_num = strtol(value, &aux, 10);
        if (*aux != '\0' || program->thread_num <= 0 || program->thread_num > MAX_THREAD_NUM)
        {
            fprintf(stderr, "Error: Invalid number for thread_num.\n");
            return false;
        }
        return true;
    }

    fprintf(stderr, "Error: Invalid line found in config file.\n");
    return false;
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

    trim_whitespace(key);
    trim_whitespace(value);

    if (handle_keys(key, value, program))
        return true;

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
