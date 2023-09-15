/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:35:03 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 14:38:03 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_has_1_philo(t_global_data *g_data)
{
	if (g_data->number_of_philosophers == 1)
	{
		ft_usleep(g_data->time_to_die * 1000);
		printf("%d 1 has died\n", g_data->time_to_die + 1);
		return (1);
	}
	return (0);
}

int	check_time(t_philo **philos, t_global_data *g_data)
{
	int	i;

	i = -1;
	while (++i < g_data->number_of_philosophers)
	{
		pthread_mutex_lock(&g_data->mutex_time[i]);
		if (get_time_since_last_meal(philos[i])
			> (unsigned long long) g_data->time_to_die
			&& g_data->philostate[i] != FINISHED_EATING)
		{
			pthread_mutex_unlock(&g_data->mutex_time[i]);
			make_death(g_data);
			printf("%llu %d died\n", get_time_since_start(philos[i]), i + 1);
			return (0);
		}
		pthread_mutex_unlock(&g_data->mutex_time[i]);
	}
	if (check_finish(g_data))
		return (0);
	ft_usleep(1500);
	return (1);
}

int	check_finish(t_global_data *g_data)
{
	int				i;
	int				nb_philos;
	pthread_mutex_t	*mutex;

	i = 0;
	nb_philos = g_data->number_of_philosophers;
	mutex = g_data->mutex_eat;
	while (i < nb_philos)
	{
		pthread_mutex_lock(&mutex[i % nb_philos]);
		if (g_data->philostate[i] != FINISHED_EATING)
		{
			pthread_mutex_unlock(&mutex[i % nb_philos]);
			return (0);
		}
		pthread_mutex_unlock(&mutex[i % nb_philos]);
		i++;
	}
	return (1);
}

void	make_death(t_global_data *g_data)
{
	pthread_mutex_t	*mutex;
	int				i;
	int				nb_philos;

	mutex = g_data->mutex_death;
	i = -1;
	nb_philos = g_data->number_of_philosophers;
	while (++i < g_data->number_of_philosophers)
	{
		pthread_mutex_lock(&mutex[i % nb_philos]);
		g_data->philostate[i] = DEAD;
		pthread_mutex_unlock(&mutex[i % nb_philos]);
	}
}
