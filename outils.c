/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 04:56:08 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/07 02:05:12 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	ns;
	char	*p;	

	i = 0;
	if (!s)
		return (NULL);
	ns = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ns)
		return (ft_strdup(""));
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (*s && i < len)
	{
		p[i] = s[start];
		start++;
		i++;
	}
	return (p[i] = '\0', p);
}

char	*ft_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	return (p[i] = 0, p);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
