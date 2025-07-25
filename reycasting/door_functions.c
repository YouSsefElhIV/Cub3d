/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:17:05 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:26:08 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	open_door(t_player *player, int x, int y)
{
	t_doors	*courant;
	t_doors	*new;

	courant = player->doors;
	new = malloc(sizeof(t_doors));
	if (!new)
	{
		cleanup_project(player);
		exit (0);
	}
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (player->doors == NULL)
		player->doors = new;
	else
	{
		while (courant->next)
			courant = courant->next;
		courant->next = new;
	}
}

void	handle_doors2(t_player *player, int i, int x, int y)
{
	int	p[4][2];

	init_p(p);
	if (player->map[(int)((x + p[i][0]) / 64)] \
	[(int)((y + p[i][1]) / 64)] == 'D')
	{
		if (coor_in(player, (int)((x + p[i][0]) / 64), \
		(int)((y + p[i][1]) / 64)) == 1)
			close_door(player, (int)((x + p[i][0]) / 64), \
			(int)((y + p[i][1]) / 64));
		else
			open_door(player, (int)((x + p[i][0]) / 64), \
			(int)((y + p[i][1]) / 64));
	}
}

void	check_other_poss(t_player *player, int x, int y)
{
	if (player->angle >= 0.78 && player->angle < 2.35)
		handle_doors2(player, 0, x, y);
	else if (player->angle >= 2.35 && player->angle < 3.92)
		handle_doors2(player, 1, x, y);
	else if (player->angle >= 3.92 && player->angle < 5.49)
		handle_doors2(player, 3, x, y);
	else
		handle_doors2(player, 2, x, y);
}

void	handle_doors(t_player *player)
{
	int	x;
	int	y;

	y = player->y + SPEED * cos(player->angle);
	x = player->x + SPEED * sin(player->angle);
	if (player->map[(int)(x / 64)][(int)(y / 64)] == 'D')
	{
		if (coor_in(player, (int)(x / 64), (int)(y / 64)) == 1)
			close_door(player, (int)(x / 64), (int)(y / 64));
		else
			open_door(player, (int)(x / 64), (int)(y / 64));
	}
	else
		check_other_poss(player, x, y);
}
