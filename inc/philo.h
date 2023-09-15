/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:52 by flmartin          #+#    #+#             */
/*   Updated: 2023/09/15 15:18:28 by flmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_philostate
{
	ALIVE,
	DEAD,
	FINISHED_EATING
}	t_PhiloState;

typedef struct s_global_data
{
	int				can_start;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	struct timeval	time_start;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_time;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*mutex_death;
	t_PhiloState	*philostate;
}	t_global_data;

typedef struct s_philo
{
	t_global_data		*g_data;
	int					id;
	int					number_have_eaten;
	unsigned long long	time_last_meal;
}	t_philo;

void				*ft_routine(void *param);
void				*monitor(void *param);
void				run_simulation(t_global_data *g_data);
void				wait_for_start(t_philo *philo);
void				run_monitor(t_philo **philos);
void				make_death(t_global_data *g_data);
void				init_private_data(t_philo *philo_args, int i);
void				init_g_data(t_global_data *g_data, int argc, char **argv);
int					init_philo_state(t_global_data *g_data);
int					check_death(t_philo *philo);
int					check_time(t_philo **philos, t_global_data *g_data);
int					check_has_1_philo(t_global_data *g_data);
int					check_finish(t_global_data *g_data);
int					check_has_finish_eating(t_philo *philo);
int					take_both_fork(t_philo *philo);
int					take_first_fork(t_philo *philo);
int					take_second_fork(t_philo *philo);
int					release_both_fork(t_philo *philo);
int					eat_spaghetti(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					think(t_philo *philo);
unsigned long long	actual_time(void);
void				ft_usleep(unsigned long long time);
void				free_all(t_global_data *g, t_philo **p, pthread_t *theads);
void				free_mutex(t_global_data *g_data);
void				free_philos(t_global_data *g_data, t_philo **philos);
void				destroy_mutex(t_global_data *g_data);
int					ft_isdigit(char c);
int					ft_atoi(char *str);
int					args_ok(char **argv);
int					help_init_mutex(int nb_philos, pthread_mutex_t *ptr_mutex);
unsigned long long	get_time_since_start(t_philo *philo);
unsigned long long	get_time_since_last_meal(t_philo *philo);
t_global_data		*init_data(int argc, char **argv);
pthread_mutex_t		*init_mutex(int number_of_philosophers);
t_philo				**run_philos(t_global_data *g_data, pthread_t *threads);

#endif
