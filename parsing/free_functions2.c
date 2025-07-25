/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:34:42 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/24 15:00:15 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	free_double_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_texture(t_config *config)
{
	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
	free(config);
}

int	exit_bar(t_player *player)
{
	free_map(player);
	free(player->mlx);
	exit (0);
}

void	destroy_img(t_player *p)
{
	if (p->north.img)
		mlx_destroy_image(p->mlx, p->north.img);
	if (p->south.img)
		mlx_destroy_image(p->mlx, p->south.img);
	if (p->west.img)
		mlx_destroy_image(p->mlx, p->west.img);
	if (p->east.img)
		mlx_destroy_image(p->mlx, p->east.img);
	if (p->door_img.img)
		mlx_destroy_image(p->mlx, p->door_img.img);
}

int	count_ver(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
