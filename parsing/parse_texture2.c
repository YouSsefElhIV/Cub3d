/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:13:27 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 09:27:09 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	check_new_line(char *map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (map[i - 1] == '\n')
		return (1);
	return (0);
}

static int	check_char(char c1, char c2)
{
	if ((c1 != 'N' ) && (c1 != 'S') && (c1 != 'W')
		&& (c1 != 'E') && (c1 != 'F') && (c1 != 'C'))
		return (0);
	if ((c2 != 'O') && (c2 != 'A') && (c2 != 'W')
		&& (c2 != 'E') && (c2 != ' '))
		return (0);
	return (1);
}

int	is_valid_prefix(t_player *p)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = NULL;
	while (p->map[i])
	{
		line = p->map[i];
		j = 0;
		while (line[j] == ' ' || (line[j] >= 9 && line[j] <= 13))
			j++;
		if (line[j] == '1' || line [j] == '0')
			return (1);
		if (line[j] == '\0')
		{
			i++;
			continue ;
		}
		if (!check_char(line[j], line[j + 1]))
			return (0);
		i++;
	}
	return (1);
}
