/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:39:32 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/08/31 13:21:33 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(void *d)
{
	int				how_many;
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)d;
	how_many = philosophers->number_of_philosophers;
	while (1)
	{
		if (check(philosophers) == 1)
			return (philosophers->id);
		pthread_mutex_lock(philosophers->death);
		while (philosophers->number_of_times_each_philosopher_must_eat != -1
			&& philosophers->number_of_times_each_philosopher_must_eat == 0)
		{
			how_many--;
			if (how_many == 0)
				return (0);
			philosophers = philosophers->next;
		}
		pthread_mutex_unlock(philosophers->death);
		how_many = philosophers->number_of_philosophers;
		philosophers = philosophers->next;
	}
	usleep(100);
	return (-1);
}

void	init_individual(t_philosophers *philo, int i, int num, char **av)
{
	philo[i].id = i + 1;
	philo[i].number_of_philosophers = num;
	philo[i].time_to_die = ft_atoi(av[2]);
	philo[i].time_to_eat = ft_atoi(av[3]);
	philo[i].time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		philo[i].number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		philo[i].number_of_times_each_philosopher_must_eat = -1;
	philo[i].last_meal = timeinmilliseconds();
	philo[i].fork = malloc(sizeof(pthread_mutex_t));
	if (!philo[i].fork)
	{
		perror("Failed to allocate memory for fork mutex");
		exit(1);
	}
	pthread_mutex_init(philo[i].fork, NULL);
}

void	init_global_mutexes(t_philosophers *philo, int i, int num)
{
	if (i == 0)
	{
		philo[i].print = malloc(sizeof(pthread_mutex_t));
		philo[i].death = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].print || !philo[i].death)
		{
			perror("Failed to allocate memory for mutexes");
			exit(1);
		}
		pthread_mutex_init(philo[i].print, NULL);
		pthread_mutex_init(philo[i].death, NULL);
	}
	else
	{
		philo[i].print = philo[0].print;
		philo[i].death = philo[0].death;
	}
	if (i == num - 1)
		philo[i].next = &philo[0];
	else
		philo[i].next = &philo[i + 1];
}

void	init_philosophers(t_philosophers *philo, int num, char **av)
{
	int	i;

	i = 0;
	while (i < num)
	{
		init_individual(philo, i, num, av);
		init_global_mutexes(philo, i, num);
		i++;
	}
}

void	free_resources(t_philosophers *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(philo[i].fork);
		free(philo[i].fork);
		i++;
	}
	pthread_mutex_destroy(philo[0].print);
	pthread_mutex_destroy(philo[0].death);
	free(philo[0].print);
	free(philo[0].death);
	free(philo);
}
