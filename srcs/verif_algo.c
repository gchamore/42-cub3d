/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:18 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 15:59:46 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_arround_1(t_cub *cub, size_t y, size_t x)
{
	cub->map[y][x].used = true;
	cub->map[y][x].count_0 = ft_count(cub, y, x, '0');
	cub->map[y][x].count_0 += ft_count(cub, y, x, 'N');
	cub->map[y][x].count_0 += ft_count(cub, y, x, 'S');
	cub->map[y][x].count_0 += ft_count(cub, y, x, 'W');
	cub->map[y][x].count_0 += ft_count(cub, y, x, 'E');
	cub->map[y][x].count = ft_count(cub, y, x, '1');
	if (cub->map[y][x].count_0 != 0)
		return (0);
	if (ft_check_map_direction(cub, y, x) == 0)
		return (0);
	else
		return (1);
}

int	ft_check_map_direction(t_cub *cub, size_t y, size_t x)
{
	if (ft_verif_right(cub, y, x) == 0)
		return (0);
	if (ft_verif_right_down(cub, y, x) == 0)
		return (0);
	if (ft_verif_down(cub, y, x) == 0)
		return (0);
	if (ft_verif_left_down(cub, y, x) == 0)
		return (0);
	if (ft_verif_left(cub, y, x) == 0)
		return (0);
	if (ft_verif_left_up(cub, y, x) == 0)
		return (0);
	if (ft_verif_up(cub, y, x) == 0)
		return (0);
	if (ft_verif_right_up(cub, y, x) == 0)
		return (0);
	return (1);
}

int	ft_count(t_cub *cub, size_t y, size_t x, char value)
{
	int	count;

	count = 0;
	if (x + 1 < cub->parse->map_width && cub->map[y][x + 1].value == value && \
		cub->map[y][x + 1].used == false)
		count++;
	if (y + 1 < cub->parse->map_height && cub->map[y + 1][x].value == value && \
		cub->map[y + 1][x].used == false)
		count++;
	if (x > 0 && cub->map[y][x - 1].value == value && \
		cub->map[y][x - 1].count == 0 && cub->map[y][x - 1].used == false)
		count++;
	if (y > 0 && cub->map[y - 1][x].value == value && \
		cub->map[y - 1][x].count == 0 && cub->map[y - 1][x].used == false)
		count++;
	if (value == '1')
		count += ft_check_diag(cub, y, x, value);
	return (count);
}

int	ft_check_diag(t_cub *cub, size_t y, size_t x, char value)
{
	int	count;

	count = 0;
	if (y > 0 && x > 0 && cub->map[y - 1][x - 1].value == value && \
	cub->map[y - 1][x - 1].used == false)
		count++;
	if (y > 0 && x + 1 < cub->parse->map_width && \
	cub->map[y - 1][x + 1].value == value && \
	cub->map[y - 1][x + 1].used == false)
		count++;
	if (y + 1 < cub->parse->map_height && x > 0 && \
	cub->map[y + 1][x - 1].value == value && \
	cub->map[y + 1][x - 1].used == false)
		count++;
	if (y + 1 < cub->parse->map_height && x + 1 < cub->parse->map_width && \
	cub->map[y + 1][x + 1].value == value && \
	cub->map[y + 1][x + 1].used == false)
		count++;
	return (count);
}
