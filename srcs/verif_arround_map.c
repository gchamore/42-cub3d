/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arround_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:53:05 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:35:01 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_borders(t_cub *cub, size_t y, size_t x)
{
	while (y < cub->parse->map_height)
	{
		x = -1;
		while (++x < cub->parse->map_width)
		{
			ft_reset_map(cub);
			ft_check_cell(cub, y, x);
			if (cub->map[y][x].value == '1')
			{
				if (ft_check_arround_1(cub, y, x) == 1)
					ft_error(cub, "Invalid 1 Alone at", y, x);
			}
			if (y == 0 || x == 0 || y == cub->parse->map_height - 1 || \
			x == cub->parse->map_width - 1)
			{
				ft_check_corners_1(cub, y, x);
				ft_check_corners_2(cub, y, x);
				ft_check_sides_1(cub, y, x);
				ft_check_sides_2(cub, y, x);
				if (cub->map[y][x].value != '1' && cub->map[y][x].value != ' ')
					ft_error(cub, "Invalid map 0 at", y, x);
			}
		}
		y++;
	}
}

void	ft_check_corners_1(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x == 0 && (cub->map[y][x].value == ' ' || \
	ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y + 1, x) == 1 || ft_is_valid(cub, y, x + 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
	if (y == cub->parse->map_height - 1 && x == cub->parse->map_width - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y - 1, x) == 1 || ft_is_valid(cub, y, x - 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
}

void	ft_check_corners_2(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x == cub->parse->map_width - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y + 1, x) == 1 || ft_is_valid(cub, y, x - 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
	if (y == cub->parse->map_height - 1 && x == 0 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y - 1, x) == 1 || ft_is_valid(cub, y, x + 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
}

void	ft_check_sides_1(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x > 0 && x < cub->parse->map_width - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y + 1, x) == 1 || \
		ft_is_valid(cub, y, x + 1) == 1) || (ft_is_valid(cub, y, x - 1) == 1))
			ft_error(cub, "Invalid map wrong value arround up side", y, x);
	}
	if (x == 0 && y > 0 && y < cub->parse->map_height - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y + 1, x) == 1 || \
		ft_is_valid(cub, y - 1, x) == 1) || (ft_is_valid(cub, y, x + 1) == 1))
			ft_error(cub, "Invalid map wrong value arround left side", y, x);
	}
}

void	ft_check_sides_2(t_cub *cub, size_t y, size_t x)
{
	if (y == cub->parse->map_height - 1 && x > 0 && \
		x < cub->parse->map_width - 1 && (cub->map[y][x].value == ' ' || \
		ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y - 1, x) == 1 || \
		ft_is_valid(cub, y, x + 1) == 1) || (ft_is_valid(cub, y, x - 1) == 1))
			ft_error(cub, "Invalid map wrong value arround down side", y, x);
	}
	if (x == cub->parse->map_width - 1 && y > 0 && \
	y < cub->parse->map_height - 1 && (cub->map[y][x].value == ' ' || \
	ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y + 1, x) == 1 || \
		ft_is_valid(cub, y - 1, x) == 1) || (ft_is_valid(cub, y, x - 1) == 1))
			ft_error(cub, "Invalid map wrong value arround right side", y, x);
	}
}
