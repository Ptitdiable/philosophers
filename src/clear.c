/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:56:30 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 14:26:36 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_all(t_global_data *g, t_philo **p, pthread_t *threads)
{
	free_mutex(g);
	free_philos(g, p);
	free(g->philostate);
	free(g);
	free(threads);
}

void	free_mutex(t_global_data *g_data)
{
	free(g_data->mutex_fork);
	free(g_data->mutex_eat);
	free(g_data->mutex_time);
	free(g_data->mutex_death);
}

void	free_philos(t_global_data *g_data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < g_data->number_of_philosophers)
		free(philos[i]);
	free(philos);
}

void	destroy_mutex(t_global_data *g_data)
{
	int	i;

	i = -1;
	while (++i < g_data->number_of_philosophers)
	{
		pthread_mutex_destroy(&g_data->mutex_fork[i]);
		pthread_mutex_destroy(&g_data->mutex_eat[i]);
		pthread_mutex_destroy(&g_data->mutex_time[i]);
		pthread_mutex_destroy(&g_data->mutex_death[i]);
	}
}
