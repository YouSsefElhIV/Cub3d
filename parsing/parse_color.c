/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:20:15 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/24 15:01:00 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	count_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

int	check_nbr(char **nbr)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (nbr[i])
	{
		j = 0;
		new = ft_strtrim(nbr[i], " ");
		while (new[j])
		{
			if (!ft_isdigit(new[j]))
				return (free(new), 0);
			if (j >= 3)
				return (free(new), 0);
			j++;
		}
		free(new);
		i++;
	}
	return (1);
}

int	parse_color_value(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**parts;

	if (count_ver(str) > 2)
		return (-1);
	parts = ft_split(str, ',');
	if (!parts || count_split(parts) != 3)
		return (map_free(parts), -1);
	if (check_nbr(parts) == 0)
		return (map_free(parts), -1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	map_free(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r * 65536 + g * 256 + b);
}

void	process_color_line(t_player *player, char *line)
{
	t_config	*cfg;

	cfg = player->config;
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (player->f_count > 0)
			return (cleanup(player),
				write(2, "Error: Duplicate floor color\n", 29), exit(1));
		cfg->floor_color = parse_color_value(line + 2);
		player->f_count++;
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (player->c_count > 0)
			return (cleanup(player),
				write(2, "Error: Duplicate ceiling color\n", 32), exit(1));
		cfg->ceiling_color = parse_color_value(line + 2);
		player->c_count++;
	}
}

void	parse_colors(t_player *player)
{
	int			i;
	char		*line;
	t_config	*cfg;

	player->f_count = 0;
	player->c_count = 0;
	cfg = player->config;
	i = 0;
	while (player->map[i])
	{
		line = player->map[i];
		process_color_line(player, line);
		i++;
	}
	if (cfg->floor_color == -1 || cfg->ceiling_color == -1)
	{
		cleanup(player);
		write(2, "Error: Invalid colors\n", 22);
		exit(1);
	}
}
