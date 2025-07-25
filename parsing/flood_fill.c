/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:10:38 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:26:21 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	fill_for_connection(t_player *player, char target, int row, int col)
{
	int	end;

	end = player->map_end - player->map_start;
	if (row < 0 || col < 0 || row >= end || col >= player->longest_row)
	{
		return ;
	}
	if (player->map3[row][col] == 32 || player->map3[row][col] == 0 \
		|| player->map3[row][col] == 'F')
		return ;
	player->map3[row][col] = 'F';
	fill_for_connection(player, target, row -1, col);
	fill_for_connection(player, target, row +1, col);
	fill_for_connection(player, target, row, col - 1);
	fill_for_connection(player, target, row, col + 1);
}

void	flood_fill_for_connection(t_player *player)
{
	char	target;
	int		j;
	int		i;

	i = 0;
	j = 0;
	target = '\0';
	while (player->map3[i])
	{
		j = 0;
		while (player->map3[i][j])
		{
			if (player->map3[i][j] == '1')
			{
				target = player->map3[i][j];
				break ;
			}
			j++;
		}
		if (target)
			break ;
		i++;
	}
	fill_for_connection(player, target, i, j);
}
