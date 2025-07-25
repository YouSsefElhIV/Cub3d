/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:05:09 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:27:04 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	set_texture(char **texture, char *line)
{
	if (*texture)
		return (0);
	*texture = ft_strtrim(line, "\n\t ");
	if (!*texture)
		return (0);
	return (1);
}

int	parse_texture_line(char *line, t_config *cfg)
{
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&cfg->no, line + 3));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&cfg->so, line + 3));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&cfg->we, line + 3));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&cfg->ea, line + 3));
	return (1);
}

void	validate_textures(t_player *player, t_config *cfg)
{
	if (!cfg->no || !cfg->so || !cfg->we || !cfg->ea)
	{
		cleanup(player);
		write(2, "Error: Missing one or more textures\n", 36);
		exit(1);
	}
}

void	parse_texture(t_player *player)
{
	int			i;
	t_config	*cfg;

	player->config->no = NULL;
	player->config->so = NULL;
	player->config->we = NULL;
	player->config->ea = NULL;
	player->config->floor_color = -1;
	player->config->ceiling_color = -1;
	cfg = player->config;
	i = 0;
	while (player->map[i])
	{
		if (parse_texture_line(player->map[i], cfg) == 0)
			return (write(2, "Error: Duplicate EA texture\n", 29),
				cleanup(player), exit(1));
		i++;
	}
	validate_textures(player, cfg);
	if (!is_valid_prefix(player))
		return (write(2, "Error: Invalid prefix found in map lines\n", 41),
			cleanup(player), exit(1));
	parse_colors(player);
}
