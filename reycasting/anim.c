/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:13:06 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 09:26:13 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	calculate_draw_params(t_player *p, t_texture *curr_frame)
{
	float	scale_ratio;

	scale_ratio = 1.2;
	p->target_width = (int)(WIDTH * scale_ratio);
	p->target_height = (curr_frame->height * p->target_width)
		/ curr_frame->width;
	p->start_x = WIDTH - p->target_width;
	p->start_y = HEIGHT - p->target_height;
}

void	draw_texture_scaled(t_player *p, t_texture *curr_frame)
{
	int	color;
	int	src_x;
	int	src_y;
	int	x;
	int	y;

	y = 0;
	while (y < p->target_height)
	{
		x = 0;
		while (x < p->target_width)
		{
			src_x = x * curr_frame->width / p->target_width;
			src_y = y * curr_frame->height / p->target_height;
			color = curr_frame->data[src_y * curr_frame->width + src_x];
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(p, p->start_x + x, p->start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_fanous(t_player *p)
{
	t_texture	*curr_frame;

	curr_frame = &p->fanous_anim.frames[p->fanous_anim.curr_frames];
	calculate_draw_params(p, curr_frame);
	draw_texture_scaled(p, curr_frame);
}

int	game_loop(t_player *p)
{
	p->fanous_anim.frame_counter++;
	if (p->fanous_anim.frame_counter >= p->fanous_anim.ani_speed)
	{
		p->fanous_anim.frame_counter = 0;
		p->fanous_anim.curr_frames++;
		if (p->fanous_anim.curr_frames >= p->fanous_anim.num_frames)
			p->fanous_anim.curr_frames = 0;
	}
	draw_fanous(p);
	return (0);
}
