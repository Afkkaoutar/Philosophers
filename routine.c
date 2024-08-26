/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:44:38 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/08/26 22:24:51 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philosophers *philo, char *str)
{
	int	time;

	pthread_mutex_lock(philo->print);
	time = timeinmilliseconds();
	printf("%d philo %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->print);
}

int	check(t_philosophers *philo)
{
	pthread_mutex_lock(philo->death);
	if (timeinmilliseconds() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}

void	action(int action, t_philosophers *philo)
{
	long	begin;

	begin = timeinmilliseconds();
	pthread_mutex_lock(philo->death);
	while (timeinmilliseconds() - begin < action)
	{
		pthread_mutex_unlock(philo->death);
		usleep(100);
		pthread_mutex_lock(philo->death);
	}
	pthread_mutex_unlock(philo->death);
}

void	*routine(void *rou)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)rou;
	if (philo->id % 2 == 1)
		usleep(philo->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(philo->fork);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->next->fork);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->death);
		philo->last_meal = timeinmilliseconds();
		if (philo->number_of_meal != -1)
			philo->number_of_meal--;
		pthread_mutex_unlock(philo->death);
		ft_print(philo, "is eating");
		action(philo->time_to_eat, philo);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		ft_print(philo, "is sleeping");
		action(philo->time_to_sleep, philo);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}
