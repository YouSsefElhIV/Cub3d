/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:16:34 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:25:29 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	touch(t_player *player, float fx, float fy)
{
	int	x;
	int	y;

	x = (int)fx;
	y = (int)fy;
	if (x < 0 || x >= player->map_end || y < 0 || y >= player->longest_row)
		return (0);
	if (player->map[x][y] == '1')
	{
		player->dda.hit_door = 0;
		return (1);
	}
	if (player->map[x][y] == 'D')
	{
		if (coor_in(player, x, y) == 1)
			return (0);
		else
		{
			player->dda.hit_door = 1;
			return (1);
		}
	}
	return (0);
}

void	dda(t_player *player, float ray_angle)
{
	int	reached_wall;

	reached_wall = 0;
	while (!reached_wall)
	{
		if (player->dda.x_dist < player->dda.y_dist)
		{
			player->dda.x_dist += player->dda.x_line_length;
			player->dda.x += player->dda.x_step;
			player->dda.wall_face = 0;
		}
		else
		{
			player->dda.y_dist += player->dda.y_line_length;
			player->dda.y += player->dda.y_step;
			player->dda.wall_face = 1;
		}
		reached_wall = touch(player, player->dda.y, player->dda.x);
	}
	if (!player->dda.wall_face)
		player->dda.distence = player->dda.x_dist - player->dda.x_line_length;
	else
		player->dda.distence = player->dda.y_dist - player->dda.y_line_length;
	player->dda.distence *= cos(player->angle - ray_angle);
}

void	put_ray_line(t_player *player, float ray_angle, int i)
{
	player->dda.x = (int)(player->y / 64);
	player->dda.y = (int)(player->x / 64);
	player->dda.x_line_length = fabs(1 / cos(ray_angle));
	player->dda.y_line_length = fabs(1 / sin(ray_angle));
	player->dda.x_step = 1;
	player->dda.y_step = 1;
	if (cos(ray_angle) < 0)
	{
		player->dda.x_step = -1;
		player->dda.x_dist = ((player->y / 64) - \
		player->dda.x) * player->dda.x_line_length;
	}
	else
		player->dda.x_dist = (player->dda.x + 1.0 - \
		(player->y / 64)) * player->dda.x_line_length;
	if (sin(ray_angle) < 0)
	{
		player->dda.y_step = -1;
		player->dda.y_dist = ((player->x / 64) - \
		player->dda.y) * player->dda.y_line_length;
	}
	else
		player->dda.y_dist = (player->dda.y + 1.0 - \
		(player->x / 64)) * player->dda.y_line_length;
	return (dda(player, ray_angle), transform_to_3d(player, i, ray_angle));
}

void	reycasting(t_player *player)
{
	float	pov;
	int		i;
	float	starting_x;

	player->dda.hit_door = 0;
	pov = PI / 3 / WIDTH;
	starting_x = player->angle - (PI / 6);
	i = 0;
	while (i < WIDTH)
	{
		put_ray_line(player, starting_x, i);
		starting_x += pov;
		i++;
	}
}
