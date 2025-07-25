/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:33:44 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 09:41:57 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_mlx_init(t_player *player)
{
	player->mlx = mlx_init();
	if (!player->mlx)
	{
		write(2, "Error\nFailed to initialize MLX\n", 32);
		cleanup_project(player);
		exit(1);
	}
}

void	ft_mlx_new_window(t_player *player)
{
	player->mlx_windows = mlx_new_window(player->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!player->mlx_windows)
	{
		write(2, "Error\nFailed to create window\n", 31);
		cleanup_project(player);
		exit(1);
	}
}

void	ft_mlx_new_image(t_player *player)
{
	player->mlx_image = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	if (!player->mlx_image)
	{
		write(2, "Error\nFailed to create image\n", 30);
		cleanup_project(player);
		exit(1);
	}
}

void	load_textures(t_player *p)
{
	p->north.img = mlx_xpm_file_to_image(p->mlx, p->config->no, \
		&p->north.width, &p->north.height);
	p->south.img = mlx_xpm_file_to_image(p->mlx, p->config->so, \
		&p->south.width, &p->south.height);
	p->west.img = mlx_xpm_file_to_image(p->mlx, p->config->we, \
		&p->west.width, &p->west.height);
	p->east.img = mlx_xpm_file_to_image(p->mlx, p->config->ea, \
		&p->east.width, &p->east.height);
	p->door_img.img = mlx_xpm_file_to_image(p->mlx, \
	"./textures/door.xpm", \
		&p->door_img.width, &p->door_img.height);
	if (!p->north.img || !p->south.img || !p->west.img
		|| !p->east.img || !p->door_img.img)
		return (write(2, "Error\nFailed to load textures\n", 31),
			cleanup_project(p), exit(1));
	p->north.data = (int *)mlx_get_data_addr(p->north.img, &p->north.bpp, \
		&p->north.s_line, &p->north.endian);
	p->south.data = (int *)mlx_get_data_addr(p->south.img, &p->south.bpp, \
		&p->south.s_line, &p->south.endian);
	p->west.data = (int *)mlx_get_data_addr(p->west.img, &p->west.bpp, \
		&p->west.s_line, &p->west.endian);
	p->east.data = (int *)mlx_get_data_addr(p->east.img, &p->east.bpp, \
		&p->east.s_line, &p->east.endian);
	p->door_img.data = (int *)mlx_get_data_addr(p->door_img.img, \
		&p->door_img.bpp, &p->door_img.s_line, &p->door_img.endian);
}
