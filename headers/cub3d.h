/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:18:04 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/24 15:00:34 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# include "mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// these are for linux
//# define ESC 65307
//# define W 119
//# define S 115
//# define A 97
//# define D 100
//# define LEFT 65361
//# define RIGHT 65363
//# define SPACE 32

// these for Mac
# define W      13
# define A      0
# define S      1
# define D      2
# define LEFT   123
# define RIGHT  124
# define DOWN   125
# define UP     126
# define SPACE  49
# define ESC 53

# define PI      3.14159265359
# define ANGLE   0.07
# define SPEED   8
# define HEIGHT  1200
# define WIDTH   1500

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		s_line;
	int		endian;
}	t_texture;

typedef struct s_anim
{
	t_texture	*frames;
	int			num_frames;
	int			curr_frames;
	int			ani_speed;
	int			frame_counter;
}	t_anim;

typedef struct s_fuck
{
	t_texture	*frames;
	int			num_frames;
	int			curr_frames;
	int			active;
	int			ani_speed;
	int			frame_counter;
}	t_fuck;

typedef struct s_dda
{
	int		x;
	int		y;
	int		x_step;
	int		y_step;
	float	x_line_length;
	float	y_line_length;
	float	x_dist;
	float	y_dist;
	float	distence;
	int		wall_face;
	int		hit_door;
}	t_dda;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_doors
{
	int				x;
	int				y;
	struct s_doors	*next;
}	t_doors;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		ceiling_color;
}	t_config;

typedef struct s_player
{
	bool		move_up;
	bool		move_down;
	bool		move_left;
	bool		move_right;
	bool		see_left;
	bool		see_right;
	bool		door_open;
	float		x;
	float		y;
	char		old_move;
	float		angle;
	int			empty_space;
	int			wall;
	int			door;
	t_doors		*doors;
	int			ply_n;
	int			ply_s;
	int			ply_e;
	int			ply_w;
	int			map_start;
	int			map_end;
	int			longest_row;
	int			new_line_flag;
	int			mini_a;
	int			mini_b;

	char		**map;
	char		**tmp_map;
	char		**map3;
	char		**map2;
	t_dda		dda;
	int			which;
	void		*mlx;
	char		*data;
	void		*mlx_image;
	void		*mlx_windows;
	int			bits;
	int			lines;
	int			end;
	int			color;
	int			start_x;
	int			start_y;
	int			target_width;
	int			target_height;
	int			f_count;
	int			c_count;
	double		dir_x;
	double		dir_y;
	t_config	*config;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_texture	door_img;
	t_fuck		surprise;
	t_anim		fanous_anim;

}	t_player;

void	parse(t_player *player, char **av);
void	parse_map(t_player *player);
void	free_map(t_player *player);
void	map_free(char **map);
char	**split_map(char const *s, char c);
void	flood_fill_for_connection(t_player *player);
void	parse_texture(t_player *player);
void	free_texture(t_config *config);
void	parse_colors(t_player *player);
void	cleanup(t_player *player);
void	free_double_arr(char **split);
void	copy_map(t_player *player, char *name);
void	free_config(t_player *player);
void	destroy_img(t_player *p);
void	cleanup_project(t_player *player);
void	check_map_content(t_player *player);
void	check_bounderies(t_player *player);
char	**copy_of_the_map(t_player *player);
int		longest(t_player *p);
void	failing_freeing(t_player *player, char **map, int k);
void	check_extension(t_player *player, char **av);
void	count_content(t_player *p);
int		is_valid_prefix(t_player *p);
int		check_new_line(char *map);
int		exit_bar(t_player *player);
int		key_pressed(int key, t_player *player);
int		key_released(int key, t_player *player);
int		mouse_move(int x, int y, void *param);
void	put_map(t_player *player);
void	put_square(t_player *player, int x, int y, int size);
void	moving(t_player *player);
bool	valid_move(t_player *player, float x, float y);
void	put_pixel(t_player *p, int x, int y, int color);
void	put_angle_helper(t_player *player, int a, int i, int j);
void	handle_doors(t_player *player);
int		coor_in(t_player *player, int x, int y);
void	close_door(t_player *player, int x, int y);
void	put_ray_line(t_player *player, float ray_angle, int i);
void	reycasting(t_player *player);
void	init_p(int p[4][2]);
void	ft_mlx_init(t_player *player);
void	ft_mlx_new_window(t_player *player);
void	ft_mlx_new_image(t_player *player);
void	load_textures(t_player *p);
void	transform_to_3d(t_player *player, int i, float ray_angle);
void	load_fanous_anim(t_player *p, int num_frames);
int		game_loop(t_player *p);
void	init_map_limits(t_player *p);
char	*get_next_line(int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *st);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strtrim(char *s1, char *set);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
void	surprise(t_player *p, int num_frames);
void	draw_emote(t_player *p);
void	update_animation(t_fuck *surprice);
int		count_ver(char *str);
int		touch(t_player *player, float fx, float fy);
void	put_angle(t_player *player);

#endif
