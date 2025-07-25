/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:22:39 by yel-haya          #+#    #+#             */
/*   Updated: 2025/07/19 09:28:55 by achemlal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	while (i > 0)
	{
		if (s[i - 1] == (char) c)
			return ((char *)&s[i - 1]);
		i--;
	}
	return (NULL);
}
