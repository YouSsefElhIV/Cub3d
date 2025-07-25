/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:39:13 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/24 15:03:33 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static t_texture	*get_texture(t_player *player)
{
	if (player->dda.hit_door == 1)
		return (&player->door_img);
	if (player->dda.wall_face == 1)
	{
		if (player->dda.y_step > 0)
			return (&player->south);
		else
			return (&player->north);
	}
	else
	{
		if (player->dda.x_step > 0)
			return (&player->east);
		else
			return (&player->west);
	}
}

static int	get_tex_x(t_player *player, t_texture *tex, float ray_angle)
{
	double	wallx;
	int		texx;
	float	dis;

	dis = player->dda.distence;
	dis /= cos(player->angle - ray_angle);
	if (player->dda.wall_face == 0)
		wallx = (player->x / 64.0) + dis * sin(ray_angle);
	else
		wallx = (player->y / 64.0) + dis * cos(ray_angle);
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)tex->width);
	if (player->dda.hit_door == 0)
	{
		if (player->dda.wall_face == 0 && cos(ray_angle) > 0)
			texx = tex->width - texx - 1;
		if (player->dda.wall_face == 1 && sin(ray_angle) < 0)
			texx = tex->width - texx - 1;
	}
	return (texx);
}

static void	draw_wall_slice(t_player *p, int i, t_texture *tex, int texX)
{
	float	wall_height;
	int		start_y;
	int		end_y;
	int		j;
	int		texy;

	wall_height = (1.0f / p->dda.distence) * WIDTH;
	start_y = (HEIGHT / 2) - (wall_height / 2);
	end_y = start_y + wall_height;
	j = 0;
	while (j < start_y)
		put_pixel(p, i, j++, p->config->ceiling_color);
	while (j < end_y)
	{
		if (j >= 0 && j < HEIGHT)
		{
			texy = (int)((j - start_y) * ((double)tex->height / wall_height));
			p->color = tex->data[texy * tex->width + texX];
			put_pixel(p, i, j, p->color);
		}
		j++;
	}
	while (j < HEIGHT)
		put_pixel(p, i, j++, p->config->floor_color);
}

void	transform_to_3d(t_player *player, int i, float ray_angle)
{
	t_texture	*texture;
	int			texx;

	texture = get_texture(player);
	texx = get_tex_x(player, texture, ray_angle);
	draw_wall_slice(player, i, texture, texx);
}
