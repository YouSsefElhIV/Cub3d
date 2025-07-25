/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:43:18 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/24 15:01:29 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	set_player_pos(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'N' || map[i][j] == 'S')
			{
				player->x = (i + player->map_start) * 64 + 32;
				player->y = j * 64 + 32;
			}
			j++;
		}
		i++;
	}
}

void	check_map_connection(t_player *player, char **copy)
{
	int	i;
	int	j;

	player->map3 = copy_of_the_map(player);
	i = 0;
	flood_fill_for_connection(player);
	while (player->map3[i])
	{
		j = 0;
		while (player->map3[i][j])
		{
			if (player->map3[i][j] == '1')
			{
				write(2, "Map0Error\n", 11);
				map_free(player->map3);
				map_free(copy);
				free_map(player);
				exit (1);
			}
			j++;
		}
		i++;
	}
	map_free(player->map3);
}

void	fill(t_player *player, char target, int row, int col)
{
	int	end;

	end = player->map_end - player->map_start;
	if (row < 0 || col < 0 || row >= end || col >= player->longest_row)
	{
		write(2, "Map1Error\n", 11);
		map_free(player->map2);
		free_map(player);
		exit (1);
	}
	if (player->map2[row][col] == '1' || player->map2[row][col] == 'F')
		return ;
	player->map2[row][col] = 'F';
	fill(player, target, row -1, col);
	fill(player, target, row +1, col);
	fill(player, target, row, col - 1);
	fill(player, target, row, col + 1);
}

void	flood_fill(t_player *player)
{
	char	target;
	int		j;
	int		i;

	i = 0;
	while (player->map2[i])
	{
		j = 0;
		while (player->map2[i][j])
		{
			if (player->map2[i][j] == '0')
			{
				target = player->map2[i][j];
				fill(player, target, i, j);
			}
			j++;
		}
		i++;
	}
}

void	check_bounderies(t_player *player)
{
	player->map2 = copy_of_the_map(player);
	check_map_connection(player, player->map2);
	set_player_pos(player, player->map2);
	flood_fill(player);
	map_free(player->map2);
}
