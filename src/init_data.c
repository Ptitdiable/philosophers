/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:35:26 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 15:52:00 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_global_data	*init_data(int argc, char **argv)
{
	t_global_data	*g_data;

	g_data = malloc(sizeof(t_global_data));
	if (!g_data)
		return (NULL);
	init_g_data(g_data, argc, argv);
	g_data->mutex_fork = init_mutex(g_data->number_of_philosophers);
	g_data->mutex_time = init_mutex(g_data->number_of_philosophers);
	g_data->mutex_eat = init_mutex(g_data->number_of_philosophers);
	g_data->mutex_death = init_mutex(g_data->number_of_philosophers);
	if (!g_data->mutex_fork || !g_data->mutex_time || !g_data->mutex_eat
		|| !g_data->mutex_death)
		return (NULL);
	init_philo_state(g_data);
	return (g_data);
}

void	init_g_data(t_global_data *g_data, int argc, char **argv)
{
	g_data->can_start = 0;
	g_data->number_of_philosophers = ft_atoi(argv[1]);
	g_data->time_to_die = ft_atoi(argv[2]);
	g_data->time_to_eat = ft_atoi(argv[3]);
	g_data->time_to_sleep = ft_atoi(argv[4]);
	g_data->number_must_eat = -1;
	if (argc == 6)
		g_data->number_must_eat = ft_atoi(argv[5]);
}

int	init_philo_state(t_global_data *g_data)
{
	int	i;

	i = 0;
	g_data->philostate = malloc(g_data->number_of_philosophers
			* sizeof(t_PhiloState));
	if (!g_data->philostate)
		return (0);
	while (i < g_data->number_of_philosophers)
	{
		g_data->philostate[i] = ALIVE;
		i++;
	}
	return (1);
}

void	init_private_data(t_philo *philo_args, int i)
{
	philo_args->id = i + 1;
	philo_args->number_have_eaten = 0;
	philo_args->time_last_meal = 0;
}
