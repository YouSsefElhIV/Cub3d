/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:08:49 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:39:33 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

size_t	ft_strlen(const char *st)
{
	size_t	i;

	if (st == NULL)
		return (0);
	i = 0;
	while (st[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char		*new_copy;
	size_t		i;
	size_t		len;

	len = ft_strlen(s1);
	i = 0;
	new_copy = malloc(len + 1);
	if (new_copy == NULL)
		return (NULL);
	while (i < len)
	{
		new_copy[i] = s1[i];
		i++;
	}
	new_copy[i] = '\0';
	return (new_copy);
}

static void	the_joining(char const *s1, char const *s2, size_t *i, char *f)
{
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	while (*i < s1_len)
	{
		f[*i] = s1[*i];
		(*i)++;
	}
	j = 0;
	while (j < s2_len)
	{
		f[*i] = s2[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*f;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	f = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (f == NULL)
		return (NULL);
	the_joining(s1, s2, &i, f);
	f[i] = '\0';
	return (f);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
