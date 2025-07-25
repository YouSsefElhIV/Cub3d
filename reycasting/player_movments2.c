/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movments2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:44:55 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:47:18 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	key_pressed(int key, t_player *player)
{
	if (key == 3)
	{
		player->surprise.active = 1;
		player->surprise.curr_frames = 0;
	}
	else if (key == ESC)
	{
		free_map(player);
		exit (0);
	}
	else if (key == W)
		player->move_up = true;
	else if (key == S)
		player->move_down = true;
	else if (key == D)
		player->move_right = true;
	else if (key == A)
		player->move_left = true;
	else if (key == RIGHT)
		player->see_right = true;
	else if (key == LEFT)
		player->see_left = true;
	else if (key == SPACE)
		handle_doors(player);
	return (0);
}

int	key_released(int key, t_player *player)
{
	if (key == W)
		player->move_up = false;
	else if (key == S)
		player->move_down = false;
	else if (key == D)
		player->move_right = false;
	else if (key == A)
		player->move_left = false;
	else if (key == RIGHT)
		player->see_right = false;
	else if (key == LEFT)
		player->see_left = false;
	return (0);
}

bool	valid_move(t_player *player, float x, float y)
{
	if ((int)x >= 0 && (int)x < player->map_end * 64 \
	&& (int)y >= 0 && (int)y < player->longest_row * 64 && \
	(player->map[(int)(x / 64)][(int)(y / 64)] != '1') && \
	(player->map[(int)((x + 10) / 64)][(int)((y + 10) / 64)] != '1')
	&& (player->map[(int)((x + 10) / 64)][(int)((y - 10) / 64)] != '1')
	&& (player->map[(int)((x - 10) / 64)][(int)((y + 10) / 64)] != '1')
	&& (player->map[(int)((x - 10) / 64)][(int)((y - 10) / 64)] != '1'))
	{
		if (player->map[(int)(x / 64)][(int)(y / 64)] == 'D'\
		&& coor_in(player, (int)(x / 64), (int)(y / 64)) == 0)
			return (false);
		else
			return (true);
	}
	return (false);
}
