/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:19 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/07 03:17:44 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *routine()
{
    printf("test");
    return NULL;
}

void creation(t_philosophers *philo)
{
    int count = 0;
    
    while (count <= philo->les_philosophers)
    {
        pthread_create(&philo->threads, NULL, &routine, NULL);
        pthread_join(philo->threads, NULL);
        count++;
    }
  
}

int isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int arg_check(char **av)
{
    int i = 1;
    char *tmp;

    while (av[i])
    {
        int j = 0;
        while (av[i][j])
        {
            if (!isdigit(av[i][j]) || isspace(av[i][j]))
            {
                write(1, "Erreur\n", 8);
                return(1);
            }
            j++;
        }
        tmp = ft_strdup("");
        tmp = ft_join(tmp, av[i]);
		tmp = ft_join(tmp, " ");
        
        i++;
    }
    return(0);
    // av = ft_split(tmp, ' ');
    // free(tmp);
}


int main(int ac, char **av)
{
    t_philosophers *philo;
    

    philo = malloc(sizeof(t_philosophers *));
    if (ac ==  5 || ac == 6)
    {
        arg_check(av);
    }
    else
    {
        write(1, "Invalid number of arguments\n", 24);
        exit(1);
    }
    creation(philo);
    free (philo);
}
