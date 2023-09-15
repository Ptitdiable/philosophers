/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:11:11 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 15:41:09 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->g_data->number_of_philosophers == 1)
	{
		printf("0 1 has taken a fork\n");
		return (NULL);
	}
	wait_for_start(philo);
	if (philo->id % 2 == 0)
		ft_usleep(500);
	while (1)
	{
		if (take_both_fork(philo))
			return (NULL);
		if (eat_spaghetti(philo))
			return (NULL);
		if (release_both_fork(philo))
			return (NULL);
		if (philo_sleep(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
	}
}

void	wait_for_start(t_philo *philo)
{
	int				nb_philos;
	int				should_continue;
	pthread_mutex_t	*mutex;

	nb_philos = philo->g_data->number_of_philosophers;
	should_continue = 1;
	mutex = philo->g_data->mutex_fork;
	while (should_continue)
	{
		pthread_mutex_lock(&mutex[0]);
		if (philo->g_data->can_start)
			should_continue = 0;
		pthread_mutex_unlock(&mutex[0]);
	}
}

void	*monitor(void *param)
{
	t_philo				**philos;
	t_global_data		*g_data;

	philos = (t_philo **)param;
	g_data = philos[0]->g_data;
	if (check_has_1_philo(g_data))
		return (NULL);
	while (1)
	{
		if (!check_time(philos, g_data))
			return (NULL);
	}
}
