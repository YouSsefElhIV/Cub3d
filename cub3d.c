/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:29:51 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/24 14:50:28 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

void	clear_screen(t_player *player)
{
	int	len;

	len = WIDTH * HEIGHT * (player->bits / 8);
	ft_memset(player->data, 0, len);
}

int	put_content(t_player *player)
{
	clear_screen(player);
	moving(player);
	reycasting(player);
	if (player->surprise.active)
	{
		draw_emote(player);
		update_animation(&player->surprise);
	}
	game_loop(player);
	put_map(player);
	mlx_put_image_to_window(player->mlx, player->mlx_windows, \
			player->mlx_image, 0, 0);
	return (0);
}

void	init_mlx(t_player *player)
{
	ft_mlx_init(player);
	ft_mlx_new_window(player);
	ft_mlx_new_image(player);
	load_textures(player);
	surprise(player, 19);
	load_fanous_anim(player, 33);
	player->data = mlx_get_data_addr(player->mlx_image, \
		&player->bits, &player->lines, &player->end);
	mlx_put_image_to_window(player->mlx, player->mlx_windows, \
		player->mlx_image, 0, 0);
	mlx_hook(player->mlx_windows, 2, 1L << 0, key_pressed, player);
	mlx_hook(player->mlx_windows, 3, 1L << 1, key_released, player);
	mlx_hook(player->mlx_windows, 17, 0, exit_bar, player);
	mlx_hook(player->mlx_windows, 6, 1L << 6, mouse_move, player);
}

int	main(int ac, char **av)
{
	t_player	player;

	ft_memset(&player, 0, sizeof(t_player));
	if (ac == 2)
	{
		parse(&player, av);
		init_mlx(&player);
		mlx_clear_window(player.mlx, player.mlx_windows);
		mlx_loop_hook(player.mlx, put_content, &player);
		mlx_loop(player.mlx);
		cleanup_project(&player);
	}
	else
		printf("Usage: ./cub3d <maps/choose_a_map_name\n");
	return (0);
}
