/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:19 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/15 01:39:28 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    creation(t_philosophers *program)
{
    int i;
    
    i = 1; 
    while (i <= program->number_of_philosophers)
    {
        pthread_create(&program->threads, NULL, &routine, program);
        program = program->next;
		pthread_detach(program->threads);
		i++;
    }
}

int main(int ac, char **av)
{
    t_philosophers *program;
    int dead;
    
    program = malloc(sizeof(t_philosophers *));
    dead = 0;
    if(ac == 5 || ac == 6)
    {
        if(parc(av))
        {
            write(1, "Bad arg\n", 9);
            return(1);
        }
        fill_strct(av, &program);
        creation(program);
        dead = check_death(program);
        if (dead != 0)
            printf("%lld philo %d is died\n", timeinmilliseconds(), dead);
    }
    else
    {   
        write(1, "Error\n", 1);
        return(1);
    }
}