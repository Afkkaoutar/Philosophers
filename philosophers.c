/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:19 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/08/02 18:43:44 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *rou)
{
    t_philosophers *philo = (t_philosophers *)rou;

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

    return NULL;
}

void creat_thread(t_philosophers *philo)
{
    int i = 0;

    while (i < philo->number_of_philosophers)
    {
        pthread_create(&philo[i].threads, NULL, &routine, &philo[i]);
        pthread_detach(philo[i].threads);
        i++;
    }
}

int ft_atoi(char *str)
{
    unsigned long long nb = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        nb = nb * 10 + (str[i] - '0');
        i++;
    }
    return sign * nb;
}

int check_arg_content(char *arg)
{
    int i = 0;

    while (arg[i] != '\0')
    {
        if (arg[i] < '0' || arg[i] > '9')
            return 1;
        i++;
    }
    return 0;
}

int check_args(char **av)
{
    if (ft_atoi(av[1]) > MAX_PHILOSOPHERS || ft_atoi(av[1]) <= 0 || check_arg_content(av[1]) == 1)
        return write(2, "Invalid philosophers number\n", 29), 1;
    if (ft_atoi(av[2]) <= 0 || check_arg_content(av[2]) == 1)
        return write(2, "Invalid time to die\n", 21), 1;
    if (ft_atoi(av[3]) <= 0 || check_arg_content(av[3]) == 1)
        return write(2, "Invalid time to eat\n", 21), 1;
    if (ft_atoi(av[4]) <= 0 || check_arg_content(av[4]) == 1)
        return write(2, "Invalid time to sleep\n", 23), 1;
    if (av[5] && (ft_atoi(av[5]) < 0 || check_arg_content(av[5]) == 1))
        return write(2, "Invalid number of times each philosopher must eat\n", 51), 1;
    return 0;
}

int main(int ac, char **av)
{
    t_philosophers *philo;
    int num_philosophers;

    if (ac != 5 && ac != 6)
        return write(2, "Wrong argument count\n", 22), 1;
    if (check_args(av) == 1)
        return 1;

    num_philosophers = ft_atoi(av[1]);
    philo = malloc(sizeof(t_philosophers) * num_philosophers);
    if (!philo)
    {
        perror("Failed to allocate memory");
        return 1;
    }

    init_philosophers(philo, num_philosophers, av);
    creat_thread(philo);

    int dead = check_death(philo);
    if (dead != 0)
        printf("%lld philo %d is died\n", timeinmilliseconds(), dead);

    free_resources(philo, num_philosophers);

    return 0;
}