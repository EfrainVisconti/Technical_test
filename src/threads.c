# include "../inc/even_odd.h"

static void	*numbers_routine(void *arg)
{
	Threads	*thread = (Threads *)arg;
    
    int i = 0;
    while (i < thread->list_size)
    {
        if (thread->numbers_received[i] % 2 == 0)
        {
            pthread_mutex_lock(thread->even_mutex);
            add_new_node(thread->even, thread->numbers_received[i]);
            //printf("Number: %d added to even by thread: %d\n", thread->numbers_received[i], thread->index); //to debug
            pthread_mutex_unlock(thread->even_mutex); 
        }
        else
        {
            pthread_mutex_lock(thread->odd_mutex);
            add_new_node(thread->odd, thread->numbers_received[i]);
            //printf("Number: %d added to odd by thread: %d\n", thread->numbers_received[i], thread->index); //to debug
            pthread_mutex_unlock(thread->odd_mutex); 
        }
        i++;
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

void create_threads(Program *program)
{
    int i = 0;
    while (i < program->thread_num)
	{
		if (pthread_create(&(program->threads[i].pthread), NULL, &numbers_routine, (void *)&(program->threads[i])) != 0)
		{
            fprintf(stderr, "Error: Occurred while creating threads.\n");
            break;
        }
        i++;
	}

    int j = 0;
    int flag_error = 0;
    while (j < i)
	{
		if (pthread_join(program->threads[j].pthread, NULL) != 0)
        {
            fprintf(stderr, "Error: Occurred while joining threads.\n");
            flag_error = 1;
        }
        j++;
	}
    if (i < program->thread_num || flag_error)
        free_exit(program);
}