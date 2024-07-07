/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 05:04:41 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/07 02:04:57 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if ((unsigned char)c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == ((unsigned char)c))
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

static size_t	ft_countword(char *s, char c)
{
	size_t	count;

	if (!s || !*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static	int	ft_split_norm(char **lst, char *s, char c, int word_len)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			if (!lst)
				return (0);
			s += word_len;
		}
	}
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**lst;
	size_t	word_len;
	size_t	i;

	word_len = 0;
	if (!s)
		return (NULL);
	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	i = 0;
	if (!ft_split_norm(lst, s, c, word_len))
	{
		while (lst + i)
		{
			free(lst + i);
			i++;
		}
		free(lst);
	}
	lst[ft_countword((char *)s, c)] = NULL;
	return (lst);
}
