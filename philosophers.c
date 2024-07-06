/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:19 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/06 05:02:17 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int isspace(int c)
{
    return (c == ' ' || c == '\t');
}

int isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

void arg_check(char **av)
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
                exit(1);
            }
            j++;
        }
        tmp = ft_strdup("");
        tmp = ft_join(tmp, av[i]);
		tmp = ft_join(tmp, " ");
        
        i++;
    }
}

int main(int ac, char **av)
{
    
    if (ac ==  5 || ac == 6)
    {
        arg_check(av);
    }
    else
    {
        write(1, "Invalid number of arguments\n", 24);
        exit(1);
    }
    return 0;
}