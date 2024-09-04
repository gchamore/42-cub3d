/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:35:59 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_if_valid_map(t_cub *cub)
{
	size_t	y;
	size_t	x;

	y = 1;
	while (y < cub->parse->map_height - 1)
	{
		x = 1;
		while (x < cub->parse->map_width - 1)
		{
			ft_get_player(cub, y, x);
			if (cub->map[y][x].value == ' ' && cub->map[y][x].used == false)
				ft_check_inside(cub, y, x);
			x++;
		}
		y++;
	}
}

void	ft_check_inside(t_cub *cub, size_t y, size_t x)
{
	if (ft_is_valid(cub, y + 1, x) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
	else if (ft_is_valid(cub, y - 1, x) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
	else if (ft_is_valid(cub, y, x + 1) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
	else if (ft_is_valid(cub, y, x - 1) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
}

int	ft_is_valid(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && y < cub->parse->map_height && x > 0 && \
	x < cub->parse->map_width && (cub->map[y][x].value == '0' || \
	cub->map[y][x].value == 'N' || cub->map[y][x].value == 'S' || \
	cub->map[y][x].value == 'W' || cub->map[y][x].value == 'E'))
		return (1);
	return (0);
}

void	ft_get_player(t_cub *cub, size_t y, size_t x)
{
	if (cub->map[y][x].value == 'N' || cub->map[y][x].value == 'S' || \
	cub->map[y][x].value == 'W' || cub->map[y][x].value == 'E')
	{
		if (cub->player->y_start != 0 || cub->player->x_start != 0 || \
		cub->player->dir != 0)
			ft_error(cub, "Invalid map to much players", -1, -1);
		cub->player->dir = cub->map[y][x].value;
		cub->player->y_start = y;
		cub->player->x_start = x;
		cub->player->y_cur = y;
		cub->player->x_cur = x;
	}
	if (y == cub->parse->map_height - 2 && x == cub->parse->map_width - 2 && \
	cub->player->dir == 0)
		ft_error(cub, "No player", -1, -1);
}
