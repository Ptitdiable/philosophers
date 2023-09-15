/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:00:01 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/14 12:54:40 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned long long	get_time_since_start(t_philo *philo)
{
	unsigned long long	res;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	tv.tv_sec -= philo->g_data->time_start.tv_sec;
	tv.tv_usec -= philo->g_data->time_start.tv_usec;
	res = tv.tv_sec * 1000ULL + tv.tv_usec / 1000;
	return (res);
}

unsigned long long	get_time_since_last_meal(t_philo *philo)
{
	int					nb_philo;
	unsigned long long	res;

	nb_philo = philo->g_data->number_of_philosophers;
	res = get_time_since_start(philo);
	pthread_mutex_lock(&philo->g_data->mutex_time[philo->id % nb_philo]);
	res -= philo->time_last_meal;
	pthread_mutex_unlock(&philo->g_data->mutex_time[philo->id % nb_philo]);
	return (res);
}
