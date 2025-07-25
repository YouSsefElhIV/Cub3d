/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:28:32 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:26:48 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	longest(t_player *p)
{
	int		i;
	size_t	max;

	i = p->map_start;
	max = ft_strlen(p->tmp_map[i]);
	while (i < p->map_end)
	{
		if (max < ft_strlen(p->tmp_map[i]))
			max = ft_strlen(p->tmp_map[i]);
		i++;
	}
	return ((int)(max));
}

void	set_player_angle(t_player *player)
{
	if (player->ply_e == 1)
		player->angle = 0;
	else if (player->ply_w == 1)
		player->angle = PI;
	else if (player->ply_n == 1)
		player->angle = (3 * PI) / 2;
	else if (player->ply_s == 1)
		player->angle = PI / 2;
}

void	check_empty_space(t_player *player)
{
	int	i;
	int	j;

	i = player->map_start;
	while (i < player->map_end)
	{
		j = 0;
		while (j < player->longest_row)
		{
			if (player->map[i][j] == 32)
			{
				if (((i + 1 < player->map_end && (player->map[i + 1][j] == '0' || player->map[i + 1][j] == 'D')))
				|| ((i - 1 > player->map_start && (player->map[i - 1][j] == '0' || player->map[i - 1][j] == 'D')))
				|| ((j + 1 < player->longest_row && (player->map[i][j + 1] == '0' || player->map[i][j + 1] == 'D')))
				|| ((j - 1 > 0 && (player->map[i][j - 1] == '0' || player->map[i][j - 1] == 'D'))))
				{
					write(2, "Map Error\n", 11);
					free_map(player);
					exit (1);
				}
			}
			j++;
		}
		i++;
	}
}

void	check_player_pos(t_player *player)
{
	int	x;
	int	y;

	x = player->x / 64;
	y = player->y / 64;
	if (x == player->map_start || x == player->map_end - 1 || \
	y == player->longest_row || y == 0)
	{
		write(2, "Map Error\n", 10);
		free_map(player);
		exit(1);
	}
	if (player->map[x + 1][y] == 32 || player->map[x - 1][y] == 32 || \
	player->map[x][y + 1] == 32 || player->map[x][y - 1] == 32)
	{
		write(2, "Map Error\n", 10);
		free_map(player);
		exit(1);
	}
}

void	parse_map(t_player *player)
{
	if (player->map_end >= 500 || player->longest_row >= 500)
	{
		write(2, "Please use a smaller map since 1337 \
resources are limited\n", 59);
		free_map(player);
		exit (1);
	}
	check_map_content(player);
	count_content(player);
	check_bounderies(player);
	set_player_angle(player);
	check_empty_space(player);
	check_player_pos(player);
}
