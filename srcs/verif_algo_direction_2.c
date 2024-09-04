/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_algo_direction_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:54:55 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:35:08 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_verif_left(t_cub *cub, size_t y, size_t x)
{
	if (x > 0 && cub->map[y][x].value == '1' && \
	cub->map[y][x - 1].value == '1' && cub->map[y][x - 1].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y, x - 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_left_up(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && x > 0 && cub->map[y - 1][x - 1].value == '1' && \
	cub->map[y - 1][x - 1].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y - 1, x - 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_up(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && cub->map[y][x].value == '1' && \
	cub->map[y - 1][x].value == '1' && cub->map[y - 1][x].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y - 1, x) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_right_up(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && x + 1 < cub->parse->map_width && \
	cub->map[y - 1][x + 1].value == '1' && \
	cub->map[y - 1][x + 1].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y - 1, x + 1) == 0)
			return (0);
	}
	return (1);
}
