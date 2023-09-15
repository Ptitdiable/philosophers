/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:57:56 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 15:59:58 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_both_fork(t_philo *philo)
{
	int				nb_philo;
	pthread_mutex_t	*mutex;

	nb_philo = philo->g_data->number_of_philosophers;
	mutex = philo->g_data->mutex_fork;
	if (philo->id % 2)
	{
		if (!take_first_fork(philo))
			return (1);
	}
	else
	{
		if (!take_second_fork(philo))
			return (1);
	}
	return (0);
}

int	release_both_fork(t_philo *philo)
{
	int				nb_philo;
	pthread_mutex_t	*mutex;

	nb_philo = philo->g_data->number_of_philosophers;
	mutex = philo->g_data->mutex_fork;
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&mutex[philo->id % nb_philo]);
		pthread_mutex_unlock(&mutex[(philo->id + 1) % nb_philo]);
	}
	else
	{
		pthread_mutex_unlock(&mutex[(philo->id + 1) % nb_philo]);
		pthread_mutex_unlock(&mutex[philo->id % nb_philo]);
	}
	return (0);
}

int	eat_spaghetti(t_philo *philo)
{
	int				nb_philo;

	nb_philo = philo->g_data->number_of_philosophers;
	if (check_death(philo))
		return (1);
	printf("%llu %d is eating\n", get_time_since_start(philo), philo->id);
	pthread_mutex_lock(&philo->g_data->mutex_time[philo->id % nb_philo]);
	philo->time_last_meal = get_time_since_start(philo);
	pthread_mutex_unlock(&philo->g_data->mutex_time[philo->id % nb_philo]);
	pthread_mutex_lock(&philo->g_data->mutex_eat[philo->id % nb_philo]);
	philo->number_have_eaten++;
	pthread_mutex_unlock(&philo->g_data->mutex_eat[philo->id % nb_philo]);
	if (check_has_finish_eating(philo))
	{
		release_both_fork(philo);
		return (1);
	}
	ft_usleep(philo->g_data->time_to_eat * 1000);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	unsigned long long	start_time;

	start_time = actual_time();
	if (check_death(philo))
		return (1);
	printf("%llu %d is sleeping\n", get_time_since_start(philo), philo->id);
	while ((actual_time() - start_time)
		< (unsigned long long) philo->g_data->time_to_sleep * 1000)
	{
		if (check_death(philo))
			return (1);
	}
	return (0);
}

int	think(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	printf("%llu %d is thinking\n", get_time_since_start(philo), philo->id);
	ft_usleep(2000);
	return (0);
}
