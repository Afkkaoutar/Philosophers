/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:38:57 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/15 01:40:10 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_philosophers *program, char *str)
{
	int	time;

	time = 0;
	pthread_mutex_lock(program->print);
	time = timeinmilliseconds();
	printf("%d philo %d %s\n", time, program->id, str);
	pthread_mutex_unlock(program->print);
}

void	action(int action, t_philosophers *program)
{
	long	begin;

	begin = timeinmilliseconds();
	pthread_mutex_lock(program->death);
	while (timeinmilliseconds() - begin < action)
	{
		pthread_mutex_unlock(program->death);
		usleep(100);
		pthread_mutex_lock(program->death);
	}
	pthread_mutex_unlock(program->death);
	return ;
}

int	check(t_philosophers *program)
{
	pthread_mutex_lock(program->death);
	if (timeinmilliseconds() - program->last_meal > program->time_to_die)
	{
		pthread_mutex_unlock(program->death);
		return (1);
	}
	pthread_mutex_unlock(program->death);
	return (0);
}

int	check_death(void *d)
{
	int		how_many;
	t_philosophers	*program;

	program = (t_philosophers *)d;
	how_many = program->number_of_philosophers;
	while (1)
	{
		if (check(program) == 1)
			return (program->id);
		pthread_mutex_lock(program->death);
		while (program->number_of_meal != -1 && program->number_of_meal == 0)
		{
			how_many--;
			if (how_many == 0)
				return (0);
			program = program->next;
		}
		pthread_mutex_unlock(program->death);
		how_many = program->number_of_philosophers;
		program = program->next;
	}
	usleep(100);
	return (-1);
}

void    *routine(void *routin)
{
    t_philosophers *program;

    program = (t_philosophers * )routin;
    if(program->id % 2 == 1)
        usleep(program->time_to_eat);
    while(1)
    {
        pthread_mutex_lock(program->fork);
		ft_print(program, "has taken a fork");
		pthread_mutex_lock(program->next->fork);
		ft_print(program, "has taken a fork");
		pthread_mutex_lock(program->death);
		program->last_meal = timeinmilliseconds();
		program->number_of_meal--;
		pthread_mutex_unlock(program->death);
		ft_print(program, "is eating");
		action(program->time_to_eat, program);
		pthread_mutex_unlock(program->fork);
		pthread_mutex_unlock(program->next->fork);
		ft_print(program, "is sleeping");
		action(program->time_to_sleep, program);
		ft_print(program, "is thinking");
    }
    return(NULL);
}