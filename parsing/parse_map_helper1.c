/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:39:37 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:26:38 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	check_extension(t_player *player, char **av)
{
	char	*dot_position;

	dot_position = ft_strrchr(av[1], '.');
	if (dot_position == NULL || ft_strlen(dot_position) != 4 \
	|| ft_strncmp(dot_position, ".cub", 4) != 0)
	{
		write(2, "Map Error\n", 10);
		exit(1);
	}
	copy_map(player, av[1]);
	if (!player->tmp_map)
	{
		write(2, "map Error\n", 11);
		exit (1);
	}
	if (player->new_line_flag == 1)
	{
		map_free(player->tmp_map);
		write(2, "map Error\n", 11);
		exit (1);
	}
}

void	update_content(t_player *player, char c)
{
	if (c == '1')
		(player->wall)++;
	else if (c == '0')
		(player->empty_space)++;
	else if (c == 'W')
		(player->ply_w)++;
	else if (c == 'E')
		(player->ply_e)++;
	else if (c == 'N')
		(player->ply_n)++;
	else if (c == 'S')
		(player->ply_s)++;
	else if (c == 'D')
		(player->door)++;
	else if (c == ' ' || c == '\n')
		return ;
	else
	{
		write(2, "Map Error\n", 11);
		free_map(player);
		exit (1);
	}
}

void	check_map_content(t_player *player)
{
	int	i;
	int	j;

	i = player->map_start;
	while (i < player->map_end)
	{
		j = 0;
		while (player->map[i][j])
		{
			update_content(player, player->map[i][j]);
			j++;
		}
		i++;
	}
}

char	**copying(t_player *player, char **map, int i)
{
	int		j;
	int		k;

	k = 0;
	while (i < player->map_end)
	{
		map[k] = (char *)malloc(sizeof(char) * (player->longest_row + 1));
		if (!map[k])
			failing_freeing(player, map, k);
		j = 0;
		while (j < player->longest_row && player->map[i][j])
		{
			map[k][j] = player->map[i][j];
			j++;
		}
		while (j < player->longest_row)
		{
			map[k][j] = 0;
			j++;
		}
		map[k][j] = '\0';
		i++;
		k++;
	}
	return (map[k] = NULL, map);
}

char	**copy_of_the_map(t_player *player)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * \
	(player->map_end - player->map_start + 1));
	if (!map)
		exit (1);
	map = copying(player, map, player->map_start);
	return (map);
}
