# include "../inc/even_odd.h"

//int pthread_detach(pthread_t thread);

//int pthread_mutex_lock(pthread_mutex_t *mutex);
//int pthread_mutex_unlock(pthread_mutex_t *mutex);


static void	*numbers_routine(void *arg)
{
	Threads	*thread = (Threads *)arg;
    
    int i = 0;
    while (thread->numbers_received[i] != NULL)
    {
        if (thread->numbers_received[i] % 2 == 0)
        {
            pthread_mutex_lock(thread->even_mutex);
            add_new_node(thread->even, thread->numbers_received[i]);
            pthread_mutex_unlock(thread->even_mutex); 
        }
        else
        {
            pthread_mutex_lock(thread->odd_mutex);
            add_new_node(thread->odd, thread->numbers_received[i]);
            pthread_mutex_unlock(thread->odd_mutex); 
        }
    }
	return (arg);
}

bool init_mutexes(Program *program)
{
    if (pthread_mutex_init(&(program->even_mutex), NULL) != 0)
    {
        fprintf(stderr, "Error: Occurred while creating mutex.\n");
        return false;
    }

    if (pthread_mutex_init(&(program->odd_mutex), NULL) != 0)
    {
        fprintf(stderr, "Error: Occurred while creating mutex.\n");
        pthread_mutex_destroy(&(program->even_mutex));
        return false;
    }

    return true;
}

bool create_threads(Program *program)
{
    program->threads = malloc(program->thread_num * sizeof(pthread_t));
    if (program->threads == NULL)
    {
        fprintf(stderr, "Error: Occurred while creating threads.\n");
        return false;
    }

    int i = 0;
    while (i < program->thread_num)
	{
		if (pthread_create(&(program->threads->pthread[i]), NULL, &numbers_routine, (void *)program->threads[i]))
		{
            fprintf(stderr, "Error: Occurred while creating threads.\n");
            return false;
        }
        i++;
	}

    i = 0;
    while (i < program->thread_num)
	{
		if (pthread_join(program->threads[i], NULL) != 0)
        {
            fprintf(stderr, "Error: Occurred while joining threads.\n");
            return false;
        }
        i++;
	}

    return true;
}