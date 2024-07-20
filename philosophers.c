/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:19 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/20 17:07:02 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine()
{
    printf("%s", "test");
    return(0);
}

void creat_thread(t_philosophers *philo)
{
    int i;
    
    i = 1;
    while(i <= philo->number_of_philosophers)
    {
        pthread_create(&philo->threads, NULL, &routine, philo);
        philo = philo->next;
        pthread_detach(philo->threads);
    }
}

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
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
	return (sign * nb);
}

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	if (ft_atoi(av[1]) > MAX_PHILOSOPHERS || ft_atoi(av[1]) <= 0
		|| check_arg_content(av[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(av[2]) <= 0 || check_arg_content(av[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(av[3]) <= 0 || check_arg_content(av[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(av[4]) <= 0 || check_arg_content(av[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || check_arg_content(av[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int main(int ac, char **av)
{
    t_philosophers  *philo;
    int dead;
    
    philo = malloc(sizeof(t_philosophers *));
    dead = 0;
    if (ac != 5 && ac != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_args(av) == 1)
		return (1);
    creat_thread(philo);
    
}