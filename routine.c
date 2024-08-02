/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:44:38 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/08/02 18:47:03 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_print(t_philosophers *philo, char *str)
{
    int time;

    pthread_mutex_lock(philo->print);
    time = timeinmilliseconds();
    printf("%d philo %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(philo->print);
}

int check(t_philosophers *philo)
{
    pthread_mutex_lock(philo->death);
    if (timeinmilliseconds() - philo->last_meal > philo->time_to_die)
    {
        pthread_mutex_unlock(philo->death);
        return 1;
    }
    pthread_mutex_unlock(philo->death);
    return 0;
}


void action(int action, t_philosophers *philo)
{
    long begin;

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

int check_death(void *d)
{
    int how_many;
    t_philosophers *philosophers = (t_philosophers *)d;

    how_many = philosophers->number_of_philosophers;
    while (1)
    {
        if (check(philosophers) == 1)
            return (philosophers->id);
        pthread_mutex_lock(philosophers->death);
        while (philosophers->number_of_meal != -1 && philosophers->number_of_meal == 0)
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
