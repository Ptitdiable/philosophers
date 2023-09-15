/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:16:37 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 15:52:17 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	run_simulation(t_global_data *g_data)
{
	int				i;
	pthread_t		*threads_philos;
	t_philo			**philos;

	threads_philos = malloc(g_data->number_of_philosophers * sizeof(pthread_t));
	if (!threads_philos)
	{
		printf("Erreur : fail allocation memoire de threads_philos\n");
		return ;
	}
	philos = run_philos(g_data, threads_philos);
	run_monitor(philos);
	i = -1;
	while (++i < g_data->number_of_philosophers)
		pthread_join(threads_philos[i], NULL);
	destroy_mutex(g_data);
	free_all(g_data, philos, threads_philos);
}

void	run_monitor(t_philo **philos)
{
	pthread_t	*thread_monitor;

	thread_monitor = malloc(sizeof(pthread_t));
	if (!thread_monitor)
	{
		printf("Erreur : fail allocation memory thread_monitor\n");
		return ;
	}
	gettimeofday(&(philos[0]->g_data->time_start), NULL);
	pthread_mutex_lock(&philos[0]->g_data->mutex_fork[0]);
	philos[0]->g_data->can_start = 1;
	pthread_mutex_unlock(&philos[0]->g_data->mutex_fork[0]);
	if (pthread_create(thread_monitor, NULL, &monitor, philos))
	{
		printf("Erreur : fail pthread_create thread_monitor\n");
		return ;
	}
	pthread_join(*thread_monitor, NULL);
}

t_philo	**run_philos(t_global_data *g_data, pthread_t *threads)
{
	t_philo	**philos;
	int		i;

	philos = malloc(g_data->number_of_philosophers * sizeof(t_philo *));
	i = -1;
	while (++i < g_data->number_of_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			printf("Error : fail allocation memory philosophers[i]\n");
			free(philos[i]);
			free(threads);
			return (NULL);
		}
		philos[i]->g_data = g_data;
		init_private_data(philos[i], i);
		if (pthread_create(&threads[i], NULL, &ft_routine, philos[i]))
		{
			printf("Error : fail pthread_create threads_philos \n");
			free(philos[i]);
			free(threads);
		}
	}
	return (philos);
}
