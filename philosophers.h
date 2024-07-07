/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:35 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/07 03:11:24 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

typedef struct s_philosophers
{
	pthread_t	threads;
	int			les_philosophers;

}	t_philosophers;

char	*ft_strdup(char *s);
char	*ft_join(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char *s, char c);
int		ft_strlen(char *str);
int		arg_check(char **av);
int		isdigit(int c);
int		isspace(int c);
char	*ft_strchr(char *s, int c);

#endif