/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surprise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:01:36 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 10:46:59 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	update_animation(t_fuck *surprise)
{
	if (surprise->active)
	{
		surprise->frame_counter++;
		if (surprise->frame_counter >= surprise->ani_speed)
		{
			surprise->frame_counter = 0;
			surprise->curr_frames++;
			if (surprise->curr_frames >= surprise->num_frames)
			{
				surprise->curr_frames = 0;
				surprise->active = 0;
			}
		}
	}
}

void	calculate_draw(t_player **p, t_texture *curr_frame)
{
	float	scale_ratio;

	scale_ratio = 0.7;
	(*p)->target_width = (int)(WIDTH * scale_ratio);
	(*p)->target_height = (curr_frame->height * (*p)->target_width)
		/ curr_frame->width;
	(*p)->start_x = 0;
	(*p)->start_y = HEIGHT - (*p)->target_height;
}

void	draw_texture(t_player **p, t_texture *curr_frame)
{
	int	color;
	int	src_x;
	int	src_y;
	int	x;
	int	y;

	y = 0;
	while (y < (*p)->target_height)
	{
		x = 0;
		while (x < (*p)->target_width)
		{
			src_x = x * curr_frame->width / (*p)->target_width;
			src_y = y * curr_frame->height / (*p)->target_height;
			color = curr_frame->data[src_y * curr_frame->width + src_x];
			if ((color & 0x00FFFFFF) != 0)
				put_pixel((*p), (*p)->start_x + x, (*p)->start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_emote(t_player *p)
{
	t_texture	*curr_frame;

	curr_frame = &p->surprise.frames[p->surprise.curr_frames];
	calculate_draw(&p, curr_frame);
	draw_texture(&p, curr_frame);
}
