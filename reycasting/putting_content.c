/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putting_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:01:58 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:25:38 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	put_pixel(t_player *p, int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * p->lines + x * p->bits / 8;
	p->data[index] = (color >> 0) & 0xFF;
	p->data[index + 1] = (color >> 8) & 0xFF;
	p->data[index + 2] = (color >> 16) & 0xFF;
}

void	put_square(t_player *player, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	if (size <= 0)
		size = 1;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (player->which == 3)
				put_pixel(player, y + i, x + j, 0x222222);
			else if (player->which == 2)
				put_pixel(player, y + i, x + j, 0x00FF00);
			else if (player->which == 1)
				put_pixel(player, y + i, x + j, 0x333333);
			else
				put_pixel(player, y + i, x + j, 0xFFD700);
			j++;
		}
		i++;
	}
}

static void	put_map_helper_draw(t_player *player, int a, int b, float size)
{
	int	x;
	int	y;

	x = (player->mini_a + 20) * size;
	y = (player->mini_b + 20) * size;
	a += player->mini_a;
	b += player->mini_b;
	if (player->map[a][b] == '1' || player->map[a][b] == 'D')
	{
		player->which = 1;
		if (coor_in(player, a, b))
			player->which = 4;
		put_square(player, x, y, size - 1);
	}
	else if (player->map[a][b] == 'E' || player->map[a][b] == 'W' || \
		player->map[a][b] == 'N' || player->map[a][b] == 'S')
	{
		player->which = 2;
		put_square(player, x, y, size);
	}
	else if (player->map[a][b] == '0')
	{
		player->which = 3;
		put_square(player, x, y, size + 1);
	}
}

void	put_map_helper(t_player *player, int a, int i, int j)
{
	int		b;
	float	size;

	size = (WIDTH + HEIGHT) / 300.0f;
	if (size <= 0)
		size = 1;
	b = -20;
	while (b < 20)
	{
		if ((j + b) >= 0 && (j + b) < player->longest_row)
		{
			player->mini_a = a;
			player->mini_b = b;
			put_map_helper_draw(player, i, j, size);
		}
		b++;
	}
}

void	put_map(t_player *player)
{
	int	i;
	int	j;
	int	a;

	i = (int)(player->x / 64);
	a = -20;
	while (a < 20)
	{
		if ((i + a) >= player->map_start && (i + a) < player->map_end)
		{
			j = (int)(player->y / 64);
			put_map_helper(player, a, i, j);
		}
		a++;
	}
	put_angle(player);
}
