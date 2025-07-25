/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:57:42 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:25:46 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	fix_angles(t_player *player)
{
	if (player->see_right)
		player->angle += ANGLE;
	if (player->see_left)
		player->angle -= ANGLE;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	sliding(t_player *p, int type)
{
	if (((type == 2 || type == 3) && p->move_up)
		|| ((type == 2 || type == 3) && p->move_down))
		return ;
	if (type == 0 && valid_move(p, p->x + SPEED * sin(p->angle), p->y))
		p->x += SPEED * sin(p->angle);
	else if (type == 0 && valid_move(p, p->x, \
		p->y + SPEED * cos(p->angle)))
		p->y += SPEED * cos(p->angle);
	if (type == 1 && valid_move(p, p->x - SPEED * sin(p->angle), p->y))
		p->x -= SPEED * sin(p->angle);
	else if (type == 1 && valid_move(p, p->x, \
	p->y - SPEED * cos(p->angle)))
		p->y -= SPEED * cos(p->angle);
	if (type == 2 && valid_move(p, p->x + SPEED * \
		sin(p->angle + (PI / 2)), p->y))
		p->x += SPEED * sin(p->angle + (PI / 2));
	else if (type == 2 && valid_move(p, p->x, p->y + SPEED * \
		cos(p->angle + (PI / 2))))
		p->y += SPEED * cos(p->angle + (PI / 2));
	if (type == 3 && valid_move(p, p->x - SPEED * \
		sin(p->angle + (PI / 2)), p->y))
		p->x -= SPEED * sin(p->angle + (PI / 2));
	else if (type == 3 && valid_move(p, p->x, p->y - SPEED * \
		cos(p->angle + (PI / 2))))
		p->y -= SPEED * cos(p->angle + (PI / 2));
}

void	vertical_moves(t_player *player)
{
	fix_angles(player);
	if (player->move_up)
	{
		if (valid_move(player, player->x + SPEED * sin(player->angle), \
			player->y + SPEED * cos(player->angle)))
		{
			player->x += SPEED * sin(player->angle);
			player->y += SPEED * cos(player->angle);
		}
		sliding(player, 0);
	}
	if (player->move_down)
	{
		if (valid_move(player, player->x - SPEED * sin(player->angle), \
			player->y - SPEED * cos(player->angle)))
		{
			player->x -= SPEED * sin(player->angle);
			player->y -= SPEED * cos(player->angle);
		}
		sliding(player, 1);
	}
}

void	side_moves(t_player *player)
{
	if (player->move_right)
	{
		if (valid_move(player, player->x + SPEED * \
			sin(player->angle + (PI / 2)), player->y + SPEED * \
			cos(player->angle + (PI / 2))))
		{
			player->x += SPEED * sin(player->angle + (PI / 2));
			player->y += SPEED * cos(player->angle + (PI / 2));
		}
		sliding(player, 2);
	}
	if (player->move_left)
	{
		if (valid_move(player, player->x - SPEED * \
			sin(player->angle + (PI / 2)), player->y - SPEED * \
			cos(player->angle + (PI / 2))))
		{
			player->x -= SPEED * sin(player->angle + (PI / 2));
			player->y -= SPEED * cos(player->angle + (PI / 2));
		}
		sliding(player, 3);
	}
}

void	moving(t_player *player)
{
	int	old_x;
	int	old_y;

	old_x = (int)(player->x / 64);
	old_y = (int)(player->y / 64);
	vertical_moves(player);
	side_moves(player);
	if (player->old_move == 'D')
		player->map[old_x][old_y] = 'D';
	else
		player->map[old_x][old_y] = '0';
	player->old_move = \
	player->map[(int)(player->x / 64)][(int)(player->y / 64)];
	player->map[(int)(player->x / 64)][(int)(player->y / 64)] = 'N';
}
