/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:08:51 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:39:18 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

char	*create_next_line(char **first_line, size_t next_line_len)
{
	size_t	i;
	char	*next_line;
	int		ln;

	ln = ((*first_line)[next_line_len] == '\n');
	i = 0;
	next_line = malloc(next_line_len + 1 + (ln));
	if (!next_line)
		return (NULL);
	while (i < next_line_len + (ln))
	{
		next_line[i] = (*first_line)[i];
		i++;
	}
	next_line[i] = '\0';
	return (next_line);
}

char	*create_new_buffer(char **first_line, size_t next_line_len)
{
	size_t	i;
	size_t	all_len;
	size_t	new_buffer_len;
	char	*tmp;
	int		len;

	len = ((*first_line)[next_line_len] == '\n');
	i = 0;
	all_len = ft_strlen(*first_line);
	new_buffer_len = all_len - (next_line_len + (len));
	tmp = malloc(new_buffer_len + 1);
	if (!tmp)
		return (NULL);
	while (i < new_buffer_len)
	{
		tmp[i] = (*first_line)[next_line_len + i + 1];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*get_other_line(char **first_line)
{
	size_t	next_line_len;
	char	*next_line;
	char	*tmp;

	next_line_len = 0;
	while ((*first_line)[next_line_len] && (*first_line)[next_line_len] != '\n')
		next_line_len++;
	next_line = create_next_line(first_line, next_line_len);
	if (!next_line)
		return (NULL);
	tmp = create_new_buffer(first_line, next_line_len);
	if (!tmp)
		return (free(next_line), NULL);
	free(*first_line);
	*first_line = tmp;
	return (next_line);
}

char	*get_first_line(int fd, char *first_line)
{
	char	*buf;
	int		n_bytes;
	char	*new_first_line;

	n_bytes = 1;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(first_line), first_line = NULL, NULL);
	while (ft_strchr(first_line, '\n') == 0 && n_bytes > 0)
	{
		n_bytes = read(fd, buf, BUFFER_SIZE);
		if (n_bytes < 0)
			return (free(buf), NULL);
		buf[n_bytes] = '\0';
		new_first_line = ft_strjoin(first_line, buf);
		if (first_line != NULL)
			free(first_line);
		first_line = new_first_line;
	}
	return (free(buf), first_line);
}

char	*get_next_line(int fd)
{
	static char	*first_line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(first_line);
		first_line = NULL;
		return (NULL);
	}
	if (BUFFER_SIZE >= 2147483647)
		return (NULL);
	first_line = get_first_line(fd, first_line);
	if (!first_line)
		return (NULL);
	next_line = get_other_line(&first_line);
	if (!next_line)
		return (free(first_line), first_line = NULL, NULL);
	if (ft_strlen(next_line) == 0)
		return (free(first_line), free(next_line), first_line = NULL, NULL);
	return (next_line);
}
