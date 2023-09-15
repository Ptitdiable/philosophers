/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:57:20 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/09 18:25:39 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
	{
		return (0);
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str == ' ')
		str++;
	while (ft_isdigit(*str))
	{
		res = 10 * res + (*str) - '0';
		str++;
	}
	while (*str)
	{
		if (*str != ' ')
			return (-1);
		str++;
	}
	if (res <= 0)
		return (-1);
	return (res);
}

int	args_ok(char **argv)
{
	if (argv[1] == NULL)
		return (0);
	argv++;
	while (*argv != NULL)
	{
		if (ft_atoi(*argv) == -1)
			return (0);
		argv++;
	}
	return (1);
}
