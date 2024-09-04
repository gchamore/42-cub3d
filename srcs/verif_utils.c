/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:51:58 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:36:10 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_reset_map(t_cub *cub)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < cub->parse->map_height)
	{
		x = 0;
		while (x < cub->parse->map_width)
		{
			cub->map[y][x].used = false;
			cub->map[y][x].count = 0;
			cub->map[y][x].count_0 = 0;
			x++;
		}
		y++;
	}
}

void	ft_check_cell(t_cub *cub, size_t y, size_t x)
{
	if (cub->map[y][x].value == ' ')
	{
		if (ft_count(cub, y, x, '0') != 0 || ft_count(cub, y, x, 'N') != 0 || \
		ft_count(cub, y, x, 'S') != 0 || ft_count(cub, y, x, 'W') != 0 || \
		ft_count(cub, y, x, 'E') != 0)
		{
			printf("cube->map[y][x].value = %c\n", cub->map[y][x].value);
			ft_error(cub, "Invalid 0,N,S,E,W Alone arround", y, x);
		}
	}
}
