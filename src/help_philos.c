/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:30:55 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 14:30:28 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_first_fork(t_philo *philo)
{
	int				nb_philo;
	pthread_mutex_t	*mutex;

	nb_philo = philo->g_data->number_of_philosophers;
	mutex = philo->g_data->mutex_fork;
	pthread_mutex_lock(&mutex[philo->id % nb_philo]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&mutex[philo->id % nb_philo]);
		return (0);
	}
	printf("%llu %d has taken a fork\n", get_time_since_start(philo), philo->id);
	pthread_mutex_lock(&mutex[(philo->id + 1) % nb_philo]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&mutex[philo->id % nb_philo]);
		pthread_mutex_unlock(&mutex[philo->id + 1 % nb_philo]);
		return (0);
	}
	printf("%llu %d has taken a fork\n", get_time_since_start(philo), philo->id);
	return (1);
}

int	take_second_fork(t_philo *philo)
{
	int				nb_philo;
	pthread_mutex_t	*mutex;

	nb_philo = philo->g_data->number_of_philosophers;
	mutex = philo->g_data->mutex_fork;
	pthread_mutex_lock(&mutex[(philo->id + 1) % nb_philo]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&mutex[(philo->id + 1) % nb_philo]);
		return (0);
	}
	printf("%llu %d has taken a fork\n", get_time_since_start(philo), philo->id);
	pthread_mutex_lock(&mutex[philo->id % nb_philo]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&mutex[(philo->id + 1) % nb_philo]);
		pthread_mutex_unlock(&mutex[philo->id % nb_philo]);
		return (0);
	}
	printf("%llu %d has taken a fork\n", get_time_since_start(philo), philo->id);
	return (1);
}

int	check_death(t_philo *philo)
{
	int				nb_philos;
	pthread_mutex_t	*mutex;

	nb_philos = philo->g_data->number_of_philosophers;
	mutex = philo->g_data->mutex_death;
	pthread_mutex_lock(&mutex[philo->id % nb_philos]);
	if (philo->g_data->philostate[philo->id % nb_philos] == DEAD)
	{
		pthread_mutex_unlock(&mutex[philo->id % nb_philos]);
		return (1);
	}
	pthread_mutex_unlock(&mutex[philo->id % nb_philos]);
	return (0);
}

int	check_has_finish_eating(t_philo *philo)
{
	int				nb_philos;
	pthread_mutex_t	*mutex;

	if (philo->g_data->number_must_eat == 0)
		return (1);
	if (philo->g_data->number_must_eat == -1)
		return (0);
	nb_philos = philo->g_data->number_of_philosophers;
	mutex = philo->g_data->mutex_eat;
	pthread_mutex_lock(&mutex[philo->id % nb_philos]);
	if (philo->number_have_eaten == philo->g_data->number_must_eat)
	{
		philo->g_data->philostate[philo->id % nb_philos] = FINISHED_EATING;
		pthread_mutex_unlock(&mutex[philo->id % nb_philos]);
		return (1);
	}
	pthread_mutex_unlock(&mutex[philo->id % nb_philos]);
	return (0);
}
