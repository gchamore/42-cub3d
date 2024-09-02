/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_minimap_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:23:19 by anferre           #+#    #+#             */
/*   Updated: 2024/09/02 08:40:18 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_iterate_line(t_img *img, t_coord start, t_coord end, t_coord s)
{
	float	err;
	float	e2;
	t_coord	d;

	d.x = fabs(end.x - start.x);
	d.y = fabs(end.y - start.y);
	err = d.x - d.y;
	while (1)
	{
		ft_mpp(img, start.x, start.y, RED_COLOR);
		if (fabs(start.x - end.x) < 0.5 && fabs(start.y - end.y) < 0.5)
			break ;
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			start.x += s.x * 0.5;
		}
		if (e2 < d.x)
		{
			err += d.x;
			start.y += s.y * 0.5;
		}
	}
}

void	ft_draw_line(t_img *img, t_coord start, t_coord end)
{
	t_coord	s;

	if (start.x < end.x)
		s.x = 1;
	else
		s.x = -1;
	if (start.y < end.y)
		s.y = 1;
	else
		s.y = -1;
	ft_iterate_line(img, start, end, s);
}

void	ft_player_orientation(t_cub *cub, float player_pos_x, \
float player_pos_y)
{
	t_coord	end;
	t_coord	start;
	float	player_size;
	float	end_x;
	float	end_y;

	player_size = PLAYER_SIZE * cub->player->minimap_scale;
	player_pos_x += player_size / 2;
	player_pos_y += player_size / 2;
	end_x = player_pos_x + (cub->player->minimap_scale * 2) * \
	cos(cub->player->angle);
	end_y = player_pos_y + (cub->player->minimap_scale * 2) * \
	sin(cub->player->angle);
	start.x = player_pos_x;
	start.y = player_pos_y;
	end.x = end_x;
	end.y = end_y;
	ft_draw_line(&cub->data->img, start, end);
}

void	ft_draw_player_minimap(t_cub *cub, float start_x, float start_y)
{
	float	player_pos_x;
	float	player_pos_y;
	float	player_size;
	int		i;
	int		j;

	player_size = PLAYER_SIZE * cub->player->minimap_scale;
	player_pos_x = start_x + (cub->player->x_cur * cub->player->minimap_scale) \
	+ (cub->player->minimap_scale / 2) - (player_size / 2);
	player_pos_y = start_y + (cub->player->y_cur * cub->player->minimap_scale) \
	+ (cub->player->minimap_scale / 2) - (player_size / 2);
	i = 0;
	while (i < player_size)
	{
		j = 0;
		while (j < player_size)
		{
			ft_mpp(&cub->data->img, player_pos_x + j, player_pos_y + i, \
			BLUE_COLOR);
			j++;
		}
		i++;
	}
	ft_player_orientation(cub, player_pos_x, player_pos_y);
}

void	ft_draw_map(t_cub *cub)
{
	size_t	x;
	size_t	y;
	int		start_x;
	int		start_y;
	t_coord	pos;

	start_x = WIN_WIDTH - MINIMAP_SIZE + \
	(MINIMAP_SIZE - cub->parse->map_width * cub->player->minimap_scale) / 2;
	start_y = WIN_HEIGTH - MINIMAP_SIZE + \
	(MINIMAP_SIZE - cub->parse->map_height * cub->player->minimap_scale) / 2;
	y = -1;
	while (++y < cub->parse->map_height)
	{
		x = -1;
		while (++x < cub->parse->map_width)
		{
			pos.x = start_x + x * cub->player->minimap_scale;
			pos.y = start_y + y * cub->player->minimap_scale;
			if (cub->map[y][x].value == '1')
				ft_draw_tiles(cub, pos.x, pos.y, BLACK_COLOR);
			else
				ft_draw_tiles(cub, pos.x, pos.y, WHITE_COLOR);
		}
	}
	ft_draw_player_minimap(cub, start_x, start_y);
}
