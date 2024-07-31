#include "philo.h"


int is_full(t_queue* q)
{
	return (q->size == q->capacity);
}

int is_empty(t_queue* q) 
{
	return (q->size == 0);
}

t_queue	*create_queue(t_queue *q, t_info *info)
{
	q = malloc(sizeof(t_queue));
	if (q == NULL)
		return ;
	q->size = 0;
	q->capacity = info->input.num_of_philos;
	q->front = 0;
	q->back = 0;
	q->plist = malloc(q->capacity * sizeof(int));
	return (q);
}

int	enqueue(t_queue *q, int philo_id)
{
	if (is_full(q))
		return 1;
	q->back = (q->back + 1) % q->capacity;
	q->plist[q->back] = philo_id;
	q->size = q->size + 1;
	return 0;
}

int	dequeue(t_queue *q, int philo_id)
{
	if (is_empty(q))
		return 1;
	philo_id = q->plist[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size = q->size - 1;
	return 0;
}

int	front(t_queue *q)
{
	if (is_empty(q))
		return INT_MIN;
	return (q->plist[q->front]);
}

int	back(t_queue *q)
{
	if (is_empty(q))
		return INT_MIN;
	return (q->plist[q->back]);
}


void	free_queue(t_queue *q)
{
	if (q != NULL) 
	{
		free(q->plist);
		free(q);
	}
}