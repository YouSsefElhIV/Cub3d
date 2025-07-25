/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:36:57 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 09:25:50 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	mouse_move(int x, int y, void *param)
{
	t_player	*player;
	static int	last_x = -1;
	int			delta_x;
	double		sensitivity;

	(void) y;
	player = (t_player *)param;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	last_x = x;
	sensitivity = 0.005;
	player->angle += delta_x * sensitivity;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	else if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	return (0);
}

void	angle(t_player *player, int x0, int y0)
{
	float	step;
	float	x;
	float	y;
	float	i;

	step = 2;
	x = (float)x0;
	y = (float)y0;
	i = 0;
	while (i < 7)
	{
		put_pixel(player, (int)y, (int)x, 0xFF0000);
		x += step * sin(player->angle);
		y += step * cos(player->angle);
		i += step;
	}
}

void	put_angle_helper(t_player *player, int a, int i, int j)
{
	int		b;
	float	size;

	size = (WIDTH + HEIGHT) / 300.0f;
	if (size <= 0)
		size = 1;
	b = 0;
	while (b < 20)
	{
		if ((j + b) >= 0 && (j + b) < player->longest_row)
		{
			if (player->map[i + a][j + b] == 'E' || \
				player->map[i + a][j + b] == 'W' || \
				player->map[i + a][j + b] == 'N' || \
				player->map[i + a][j + b] == 'S')
				angle(player, ((a + 20) * size + 1), ((b + 20) * size + 1));
		}
		b++;
	}
}

void	put_angle(t_player *player)
{
	int	i;
	int	j;
	int	a;

	i = (int)(player->x / 64);
	a = 0;
	while (a < 20)
	{
		if ((i + a) >= player->map_start && (i + a) < player->map_end)
		{
			j = (int)(player->y / 64);
			put_angle_helper(player, a, i, j);
		}
		a++;
	}
}

void	init_p(int p[4][2])
{
	p[0][0] = 60;
	p[0][1] = 0;
	p[1][0] = 0;
	p[1][1] = -60;
	p[2][0] = 0;
	p[2][1] = 60;
	p[3][0] = -60;
	p[3][1] = 0;
}
