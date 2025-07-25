/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:33 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:27:14 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	copy_map(t_player *player, char *name)
{
	int		fd;
	char	*tmp;
	char	*tmp_map;
	char	*line;

	1 && (tmp_map = NULL, fd = open(name, O_RDONLY));
	if (fd < 0)
	{
		write (2, "Error, can't open the file\n", 28);
		exit (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = ft_strjoin(tmp_map, line);
		free(tmp_map);
		tmp_map = tmp;
		free(line);
		line = get_next_line(fd);
	}
	if (tmp_map)
		player->new_line_flag = check_new_line(tmp_map);
	player->tmp_map = split_map(tmp_map, '\n');
	free(tmp_map);
	close (fd);
}

static void	fill_row(char *dest, char *src, int longest_row)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	while (j < longest_row)
	{
		dest[j] = 32;
		j++;
	}
	dest[j] = '\0';
}

char	**upgrading(t_player *player, char **map)
{
	int	i;
	int	len;

	i = 0;
	while (i < player->map_end)
	{
		len = (int)ft_strlen(player->tmp_map[i]);
		if (len < player->longest_row)
			map[i] = malloc(sizeof(char) * (player->longest_row + 1));
		else
			map[i] = malloc(sizeof(char) * (len + 1));
		if (!map[i])
			failing_freeing(player, map, i);
		fill_row(map[i], player->tmp_map[i], player->longest_row);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	upgrade_map(t_player *player)
{
	char	**map;

	player->longest_row = longest(player);
	map = (char **)malloc(sizeof(char *) * (player->map_end + 1));
	if (!map)
		exit (1);
	player->map = upgrading(player, map);
	map_free(player->tmp_map);
}

void	parse(t_player *player, char **av)
{
	if (SPEED > 100 || WIDTH > 2300 || HEIGHT > 1800)
	{
		write(2, "Macros Error (SPEED < 100, \
WIDTH < 2300 HEIGHT < 1800)\n", 56);
		exit (0);
	}
	check_extension(player, av);
	init_map_limits(player);
	upgrade_map(player);
	parse_map(player);
	player->config = malloc(sizeof(t_config));
	if (!player->config)
		return (write(2, "Error: malloc config\n", 22), \
		free_map(player), exit(1));
	player->move_up = false;
	player->move_down = false;
	player->move_right = false;
	player->move_left = false;
	parse_texture(player);
}
