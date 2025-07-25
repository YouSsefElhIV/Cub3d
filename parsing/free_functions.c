/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:26:23 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 10:47:44 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	cleanup(t_player *player)
{
	if (!player)
		return ;
	if (player->config)
		free_texture(player->config);
	free_map(player);
}

void	map_free(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

void	free_map(t_player *player)
{
	int		i;

	i = 0;
	while (player->map[i])
	{
		if (player->map[i])
			free(player->map[i]);
		i++;
	}
	free(player->map);
}

void	cleanup_project(t_player *player)
{
	t_doors	*courant;
	t_doors	*prec;

	free_texture(player->config);
	destroy_img(player);
	free_map(player);
	if (player->doors)
	{
		courant = player->doors;
		while (courant)
		{
			prec = courant;
			courant = courant->next;
			free(prec);
		}
	}
	if (player->mlx)
		free(player->mlx);
}

void	failing_freeing(t_player *player, char **map, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(map[i]);
		i++;
	}
	free(map);
	free_map(player);
	exit (1);
}
