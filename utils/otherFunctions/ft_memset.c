/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:35:04 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:28:29 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*st;

	st = (char *)b;
	i = 0;
	while (i < len)
	{
		st[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
