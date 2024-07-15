/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:35 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/15 01:41:52 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define MAX_PHILOSOPHERS 200

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philosophers {
    pthread_t threads;
    int id;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_meal;
    long long last_meal;
    pthread_mutex_t *fork;
    pthread_mutex_t *print;
    pthread_mutex_t *death;
    struct s_philosophers *next;
} t_philosophers;

void    *routine(void *routin);
int	check_death(void *d);
int	check(t_philosophers *program);
void	action(int action, t_philosophers *program);
void	ft_print(t_philosophers *program, char *str);

#endif