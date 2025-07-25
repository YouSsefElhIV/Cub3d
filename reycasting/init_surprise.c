/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_surprise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:59:08 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 10:49:36 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static char	*create_frame_filename(int num)
{
	char	*num_str;
	char	*final_path;

	num_str = ft_itoa(num);
	if (!num_str)
		return (NULL);
	final_path = ft_strjoin(num_str, ".xpm");
	if (!final_path)
		return (free(num_str), NULL);
	free (num_str);
	return (final_path);
}

static void	init_fuck(t_player *p, int num_frames)
{
	p->surprise.num_frames = num_frames;
	p->surprise.curr_frames = 0;
	p->surprise.active = 0;
	p->surprise.frame_counter = 0;
	p->surprise.ani_speed = 4;
	p->surprise.frames = malloc(sizeof(t_texture) * num_frames);
	if (!p->surprise.frames)
	{
		cleanup_project(p);
		exit(1);
	}
}

static char	*get_fuck_frame_path(int frame_num)
{
	char	*base_path;
	char	*path_wi_ext;
	char	*final_path;

	base_path = "./textures/surprise/";
	path_wi_ext = create_frame_filename(frame_num);
	final_path = ft_strjoin(base_path, path_wi_ext);
	free(path_wi_ext);
	if (!final_path)
		return (NULL);
	return (final_path);
}

static void	load_fuck_frame(t_player *p, t_texture *cur_tex, char *path)
{
	cur_tex->img = mlx_xpm_file_to_image(p->mlx, path, &cur_tex->width, \
		&cur_tex->height);
	if (!cur_tex->img)
	{
		write(2, "Error\nFailed to load textures fuck\n", 36);
		cleanup_project(p);
		exit(1);
	}
	cur_tex->data = (int *)mlx_get_data_addr(cur_tex->img, &cur_tex->bpp, \
		&cur_tex->s_line, &cur_tex->endian);
}

void	surprise(t_player *p, int num_frames)
{
	int			i;
	char		*final_path;
	t_texture	*cur_tex;

	init_fuck(p, num_frames);
	i = 0;
	while (i < num_frames)
	{
		final_path = get_fuck_frame_path(i + 1);
		if (!final_path)
		{
			free(p->surprise.frames);
			cleanup_project(p);
			exit(1);
		}
		cur_tex = &p->surprise.frames[i];
		load_fuck_frame(p, cur_tex, final_path);
		free(final_path);
		i++;
	}
}
