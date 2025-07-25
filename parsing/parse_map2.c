/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:45:04 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 09:27:00 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	is_map_line(char *line)
{
	return (ft_strrchr(line, '.') == NULL && ft_strrchr(line, ',') == NULL
		&& (line[0] == '1' || line[0] == 32 || line[0] == '0' || \
		line[0] == 'N' || line[0] == 'W' || line[0] == 'E' || \
		line[0] == 'S'));
}

static int	has_non_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

static void	handle_map_bounds(t_player *p, int i)
{
	if (p->map_start == -1)
	{
		if (has_non_space(p->tmp_map[i]))
			p->map_start = i;
	}
	else
		p->map_end = i + 1;
}

void	init_map_limits(t_player *p)
{
	int	i;

	p->map_start = -1;
	p->map_end = -1;
	i = 0;
	while (p->tmp_map[i])
	{
		if (is_map_line(p->tmp_map[i]))
			handle_map_bounds(p, i);
		i++;
	}
	if (p->tmp_map[p->map_end] != NULL)
	{
		write(2, "Map Error\n", 11);
		map_free(p->tmp_map);
		exit(1);
	}
}

void	count_content(t_player *p)
{
	if ((p->ply_e > 1 || p->ply_n > 1 || p->ply_s > 1 || p->ply_w > 1)
		|| (p->ply_e == 0 && p->ply_n == 0 && p->ply_s == 0 && p->ply_w == 0)
		|| p->wall == 0 || p->empty_space == 0 || p->door == 0)
	{
		write(2, "Map Error\n", 11);
		free_map(p);
		exit (1);
	}
	if ((p->ply_e == 1 && (p->ply_n == 1 || p->ply_s == 1 || p->ply_w == 1))
		|| (p->ply_s == 1 && (p->ply_n == 1 || p->ply_e == 1 || p->ply_w == 1))
		|| (p->ply_n == 1 && (p->ply_s == 1 || p->ply_s == 1 || p->ply_w == 1))
		|| (p->ply_w == 1 && (p->ply_n == 1 || p->ply_s == 1 || p->ply_e == 1)))
	{
		write(2, "Map Error\n", 11);
		free_map(p);
		exit (1);
	}
}
