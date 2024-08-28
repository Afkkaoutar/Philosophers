/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:35 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/08/28 04:30:00 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_PHILOSOPHERS 200

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philosophers
{
	pthread_t				threads;
	int						id;
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_times_each_philosopher_must_eat;
	long long				last_meal;
	pthread_mutex_t			*fork;
	pthread_mutex_t			*print;
	pthread_mutex_t			*death;
	struct s_philosophers	*next;
}	t_philosophers;

void		*routine(void *rou);
void		init_philosophers(t_philosophers *philo, int num, char **av);
void		free_resources(t_philosophers *philo, int num);
void		ft_print(t_philosophers *philo, char *str);
void		action(int action, t_philosophers *philo);
void		init_philosophers(t_philosophers *philo, int num, char **av);
long long	timeinmilliseconds(void);
int			check_death(void *d);
int			ft_atoi(char *str);
int			check_death(void *d);
int			check(t_philosophers *philo);

#endif