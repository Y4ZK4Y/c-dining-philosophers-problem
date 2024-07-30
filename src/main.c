#include "philo.h"



// void *func(void *arg)
// {
//     t_info *info = (t_info *)arg;

//     pthread_mutex_lock(&info->mutex);
//     printf("hello from func.\n");
//     pthread_mutex_unlock(&info->mutex);
//     pthread_mutex_unlock(&info->mutex);
//     usleep(100); // Sleep for a short time to avoid busy waiting
    

//     return NULL;
// }


// int main(int argc, char **argv)
// {
//     t_input input;
//     int i;
//     t_info info;


//     if (argc != 5)
//     {
//         printf("arg aint right\n");
//         return (1);
//     }

//     input = parse(argc, argv);
//     if (input.error == 1)
//     {
//         printf("parsing failed.\n");
//         return (1);
//     }
//     bzero(&info, sizeof(info));
//     pthread_t p[5];
//     pthread_mutex_init(&info.mutex, NULL);
//     for (i = 0; i < 5; i++)
//     {
//         pthread_create(&p[i], NULL, &func, &info);
//         printf("thread %d started: %p\n", i, p[i]);
//     }
//     for (i = 0; i < 5; i++)
//     {
//         pthread_join(p[i], NULL);
//         printf("thread %d joined: %p\n", i, p[i]);
//     }
//     pthread_mutex_destroy(&info.mutex);
//     return (0);

// }


int main(int argc, char *argv[])
{
	t_info	info;

	bzero(&info, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
	{
		printf("parsing func failed\n");
		return (1);
	}

}