/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:30:54 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 10:56:09 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_global_data	*g_data;

	if (!args_ok(argv) || (argc != 5 && argc != 6))
	{
		printf("Erreur : nombre d'arguments ou format incorrect\n");
		return (1);
	}
	g_data = init_data(argc, argv);
	if (!g_data)
		return (1);
	run_simulation(g_data);
	return (0);
}
