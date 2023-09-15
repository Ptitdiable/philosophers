/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:59:54 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 13:00:20 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

pthread_mutex_t	*init_mutex(int nb_philos)
{
	pthread_mutex_t	*ptr_mutex;

	ptr_mutex = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (!ptr_mutex)
	{
		printf("Error\n");
		free(ptr_mutex);
		return (NULL);
	}
	if (!help_init_mutex(nb_philos, ptr_mutex))
	{
		free(ptr_mutex);
		return (NULL);
	}
	return (ptr_mutex);
}

int	help_init_mutex(int nb_philos, pthread_mutex_t *ptr_mutex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nb_philos)
	{
		if (pthread_mutex_init(&ptr_mutex[i], NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&ptr_mutex[j]);
				j++;
			}
			printf("Error\n");
			return (0);
		}
		i++;
	}
	return (1);
}
