/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:28:40 by achemlal          #+#    #+#             */
/*   Updated: 2025/07/19 09:26:03 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	coor_in(t_player *player, int x, int y)
{
	t_doors	*courant;

	courant = player->doors;
	if (player->doors == NULL)
		return (0);
	while (courant)
	{
		if (courant->x == x && courant->y == y)
			return (1);
		courant = courant->next;
	}
	return (0);
}

void	close_door(t_player *player, int x, int y)
{
	t_doors	*courant;
	t_doors	*prec;

	prec = NULL;
	courant = player->doors;
	while (courant)
	{
		if (courant->x == x && courant->y == y)
		{
			if (prec == NULL)
			{
				if (courant->next == NULL)
					player->doors = NULL;
				else
					player->doors = courant->next;
			}
			else
				prec->next = courant->next;
			free(courant);
			break ;
		}
		prec = courant;
		courant = courant->next;
	}
}
